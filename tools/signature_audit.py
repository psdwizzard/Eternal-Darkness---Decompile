#!/usr/bin/env python3
"""Audit TU-local extern function declarations for PPC EABI disagreements.

The game translation units intentionally declare their dependencies locally.  That
makes it easy for two already-matching callers to acquire source-level signatures
which look plausible in isolation but cannot both describe the retail callee.  This
tool groups those declarations by symbol and compares the parts of a prototype
which affect PowerPC EABI register assignment.

This is a declaration audit, not a C parser.  It accepts the deliberately small
prototype dialect used below src/game, including multiline declarations and
function-pointer parameters.
"""

from __future__ import annotations

import argparse
import json
import re
from collections import Counter, defaultdict
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_SOURCE = ROOT / "src" / "game"
DEFAULT_RETAIL_EVIDENCE = ROOT / "config" / "GEDE01" / "retail-return-shapes.json"
FUNCTION_NAME = re.compile(r"\b(fn_[0-9A-Fa-f]+)\s*\(")
LEGACY_UNSPECIFIED_FUNCTION = re.compile(
    r"(?m)^[ \t]*(?:M2C_UNK|UNK_TYPE)[ \t]+(fn_[0-9A-Fa-f]+)"
    r"[ \t]*\([ \t]*\)[ \t]*;"
)
EXTERN_STATEMENT = re.compile(r"\bextern\b(?P<body>.*?);", re.DOTALL)
COMMENTS = re.compile(r"/\*.*?\*/|//[^\n]*", re.DOTALL)
FLOAT_TYPES = {"float", "f32"}
DOUBLE_TYPES = {"double", "f64"}
INT64_TYPES = {
    "long long", "signed long long", "unsigned long long", "s64", "u64",
    "int64_t", "uint64_t",
}
TYPE_WORDS = {
    "void", "char", "short", "int", "long", "float", "double", "signed",
    "unsigned", "const", "volatile", "restrict", "struct", "union", "enum",
    "s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "f32", "f64",
    "int8_t", "uint8_t", "int16_t", "uint16_t", "int32_t", "uint32_t",
    "int64_t", "uint64_t", "size_t", "ptrdiff_t", "bool", "_Bool",
}
AGGREGATE_TYPES: set[str] = set()
AGGREGATE_TYPEDEF = re.compile(
    r"\btypedef\s+(?:struct|union)\b[^;{]*\{.*?\}\s*([A-Za-z_]\w*)\s*;",
    re.DOTALL,
)
OBJECT_DEFINE = re.compile(
    r"(?m)^[ \t]*#define[ \t]+([A-Za-z_]\w*)[ \t]+([^\n]+)$"
)


@dataclass(frozen=True)
class Declaration:
    symbol: str
    return_type: str
    parameters: tuple[str, ...]
    variadic: bool
    unspecified_parameters: bool
    path: str
    line: int

    @property
    def signature(self) -> str:
        params = list(self.parameters)
        if self.variadic:
            params.append("...")
        if not params and not self.unspecified_parameters:
            params.append("void")
        return f"{self.return_type} {self.symbol}({', '.join(params)})"

    @property
    def return_shape(self) -> str:
        return return_register_shape(self.return_type)

    @property
    def abi_shape(self) -> tuple[str, tuple[str, ...], bool, bool]:
        parameter_shapes = tuple(parameter_register_shape(p) for p in self.parameters)
        if is_aggregate(self.return_type):
            parameter_shapes = ("GPR:1(hidden-result)",) + parameter_shapes
        return (
            self.return_shape,
            parameter_shapes,
            self.variadic,
            self.unspecified_parameters,
        )


@dataclass(frozen=True)
class Definition:
    symbol: str
    return_type: str
    parameters: tuple[str, ...]
    variadic: bool
    unspecified_parameters: bool
    path: str
    line: int

    @property
    def signature(self) -> str:
        params = list(self.parameters)
        if self.variadic:
            params.append("...")
        if not params and not self.unspecified_parameters:
            params.append("void")
        return f"{self.return_type} {self.symbol}({', '.join(params)})"

    @property
    def return_shape(self) -> str:
        return return_register_shape(self.return_type)

    @property
    def parameter_shapes(self) -> tuple[str, ...]:
        return tuple(parameter_register_shape(item) for item in self.parameters)


def squash_space(text: str) -> str:
    text = re.sub(r"\s+", " ", text.strip())
    text = re.sub(r"\s*\*\s*", "*", text)
    text = re.sub(r"\s*\[\s*", "[", text)
    text = re.sub(r"\s*\]\s*", "]", text)
    return text


def split_parameters(text: str) -> list[str]:
    """Split a parameter list while retaining nested function declarators."""
    result: list[str] = []
    start = 0
    parens = brackets = 0
    for index, char in enumerate(text):
        if char == "(":
            parens += 1
        elif char == ")":
            parens -= 1
        elif char == "[":
            brackets += 1
        elif char == "]":
            brackets -= 1
        elif char == "," and parens == 0 and brackets == 0:
            result.append(text[start:index])
            start = index + 1
    result.append(text[start:])
    return [squash_space(item) for item in result if item.strip()]


def parameter_type(declaration: str) -> str:
    """Remove a declarator name where present; names do not affect the ABI."""
    declaration = squash_space(declaration)
    if "(*" in declaration or re.search(r"\(\s*\*", declaration):
        return "function-pointer"
    if "[" in declaration:
        # Array parameters are adjusted to pointers by C.
        return re.sub(r"\s+[A-Za-z_]\w*(?=\[)", "", declaration) + "*"

    match = re.search(r"\b([A-Za-z_]\w*)$", declaration)
    if not match:
        return declaration
    final = match.group(1)
    prefix = declaration[: match.start()].rstrip()
    if not prefix or final in TYPE_WORDS:
        return declaration
    prefix_words = prefix.split()
    # Do not mistake the tag in `struct Foo` or the type in `const Foo` for a
    # parameter name.  In all other multi-token spellings used by this tree, the
    # trailing non-keyword identifier is the optional declarator name.
    if prefix_words[-1] in {"struct", "union", "enum"}:
        return declaration
    if all(word in {"const", "volatile", "restrict"} for word in prefix_words):
        return declaration
    return squash_space(prefix)


def base_type(type_name: str) -> str:
    type_name = parameter_type(type_name)
    type_name = re.sub(r"\b(const|volatile|restrict)\b", "", type_name)
    return squash_space(type_name)


def has_bare_symbol_reference(path: Path, symbol: str) -> bool:
    """Return true when a TU uses a declaration as a callback/cast value."""
    text = COMMENTS.sub("", path.read_text(encoding="utf-8"))
    text = EXTERN_STATEMENT.sub("", text)
    return re.search(rf"\b{re.escape(symbol)}\b(?!\s*\()", text) is not None


def return_type_is_available(path: Path, return_type: str) -> bool:
    """Conservatively check whether an owned return spelling is usable in a TU."""
    spelling = base_type(return_type).replace("*", "").strip()
    if spelling in TYPE_WORDS or spelling in {"M2C_UNK", "UNK_TYPE", "undefined4"}:
        return True
    text = COMMENTS.sub("", path.read_text(encoding="utf-8"))
    return re.search(
        rf"\b(?:typedef\b[^;]*\b|struct\s+|union\s+|enum\s+){re.escape(spelling)}\b",
        text,
    ) is not None


def return_register_shape(type_name: str) -> str:
    base = base_type(type_name)
    if base in {"M2C_UNK", "UNK_TYPE"}:
        return "unknown"
    if base == "void":
        return "none"
    if "*" in base or base == "function-pointer":
        return "GPR:r3"
    if base in FLOAT_TYPES | DOUBLE_TYPES:
        return "FPR:f1"
    if base in INT64_TYPES:
        return "GPR:r3-r4"
    if is_aggregate(type_name):
        return "none"
    return "GPR:r3"


def return_value_kind(type_name: str) -> str:
    """Classify source-level result semantics beyond the physical register file."""
    base = base_type(type_name)
    if base == "void":
        return "void"
    if "*" in base or base == "function-pointer":
        return "pointer"
    if base in FLOAT_TYPES | DOUBLE_TYPES:
        return "floating"
    if base in INT64_TYPES:
        return "integer64"
    if is_aggregate(type_name):
        return "aggregate"
    return "integer"


def is_aggregate(type_name: str) -> bool:
    base = base_type(type_name)
    return base.startswith(("struct ", "union ")) or base in AGGREGATE_TYPES


def parameter_register_shape(type_name: str) -> str:
    base = base_type(type_name)
    if "*" in base or base == "function-pointer":
        return "GPR:1"
    if base in FLOAT_TYPES | DOUBLE_TYPES:
        return "FPR:1"
    if base in INT64_TYPES:
        return "GPR:2"
    if is_aggregate(base):
        return "aggregate"
    return "GPR:1"


def declarations_in(path: Path, source_root: Path) -> Iterable[Declaration]:
    original = path.read_text(encoding="utf-8")
    text = COMMENTS.sub(lambda match: "\n" * match.group(0).count("\n"), original)
    # Some matching TUs use object-like macros to retain ABI-equivalent source
    # spellings whose aggregate-return lowering differs in MWCC.  Audit the
    # expanded declaration, not the macro identifier (which otherwise looks
    # like an integer typedef and creates a false return-register conflict).
    defines = dict(OBJECT_DEFINE.findall(text))

    def expand_macros(body: str) -> str:
        for _ in range(8):
            expanded = re.sub(
                r"\b[A-Za-z_]\w*\b",
                lambda item: defines.get(item.group(0), item.group(0)),
                body,
            )
            if expanded == body:
                break
            body = expanded
        return body

    for statement in EXTERN_STATEMENT.finditer(text):
        body = expand_macros(statement.group("body"))
        functions = []
        depth = 0
        search_from = 0
        for function in FUNCTION_NAME.finditer(body):
            for char in body[search_from:function.start()]:
                if char == "(":
                    depth += 1
                elif char == ")":
                    depth -= 1
            search_from = function.start()
            if depth == 0:
                functions.append(function)
        if not functions:
            continue

        # A comma-separated declaration shares the first declarator's type:
        # `extern void fn_A(void), fn_B(int);` declares both functions as void.
        return_type = squash_space(body[: functions[0].start()])
        for function in functions:
            cursor = function.end()
            depth = 1
            while cursor < len(body) and depth:
                if body[cursor] == "(":
                    depth += 1
                elif body[cursor] == ")":
                    depth -= 1
                cursor += 1
            if depth:
                continue

            parameter_text = body[function.end(): cursor - 1]
            unspecified_parameters = not parameter_text.strip()
            raw_parameters = split_parameters(parameter_text)
            variadic = bool(raw_parameters and raw_parameters[-1] == "...")
            if variadic:
                raw_parameters.pop()
            if raw_parameters == ["void"]:
                raw_parameters = []
            parameters = tuple(parameter_type(item) for item in raw_parameters)
            line = text.count("\n", 0, statement.start() + function.start()) + 1
            yield Declaration(
                symbol=function.group(1),
                return_type=return_type,
                parameters=parameters,
                variadic=variadic,
                unspecified_parameters=unspecified_parameters,
                path=str(path.relative_to(ROOT)),
                line=line,
            )


def definition_in(path: Path) -> Definition | None:
    """Recover the primary function definition from a per-function game TU."""
    match = re.fullmatch(r"game_(fn_[0-9A-Fa-f]+)", path.stem)
    if match is None:
        return None
    symbol = match.group(1)
    original = path.read_text(encoding="utf-8")
    text = COMMENTS.sub(lambda item: "\n" * item.group(0).count("\n"), original)
    header = re.compile(
        rf"(?m)^[ \t]*(?!extern\b)(?P<return>[A-Za-z_]"
        rf"[A-Za-z0-9_ \t*]*?)[ \t]+{re.escape(symbol)}[ \t]*\("
    )
    for candidate in header.finditer(text):
        cursor = candidate.end()
        depth = 1
        while cursor < len(text) and depth:
            if text[cursor] == "(":
                depth += 1
            elif text[cursor] == ")":
                depth -= 1
            cursor += 1
        if depth or not re.match(r"\s*\{", text[cursor:]):
            continue
        return_type = re.sub(
            r"\b(?:asm|static|inline|__inline)\b", "", candidate.group("return")
        )
        parameter_text = text[candidate.end(): cursor - 1]
        unspecified_parameters = not parameter_text.strip()
        raw_parameters = split_parameters(parameter_text)
        variadic = bool(raw_parameters and raw_parameters[-1] == "...")
        if variadic:
            raw_parameters.pop()
        if raw_parameters == ["void"]:
            raw_parameters = []
        return Definition(
            symbol=symbol,
            return_type=squash_space(return_type),
            parameters=tuple(parameter_type(item) for item in raw_parameters),
            variadic=variadic,
            unspecified_parameters=unspecified_parameters,
            path=str(path.relative_to(ROOT)),
            line=text.count("\n", 0, candidate.start()) + 1,
        )
    return None


def load_retail_evidence(path: Path) -> dict[str, dict[str, str]]:
    if not path.is_file():
        return {}
    payload = json.loads(path.read_text(encoding="utf-8"))
    symbols = payload.get("symbols", {})
    if not isinstance(symbols, dict):
        raise ValueError(f"{path}: 'symbols' must be an object")
    return symbols


def audit(
    source_root: Path,
    retail_evidence_path: Path = DEFAULT_RETAIL_EVIDENCE,
    applied_symbols: set[str] | None = None,
    trialed_reverted_symbols: set[str] | None = None,
    baseline_blocked_symbols: set[str] | None = None,
    corrected_translation_units: dict[str, set[str]] | None = None,
) -> dict[str, object]:
    grouped: dict[str, list[Declaration]] = defaultdict(list)
    definitions: dict[str, Definition] = {}
    paths = sorted(
        path
        for path in source_root.rglob("*")
        if path.is_file() and path.suffix in {".c", ".h"}
    )
    AGGREGATE_TYPES.clear()
    for path in paths:
        AGGREGATE_TYPES.update(AGGREGATE_TYPEDEF.findall(path.read_text(encoding="utf-8")))
    for path in paths:
        for declaration in declarations_in(path, source_root):
            grouped[declaration.symbol].append(declaration)
        definition = definition_in(path)
        if definition is not None:
            definitions[definition.symbol] = definition

    # The fan-out gate must also see legacy file-scope prototypes which omit
    # `extern`, notably `M2C_UNK fn_XXXXXXXX();`.  A conservative occurrence
    # index can only hold or raise the gate count.  Exclude the owned definition
    # TU itself so the measure remains caller/declaration fan-out rather than a
    # definition count.
    symbol_translation_units: dict[str, set[str]] = defaultdict(set)
    legacy_unspecified_symbols: set[str] = set()
    for path in (item for item in paths if item.suffix == ".c"):
        relative_path = str(path.relative_to(ROOT))
        text = COMMENTS.sub("", path.read_text(encoding="utf-8"))
        legacy_unspecified_symbols.update(LEGACY_UNSPECIFIED_FUNCTION.findall(text))
        for symbol in set(FUNCTION_NAME.findall(text)):
            definition = definitions.get(symbol)
            if definition is not None and definition.path == relative_path:
                continue
            symbol_translation_units[symbol].add(relative_path)

    retail_evidence = load_retail_evidence(retail_evidence_path)
    ground_truth_by_symbol: dict[str, dict[str, object]] = {
        symbol: {
            "kind": "definition",
            "declaration": definition.signature,
            "return_type": definition.return_type,
            "return_value_kind": return_value_kind(definition.return_type),
            "return_shape": definition.return_shape,
            "parameter_types": list(definition.parameters),
            "parameter_shapes": list(definition.parameter_shapes),
            "variadic": definition.variadic,
            "unspecified_parameters": definition.unspecified_parameters,
            "source": f"{definition.path}:{definition.line}",
        }
        for symbol, definition in definitions.items()
    }
    for symbol, evidence in retail_evidence.items():
        ground_truth_by_symbol.setdefault(symbol, {
            "kind": "retail-epilogue",
            "return_shape": evidence["return_shape"],
            "source": evidence["source"],
            "detail": evidence.get("detail", ""),
        })

    categories: dict[str, list[dict[str, object]]] = {
        "return_register_contradictions": [],
        "abi_divergent": [],
        "cosmetic": [],
    }
    for symbol, declarations in sorted(grouped.items()):
        signatures = Counter(item.signature for item in declarations)
        if len(signatures) < 2:
            continue
        return_shapes = {item.return_shape for item in declarations}
        abi_shapes = {item.abi_shape for item in declarations}
        # `void` versus a value result is still a return-register contradiction:
        # although a void caller simply ignores the physical register, both
        # declarations cannot be the callee's true C signature.  Likewise, two
        # value declarations which select different EABI register files cannot
        # both be correct.  Spellings which select the same register file remain
        # cosmetic and are separated below.
        known_return_shapes = return_shapes - {"unknown"}
        if len(known_return_shapes) > 1:
            category = "return_register_contradictions"
        elif len(abi_shapes) > 1:
            category = "abi_divergent"
        else:
            category = "cosmetic"
        categories[category].append({
            "symbol": symbol,
            "declarations": len(declarations),
            "return_shapes": sorted(return_shapes),
            "variants": [
                {
                    "signature": signature,
                    "count": count,
                    "abi": next(
                        {
                            "return": item.return_shape,
                            "parameters": list(item.abi_shape[1]),
                            "variadic": item.variadic,
                            "unspecified_parameters": item.unspecified_parameters,
                        }
                        for item in declarations if item.signature == signature
                    ),
                    "sites": [
                        f"{item.path}:{item.line}"
                        for item in declarations if item.signature == signature
                    ],
                }
                for signature, count in signatures.most_common()
            ],
        })

    for entries in categories.values():
        entries.sort(key=lambda item: (-int(item["declarations"]), str(item["symbol"])))

    ground_truth_contradictions: list[dict[str, object]] = []
    for symbol, declarations in sorted(grouped.items()):
        definition = definitions.get(symbol)
        truth = ground_truth_by_symbol.get(symbol)
        if truth is None:
            continue
        expected_shape = str(truth["return_shape"])
        disagreeing = [
            item for item in declarations if item.return_shape != expected_shape
        ]
        if not disagreeing:
            continue
        variants = Counter(item.signature for item in disagreeing)
        disagreement_units = sorted({item.path for item in disagreeing})
        translation_units = sorted(
            {item.path for item in declarations} | symbol_translation_units[symbol]
        )
        ground_truth_contradictions.append({
            "symbol": symbol,
            "declarations": len(declarations),
            "ground_truth": truth,
            "disagreeing_declarations": len(disagreeing),
            "disagreement_translation_units": len(disagreement_units),
            "disagreement_units": disagreement_units,
            "affected_translation_units": len(translation_units),
            "translation_units": translation_units,
            "confidence": "high",
            "disposition": "deferred",
            "disposition_reason": (
                "Owned-definition or unambiguous retail evidence establishes a "
                "different PPC EABI signature; the declaration is left unchanged "
                "unless separately listed as an applied correction."
            ),
            "variants": [
                {
                    "signature": signature,
                    "count": count,
                    "parameter_count": next(
                        len(item.parameters)
                        for item in disagreeing if item.signature == signature
                    ),
                    "ground_truth_parameter_count": (
                        len(definition.parameters) if definition is not None else None
                    ),
                    "parameter_arity_matches_ground_truth": (
                        next(
                            len(item.parameters)
                            for item in disagreeing if item.signature == signature
                        ) == len(definition.parameters)
                        if definition is not None else None
                    ),
                    "sites": [
                        f"{item.path}:{item.line}"
                        for item in disagreeing if item.signature == signature
                    ],
                }
                for signature, count in variants.most_common()
            ],
        })
    ground_truth_contradictions.sort(
        key=lambda item: (-int(item["declarations"]), str(item["symbol"]))
    )
    truth_by_symbol = {
        str(item["symbol"]): item["ground_truth"]
        for item in ground_truth_contradictions
    }
    categorized_symbols = {
        str(entry["symbol"])
        for entries in categories.values()
        for entry in entries
    }
    # A symbol can have one consistently wrong extern spelling.  Such a symbol
    # has no declaration-vs-declaration disagreement, but its owned definition
    # or retail evidence still proves a return-register contradiction and must
    # appear in the shadow categories.
    for contradiction in ground_truth_contradictions:
        symbol = str(contradiction["symbol"])
        if symbol in categorized_symbols:
            continue
        declarations = grouped[symbol]
        signatures = Counter(item.signature for item in declarations)
        categories["return_register_contradictions"].append({
            "symbol": symbol,
            "declarations": len(declarations),
            "return_shapes": sorted({item.return_shape for item in declarations}),
            "variants": [
                {
                    "signature": signature,
                    "count": count,
                    "abi": next(
                        {
                            "return": item.return_shape,
                            "parameters": list(item.abi_shape[1]),
                            "variadic": item.variadic,
                            "unspecified_parameters": item.unspecified_parameters,
                        }
                        for item in declarations if item.signature == signature
                    ),
                    "sites": [
                        f"{item.path}:{item.line}"
                        for item in declarations if item.signature == signature
                    ],
                }
                for signature, count in signatures.most_common()
            ],
        })
    for entries in categories.values():
        entries.sort(key=lambda item: (-int(item["declarations"]), str(item["symbol"])))
    applied_symbols = applied_symbols or set()
    trialed_reverted_symbols = trialed_reverted_symbols or set()
    baseline_blocked_symbols = baseline_blocked_symbols or set()
    corrected_translation_units = corrected_translation_units or {}
    for category, entries in categories.items():
        for entry in entries:
            truth = truth_by_symbol.get(str(entry["symbol"]))
            variants = entry["variants"]
            if truth is not None and category == "return_register_contradictions":
                sites = [
                    site
                    for variant in variants
                    if variant["abi"]["return"] != truth["return_shape"]
                    for site in variant["sites"]
                ]
            else:
                sites = [site for variant in variants for site in variant["sites"]]
            disagreement_units = sorted({site.rsplit(":", 1)[0] for site in sites})
            translation_units = sorted(
                {item.path for item in grouped[str(entry["symbol"])]}
                | symbol_translation_units[str(entry["symbol"])]
            )
            entry["affected_translation_units"] = len(translation_units)
            entry["translation_units"] = translation_units
            entry["has_unspecified_parameters"] = (
                str(entry["symbol"]) in legacy_unspecified_symbols
                or any(
                    item.unspecified_parameters
                    for item in grouped[str(entry["symbol"])]
                )
            )
            entry["disagreement_translation_units"] = len(disagreement_units)
            entry["disagreement_units"] = disagreement_units
            entry["confidence"] = "high" if truth is not None else "low"
            wrong_return_variants = [
                variant for variant in variants
                if truth is not None
                and variant["abi"]["return"] != truth["return_shape"]
            ]
            entry["return_only_parameter_abi_matches"] = (
                truth is not None
                and "parameter_shapes" in truth
                and all(
                    variant["abi"]["parameters"] == truth["parameter_shapes"]
                    and variant["abi"]["variadic"] == truth["variadic"]
                    and variant["abi"]["unspecified_parameters"]
                    == truth["unspecified_parameters"]
                    for variant in wrong_return_variants
                )
            )
            entry["callback_or_caller_cast_units"] = sorted({
                site.rsplit(":", 1)[0]
                for variant in wrong_return_variants
                for site in variant["sites"]
                if has_bare_symbol_reference(
                    ROOT / site.rsplit(":", 1)[0], str(entry["symbol"])
                )
            })
            entry["return_type_unavailable_units"] = (
                sorted({
                    site.rsplit(":", 1)[0]
                    for variant in wrong_return_variants
                    for site in variant["sites"]
                    if not return_type_is_available(
                        ROOT / site.rsplit(":", 1)[0],
                        str(truth["return_type"]),
                    )
                }) if truth is not None and "return_type" in truth else []
            )
            entry["evidence"] = (
                [truth]
                if truth is not None
                else [{
                    "kind": "declarations-only",
                    "source": site,
                    "detail": "No owned definition or unambiguous retail return evidence grounds this reading.",
                } for site in sites]
            )
            for variant in entry["variants"]:
                variant["evidence"] = [
                    {"kind": "declaration", "source": site}
                    for site in variant["sites"]
                ]
                if truth is not None:
                    variant["ground_truth"] = truth
            symbol = str(entry["symbol"])
            if symbol in applied_symbols:
                entry["disposition"] = "applied"
                entry["disposition_reason"] = (
                    "Owned-definition return evidence grounds the signature correction. "
                    "The rebuild, objdiff, and DOL gates establish codegen safety and do "
                    "not independently prove the source-level return type."
                )
            elif symbol in baseline_blocked_symbols:
                entry["disposition"] = "blocked_on_baseline"
                entry["disposition_reason"] = (
                    "The grounded correction remains eligible, but every affected "
                    "object must first have a 100-percent baseline. This is a transient "
                    "verification dependency, not a steady-state deferral."
                )
            elif symbol in trialed_reverted_symbols:
                entry["disposition"] = "deferred"
                entry["disposition_reason"] = (
                    "Trialed and reverted in this consolidation session because the "
                    "correction could not satisfy every required verification gate. "
                    "No source correction is retained; reconsideration belongs on the "
                    "signature sweep list."
                )
            else:
                entry["disposition"] = "deferred"
                if truth is None:
                    reason = "Low confidence: declarations alone do not establish the callee's true signature."
                elif len(translation_units) > 12:
                    reason = "High-confidence evidence exists, but the contradiction affects more than 12 translation units."
                elif entry["has_unspecified_parameters"]:
                    reason = (
                        "Deferred because at least one declaring translation unit uses "
                        "an unspecified/K&R prototype."
                    )
                elif not entry["return_only_parameter_abi_matches"]:
                    reason = (
                        "Deferred because at least one wrong-return declaration also "
                        "disagrees with the grounded parameter ABI; a return-only edit "
                        "would not produce a source-complete signature correction."
                    )
                elif entry["callback_or_caller_cast_units"]:
                    reason = (
                        "Deferred because at least one wrong-return declaration is used "
                        "as a callback value or caller-side cast target; the broad APPLY "
                        "trial reproduced incompatible function-pointer diagnostics."
                    )
                elif entry["return_type_unavailable_units"]:
                    reason = (
                        "Deferred because the grounded return-type spelling is unavailable "
                        "in at least one declaring translation unit; the broad APPLY trial "
                        "reproduced unknown-type compiler diagnostics."
                    )
                elif category != "return_register_contradictions":
                    reason = "Deferred because this session is scoped to return-register contradictions."
                else:
                    entry["disposition"] = "pending"
                    reason = (
                        "High-confidence return-register contradiction within the "
                        "12-translation-unit bound. This is eligible unstarted work, not a "
                        "steady-state deferral."
                    )
                entry["disposition_reason"] = reason
    categorized_dispositions = {
        str(entry["symbol"]): (
            str(entry["disposition"]), str(entry["disposition_reason"])
        )
        for entries in categories.values()
        for entry in entries
    }
    for entry in ground_truth_contradictions:
        symbol = str(entry["symbol"])
        categorized = categorized_dispositions.get(symbol)
        if categorized is None:
            affected = int(entry["affected_translation_units"])
            if affected > 12:
                reason = (
                    "High-confidence owned-definition or retail evidence exists, but "
                    "the contradiction affects more than 12 translation units."
                )
            else:
                reason = (
                    "High-confidence owned-definition or retail evidence exists and the "
                    "contradiction is within the 12-translation-unit bound. It remains "
                    "eligible, but was deferred because the bounded consolidation session "
                    "could rebuild and verify only the explicitly selected correction "
                    "before its deadline."
                )
        else:
            entry["disposition"], reason = categorized
        entry["disposition_reason"] = reason
    applied_corrections = []
    for symbol in sorted(applied_symbols):
        definition = definitions.get(symbol)
        declarations = grouped.get(symbol, [])
        edited_translation_units = sorted(
            corrected_translation_units.get(symbol, set())
        )
        if not edited_translation_units:
            raise ValueError(
                f"{symbol}: applied correction lacks explicit corrected translation units"
            )
        declaring_units = {item.path for item in declarations}
        translation_units = sorted(
            declaring_units | symbol_translation_units[symbol]
        )
        unspecified_parameter_units = sorted({
            item.path for item in declarations if item.unspecified_parameters
        } | ({
            path for path in translation_units
            if symbol in legacy_unspecified_symbols
            and re.search(
                rf"(?m)^[ \t]*(?:M2C_UNK|UNK_TYPE)[ \t]+{re.escape(symbol)}"
                rf"[ \t]*\([ \t]*\)[ \t]*;",
                COMMENTS.sub("", (ROOT / path).read_text(encoding="utf-8")),
            )
        }))
        edited_unspecified_units = sorted(
            set(edited_translation_units) & set(unspecified_parameter_units)
        )
        if edited_unspecified_units:
            raise ValueError(
                f"{symbol}: applied correction edits unspecified/K&R prototype "
                f"units {edited_unspecified_units}"
            )
        unknown_units = sorted(set(edited_translation_units) - set(translation_units))
        if unknown_units:
            raise ValueError(
                f"{symbol}: corrected translation units do not declare the symbol "
                f"{unknown_units}"
            )
        if len(translation_units) > 12:
            raise ValueError(
                f"{symbol}: applied correction exceeds the 12-translation-unit "
                f"gate ({len(translation_units)} declaring translation units)"
            )
        applied_corrections.append({
            "symbol": symbol,
            "affected_translation_units": len(translation_units),
            "translation_units": translation_units,
            "edited_translation_units": edited_translation_units,
            "has_unspecified_parameters": bool(unspecified_parameter_units),
            "unspecified_parameter_units": unspecified_parameter_units,
            "edited_translation_units_have_unspecified_parameters": False,
            "prototype_gate_basis": (
                "The unspecified/K&R gate is enforced on edited declarations. "
                "Unedited occurrence-only translation units remain recorded in fan-out."
            ),
            "resulting_signatures": sorted({item.signature for item in declarations}),
            "confidence": "high" if definition is not None else "low",
            "evidence": ({
                "kind": "owned-definition",
                "return_type": definition.return_type,
                "return_shape": definition.return_shape,
                "source": f"{definition.path}:{definition.line}",
            } if definition is not None else None),
            "signature_grounding": (
                "The owned definition grounds the source-level return type."
                if definition is not None
                else "No owned definition grounds the source-level return type."
            ),
            "verification_scope": (
                "Rebuild, objdiff, relocation, and DOL checks establish codegen "
                "safety; they do not independently prove the signature."
            ),
            "disposition": "applied",
        })
    return {
        "source": str(source_root.relative_to(ROOT)),
        "declarations": sum(len(items) for items in grouped.values()),
        "symbols": len(grouped),
        "definitions": len(definitions),
        "ground_truth_by_symbol": ground_truth_by_symbol,
        "retail_evidence_symbols": len(retail_evidence),
        "applied_corrections": applied_corrections,
        "ground_truth_contradictions": ground_truth_contradictions,
        **categories,
    }


def print_report(report: dict[str, object], limit: int | None) -> None:
    print(
        f"Audited {report['declarations']} extern declarations for "
        f"{report['symbols']} symbols under {report['source']}"
    )
    headings = (
        ("ground_truth_contradictions", "GROUND-TRUTH CONTRADICTIONS"),
        ("return_register_contradictions", "RETURN-REGISTER CONTRADICTIONS"),
        ("abi_divergent", "ABI-DIVERGENT DECLARATIONS"),
        ("cosmetic", "COSMETIC DECLARATION DIFFERENCES"),
    )
    for key, heading in headings:
        entries = report[key]
        assert isinstance(entries, list)
        shown = entries if limit is None else entries[:limit]
        print(f"\n{heading}: {len(entries)} symbol(s)")
        for entry in shown:
            print(f"  {entry['symbol']} ({entry['declarations']} declarations)")
            if key == "ground_truth_contradictions":
                truth = entry["ground_truth"]
                print(
                    f"    truth={truth['kind']} return={truth['return_shape']} "
                    f"source={truth['source']}"
                )
            for variant in entry["variants"]:
                if key == "ground_truth_contradictions":
                    sites = ", ".join(variant["sites"][:8])
                    if len(variant["sites"]) > 8:
                        sites += f", ... {len(variant['sites']) - 8} more"
                    print(f"    [{variant['count']}x] {variant['signature']}")
                    print(f"      {sites}")
                    continue
                abi = variant["abi"]
                params = ",".join(abi["parameters"]) or "none"
                suffix = ",variadic" if abi["variadic"] else ""
                if abi["unspecified_parameters"]:
                    suffix += ",unspecified"
                variant_sites = variant["sites"]
                sites = ", ".join(variant_sites[:8])
                if len(variant_sites) > 8:
                    sites += f", ... {len(variant_sites) - 8} more"
                print(
                    f"    [{variant['count']}x; return={abi['return']}; "
                    f"params={params}{suffix}] {variant['signature']}"
                )
                print(f"      {sites}")
        if limit is not None and len(entries) > limit:
            print(f"  ... {len(entries) - limit} more (use --limit 0 to show all)")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=DEFAULT_SOURCE)
    parser.add_argument(
        "--retail-evidence", type=Path, default=DEFAULT_RETAIL_EVIDENCE,
        help="JSON file of manually verified retail callee return shapes",
    )
    parser.add_argument("--json", action="store_true", help="emit machine-readable JSON")
    parser.add_argument(
        "--json-output", type=Path,
        help="write the complete machine-readable report to this path",
    )
    parser.add_argument(
        "--limit", type=int, default=10,
        help="maximum symbols shown per category (0 means unlimited; default: 10)",
    )
    parser.add_argument("--session-id", help="attach consolidation-session metadata")
    parser.add_argument("--starting-target", help="starting chain target")
    parser.add_argument("--ending-next-target", help="unchanged ending chain target")
    parser.add_argument(
        "--applied-symbol", action="append", default=[],
        help="symbol corrected and independently verified in this session",
    )
    parser.add_argument(
        "--trialed-reverted-symbol", action="append", default=[],
        help="symbol trialed and reverted without retained verification evidence",
    )
    parser.add_argument(
        "--baseline-blocked-symbol", action="append", default=[],
        help="eligible symbol blocked only because an affected object lacks a 100-percent baseline",
    )
    parser.add_argument(
        "--correction-evidence", action="append", default=[], metavar="SYMBOL=PATH",
        help="objdiff artifact for an applied correction (repeat per affected object)",
    )
    parser.add_argument(
        "--corrected-translation-unit", action="append", default=[],
        metavar="SYMBOL=PATH",
        help=(
            "source translation unit actually edited for an applied correction "
            "(repeat per affected unit)"
        ),
    )
    parser.add_argument(
        "--evidence-report", type=Path,
        help="report containing verification commands and their raw output",
    )
    parser.add_argument("--dol-sha1", help="verified linked DOL SHA-1")
    parser.add_argument("--build-report", type=Path, help="fresh objdiff report.json")
    parser.add_argument(
        "--verified-object", action="append", default=[],
        help="affected objdiff unit confirmed at 100 percent",
    )
    args = parser.parse_args()
    source = args.source.resolve()
    corrected_translation_units: dict[str, set[str]] = defaultdict(set)
    for value in args.corrected_translation_unit:
        symbol, separator, path = value.partition("=")
        if not separator or not symbol or not path:
            raise ValueError(f"invalid --corrected-translation-unit value {value!r}")
        corrected_translation_units[symbol].add(path)
    report = audit(
        source,
        args.retail_evidence.resolve(),
        set(args.applied_symbol),
        set(args.trialed_reverted_symbol),
        set(args.baseline_blocked_symbol),
        corrected_translation_units,
    )
    evidence_by_symbol: dict[str, list[str]] = defaultdict(list)
    for value in args.correction_evidence:
        symbol, separator, artifact = value.partition("=")
        if not separator or not symbol or not artifact:
            raise ValueError(f"invalid --correction-evidence value {value!r}")
        artifact_path = (ROOT / artifact).resolve()
        if not artifact_path.is_file():
            raise ValueError(f"missing correction evidence artifact {artifact_path}")
        evidence_by_symbol[symbol].append(str(artifact_path.relative_to(ROOT)))
    for correction in report["applied_corrections"]:
        correction["objdiff_artifacts"] = evidence_by_symbol.get(
            str(correction["symbol"]), []
        )
    verified_objects: list[dict[str, object]] = []
    if args.build_report is not None:
        build_report_path = args.build_report.resolve()
        build_report = json.loads(build_report_path.read_text(encoding="utf-8"))
        units = {item["name"]: item for item in build_report.get("units", [])}
        for name in args.verified_object:
            unit = units.get(name)
            if unit is None:
                raise ValueError(f"{build_report_path}: missing verified unit {name}")
            measures = unit.get("measures", {})
            verified_objects.append({
                "name": name,
                "matched_code_percent": measures.get("matched_code_percent"),
                "complete_code_percent": measures.get("complete_code_percent"),
                "complete": unit.get("metadata", {}).get("complete", False),
                "source": str(build_report_path.relative_to(ROOT)),
            })
    verified_by_name = {str(item["name"]): item for item in verified_objects}
    for correction in report["applied_corrections"]:
        artifacts = correction["objdiff_artifacts"]
        if not artifacts:
            raise ValueError(
                f"{correction['symbol']}: applied correction lacks objdiff evidence"
            )
        for artifact in artifacts:
            payload = json.loads((ROOT / artifact).read_text(encoding="utf-8"))
            code_sections = [
                section for section in payload.get("left", {}).get("sections", [])
                if section.get("kind") == "SECTION_CODE"
            ]
            if not code_sections or any(
                section.get("match_percent") != 100.0 for section in code_sections
            ):
                raise ValueError(f"{artifact}: objdiff code is not 100 percent")
        expected_units = {
            "main/" + path.removeprefix("src/").removesuffix(".c")
            for path in correction["edited_translation_units"]
            if path.endswith(".c")
        }
        missing = sorted(expected_units - verified_by_name.keys())
        if missing:
            raise ValueError(
                f"{correction['symbol']}: missing verified affected units {missing}"
            )
        failed = sorted(
            name for name in expected_units
            if not verified_by_name[name]["complete"]
            or verified_by_name[name]["matched_code_percent"] != 100.0
            or verified_by_name[name]["complete_code_percent"] != 100.0
        )
        if failed:
            raise ValueError(
                f"{correction['symbol']}: affected units are not 100 percent {failed}"
            )
    if args.session_id:
        report["session"] = {
            "session_id": args.session_id,
            "starting_target": args.starting_target,
            "ending_next_target": args.ending_next_target,
            "matched_bytes_added": 0,
            "nonmatching_bytes_added": 0,
            "match_counts_revised": False,
            "verification": {
                "build_command": ".tools/bin/ninja",
                "build_status": "passed",
                "dol_sha1": args.dol_sha1,
                "expected_dol_sha1": "ea24b6af954876ce072562ff39cdb4c81d32be1f",
                "dol_byte_change": args.dol_sha1 != "ea24b6af954876ce072562ff39cdb4c81d32be1f",
                "affected_objects_100_percent": verified_objects,
                "evidence_report": (
                    str(args.evidence_report.resolve().relative_to(ROOT))
                    if args.evidence_report is not None else None
                ),
            },
        }
    serialized = json.dumps(report, indent=2) + "\n"
    if args.json_output is not None:
        args.json_output.write_text(serialized, encoding="utf-8")
    if args.json:
        print(serialized, end="")
    else:
        print_report(report, None if args.limit == 0 else args.limit)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
