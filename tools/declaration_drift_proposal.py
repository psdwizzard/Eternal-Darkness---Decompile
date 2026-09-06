#!/usr/bin/env python3
"""Generate a reproducible, call-site-aware declaration-drift proposal.

The proposal is measured against an immutable git snapshot so an applied source
correction does not erase the evidence which justified it.  ``--facts`` emits
the exact machine-generated evidence stream.  A subsequent generation run must
receive that captured stream with ``--facts-log``; it reruns the measurement and
refuses to write a report if the bytes differ.
"""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import tarfile
import tempfile
from collections import Counter, defaultdict
from pathlib import Path

import signature_audit


ROOT = Path(__file__).resolve().parents[1]
REPO = ROOT.parent
EXTERN_STATEMENT = re.compile(r"\bextern\b.*?;", re.DOTALL)
COMMENTS = re.compile(r"/\*.*?\*/|//[^\n]*", re.DOTALL)
TOP_SYMBOLS = 10


def resolve_proposed_variant(
    symbol: str,
    variants: list[dict[str, object]],
    truth: dict[str, object] | None,
) -> dict[str, object]:
    """Resolve a declaration only when the available evidence supports it."""
    if truth is not None and truth.get("kind") == "definition":
        candidates = [
            variant
            for variant in variants
            if variant["signature"] == truth["declaration"]
        ]
        if not candidates:
            # The owned definition remains the high-confidence reading even
            # when every caller declaration is wrong.  Keep it as a synthetic
            # zero-site candidate so the proposal records the actual reading
            # instead of inventing a third confidence state.
            return {
                "signature": truth["declaration"],
                "count": 0,
                "sites": [],
                "abi": {"return": truth["return_shape"]},
            }
        return candidates[0]
    if truth is not None:
        candidates = [
            variant
            for variant in variants
            if variant["abi"]["return"] == truth["return_shape"]
        ]
        if not candidates:
            # A retail epilogue can establish the result-register shape without
            # establishing any source-level parameter list.  Preserve exactly
            # that partial reading instead of leaking max()'s ValueError into a
            # third confidence state.
            return {
                "signature": None,
                "count": 0,
                "sites": [],
                "abi": {"return": truth["return_shape"]},
            }
        return max(candidates, key=lambda item: int(item["count"]))
    return max(variants, key=lambda item: int(item["count"]))


def snapshot(ref: str) -> tempfile.TemporaryDirectory[str]:
    temporary = tempfile.TemporaryDirectory(
        prefix="declaration-drift-", dir=ROOT / "build"
    )
    archive_path = Path(temporary.name) / "snapshot.tar"
    with archive_path.open("wb") as archive:
        subprocess.run(
            [
                "git", "archive", ref,
                "eternal-darkness-decomp/src/game",
                "eternal-darkness-decomp/config/GEDE01/retail-return-shapes.json",
            ],
            cwd=REPO,
            stdout=archive,
            check=True,
        )
    with tarfile.open(archive_path) as archive:
        archive.extractall(temporary.name, filter="data")
    return temporary


def call_sites(path: Path, symbol: str, display_path: str) -> list[str]:
    original = path.read_text(encoding="utf-8")
    text = COMMENTS.sub(lambda match: "\n" * match.group(0).count("\n"), original)
    text = EXTERN_STATEMENT.sub(
        lambda match: "\n" * match.group(0).count("\n"), text
    )
    pattern = re.compile(rf"\b{re.escape(symbol)}\s*\(")
    return [
        f"{display_path}:{text.count(chr(10), 0, match.start()) + 1}"
        for match in pattern.finditer(text)
        if not text[text.rfind("\n", 0, match.start()) + 1:match.start()].lstrip().startswith("#")
    ]


def collect(ref: str) -> dict[str, object]:
    with snapshot(ref) as temporary:
        snapshot_root = Path(temporary) / "eternal-darkness-decomp"
        source_root = snapshot_root / "src/game"
        retail_path = snapshot_root / "config/GEDE01/retail-return-shapes.json"

        old_root = signature_audit.ROOT
        signature_audit.ROOT = snapshot_root
        try:
            audit = signature_audit.audit(source_root, retail_path)
        finally:
            signature_audit.ROOT = old_root

        entries = list(audit["return_register_contradictions"])
        entries.extend(audit["abi_divergent"])
        entries.sort(key=lambda item: (-int(item["declarations"]), str(item["symbol"])))
        selected = entries[:TOP_SYMBOLS]
        # The ranked drift list includes parameter-only disagreements.  Those
        # do not appear in ground_truth_contradictions when every declaration
        # uses the definition's return register, so consume the audit's full
        # owned-definition/retail index rather than its return-conflict subset.
        truths = audit["ground_truth_by_symbol"]
        result_symbols: list[dict[str, object]] = []
        for rank, entry in enumerate(selected, 1):
            symbol = str(entry["symbol"])
            variants = list(entry["variants"])
            truth = truths.get(symbol)
            proposed = resolve_proposed_variant(symbol, variants, truth)

            disagreeing_sites = sorted({
                site
                for variant in variants
                if variant["signature"] != proposed["signature"]
                for site in variant["sites"]
            })
            disagreeing_tus = sorted({site.rsplit(":", 1)[0] for site in disagreeing_sites})
            all_tus = sorted({
                site.rsplit(":", 1)[0]
                for variant in variants
                for site in variant["sites"]
            })
            calls_by_tu: dict[str, list[str]] = defaultdict(list)
            for relative in all_tus:
                calls_by_tu[relative].extend(
                    call_sites(source_root.parent.parent / relative, symbol, relative)
                )
            proposed_calls = sorted({
                call for tu in all_tus for call in calls_by_tu.get(tu, [])
            })
            variant_rows = []
            for variant in variants:
                tus = sorted({site.rsplit(":", 1)[0] for site in variant["sites"]})
                variant_rows.append({
                    "declaration": variant["signature"],
                    "count": variant["count"],
                    "declaring_tu_count": len(tus),
                    "declaration_sites": variant["sites"],
                    "call_site_evidence": sorted(
                        call for tu in tus for call in calls_by_tu.get(tu, [])
                    ),
                })
            if truth is not None and truth.get("kind") == "definition":
                confidence_by_component = {
                    "return_shape": "high",
                    "parameters": "high",
                }
                basis = {
                    "return_shape": truth,
                    "parameters": truth,
                }
            elif truth is not None:
                confidence_by_component = {
                    "return_shape": "high",
                    "parameters": "low",
                }
                basis = {
                    "return_shape": truth,
                    "parameters": {
                        "kind": "declaration-plurality",
                        "detail": (
                            "The retail epilogue does not establish parameters. "
                            "Any displayed declaration uses only the plurality among "
                            "variants with the grounded return-register shape and must "
                            "not be canonicalized without independent parameter evidence."
                        ),
                    },
                }
            else:
                confidence_by_component = {
                    "return_shape": "low",
                    "parameters": "low",
                }
                plurality_basis = {
                    "kind": "declaration-plurality",
                    "detail": "Plurality is tentative; declarations alone do not ground the callee signature.",
                }
                basis = {
                    "return_shape": plurality_basis,
                    "parameters": plurality_basis,
                }
            believed_correct_reading = {
                "status": (
                    "resolved" if proposed["signature"] is not None
                    else "return-shape-only"
                ),
                "declaration": proposed["signature"],
                "return_shape": proposed["abi"]["return"],
                "call_site_evidence": proposed_calls,
                "basis": basis,
                "confidence_rationale": (
                    "High confidence: an owned function definition grounds both the "
                    "return-register shape and parameter ABI."
                    if truth is not None and truth.get("kind") == "definition"
                    else (
                        "Low overall confidence: retail epilogue evidence grounds only "
                        "the return-register shape; the parameter reading remains ungrounded."
                        if truth is not None
                        else "Low confidence: declaration plurality and call sites do not ground the callee ABI."
                    )
                ),
            }
            confidence = (
                "high"
                if set(confidence_by_component.values()) == {"high"}
                else "low"
            )
            result_symbols.append({
                "rank": rank,
                "symbol": symbol,
                "category": next(
                    category for category in (
                        "return_register_contradictions", "abi_divergent", "cosmetic"
                    ) if entry in audit[category]
                ),
                "declaration_count": entry["declarations"],
                "total_affected_tu_count": int(entry["affected_translation_units"]),
                "affected_translation_units": list(entry["translation_units"]),
                "confidence": confidence,
                "confidence_by_component": confidence_by_component,
                "competing_declarations": variant_rows,
                "believed_correct_reading": believed_correct_reading,
                "estimated_blast_radius_tus": len(disagreeing_tus),
                "disagreeing_translation_units": disagreeing_tus,
                "disagreeing_declaration_sites": disagreeing_sites,
            })
        return {
            "baseline_ref": ref,
            "audited_declarations": audit["declarations"],
            "audited_symbols": audit["symbols"],
            "selected_symbols": result_symbols,
        }


def facts_text(measurement: dict[str, object]) -> str:
    lines = [
        f"AUDIT declarations={measurement['audited_declarations']} symbols={measurement['audited_symbols']}"
    ]
    for item in measurement["selected_symbols"]:
        lines.append(
            "SYMBOL "
            f"rank={item['rank']} name={item['symbol']} "
            f"declarations={item['declaration_count']} "
            f"affected_tus={item['total_affected_tu_count']} "
            f"blast_radius_tus={item['estimated_blast_radius_tus']} "
            f"confidence={item['confidence']} "
            f"resolution={item['believed_correct_reading']['status']}"
        )
        for variant in item["competing_declarations"]:
            lines.append(
                f"VARIANT name={item['symbol']} declaration={json.dumps(variant['declaration'])} "
                f"declarations={variant['count']} "
                f"declaring_tus={variant['declaring_tu_count']} "
                f"call_sites={len(variant['call_site_evidence'])}"
            )
        for site in item["disagreeing_translation_units"]:
            lines.append(f"DISAGREEING_TU name={item['symbol']} path={site}")
        lines.append(
            f"CONFIDENCE name={item['symbol']} "
            f"return_shape={item['confidence_by_component']['return_shape']} "
            f"parameters={item['confidence_by_component']['parameters']}"
        )
        for site in item["believed_correct_reading"]["call_site_evidence"]:
            lines.append(f"BELIEVED_CALL name={item['symbol']} site={site}")
    return "\n".join(lines) + "\n"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--baseline-ref", required=True)
    parser.add_argument("--facts", action="store_true")
    parser.add_argument("--facts-output", type=Path)
    parser.add_argument("--facts-log", type=Path)
    parser.add_argument("--verification-log", type=Path)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--session-id")
    parser.add_argument("--starting-target")
    parser.add_argument("--ending-next-target")
    parser.add_argument("--applied-symbol", action="append", default=[])
    parser.add_argument("--tested-reverted-symbol", action="append", default=[])
    parser.add_argument(
        "--inherited-tested-reverted-symbol", action="append", default=[]
    )
    args = parser.parse_args()

    measurement = collect(args.baseline_ref)
    raw_facts = facts_text(measurement)
    if args.facts:
        if args.facts_output is not None:
            args.facts_output.write_text(raw_facts, encoding="utf-8")
        else:
            print(raw_facts, end="")
        return 0
    if args.output is None or args.facts_log is None or args.verification_log is None:
        parser.error("generation requires --output, --facts-log, and --verification-log")
    if args.session_id is None or args.starting_target is None or args.ending_next_target is None:
        parser.error(
            "generation requires --session-id, --starting-target, and --ending-next-target"
        )
    recorded_facts = args.facts_log.read_text(encoding="utf-8")
    if recorded_facts != raw_facts:
        raise ValueError("facts log does not match a fresh measurement")

    applied = set(args.applied_symbol)
    tested_reverted = set(args.tested_reverted_symbol)
    inherited_tested_reverted = set(args.inherited_tested_reverted_symbol)
    for item in measurement["selected_symbols"]:
        if item["symbol"] in applied:
            item["disposition"] = "applied"
            item["disposition_reason"] = (
                "High-confidence return correction was within the TU cap and passed rebuild, affected-object objdiff, relocation, and DOL gates."
            )
        elif item["symbol"] in tested_reverted:
            item["disposition"] = "tested-and-reverted"
            item["disposition_reason"] = (
                "The bounded rewrite of only the disagreeing declarations was tested, "
                "but it broke an existing exact object and the build; the declarations "
                "were restored. For this symbol, the failed bounded trial is evidence that "
                "the total declaring-TU set remains the conservative integration scope. "
                "The verification report records the trial and restored gates."
            )
        elif item["symbol"] in inherited_tested_reverted:
            item["disposition"] = "proposal-only"
            item["disposition_reason"] = (
                "Proposal only: inherited evidence records that this exact candidate "
                "regressed an affected object and was reverted; no rewrite was repeated "
                f"in {args.session_id}."
            )
        elif item["confidence"] == "low":
            item["disposition"] = "proposal-only"
            item["disposition_reason"] = (
                "Low confidence: declarations and their call sites do not establish the callee signature."
            )
        elif int(item["estimated_blast_radius_tus"]) > 12:
            item["disposition"] = "proposal-only"
            item["disposition_reason"] = (
                "Proposal only: the high-confidence candidate has a measured blast radius of "
                f"{item['estimated_blast_radius_tus']} TUs, exceeding the 12-TU rewrite ceiling."
            )
        else:
            item["disposition"] = "proposal-only"
            item["disposition_reason"] = "High-confidence candidate was not applied."
        item["measurement_evidence_ref"] = "measurement_evidence"

    disposition_args = " ".join(
        [f"--applied-symbol {symbol}" for symbol in args.applied_symbol]
        + [
            f"--tested-reverted-symbol {symbol}"
            for symbol in args.tested_reverted_symbol
        ]
        + [
            f"--inherited-tested-reverted-symbol {symbol}"
            for symbol in args.inherited_tested_reverted_symbol
        ]
    )
    if disposition_args:
        disposition_args += " "
    source_diff_command = [
        "git", "diff", "--name-only", "HEAD", "--", "eternal-darkness-decomp/src"
    ]
    source_diff = subprocess.run(
        source_diff_command,
        cwd=REPO,
        check=True,
        capture_output=True,
        text=True,
    ).stdout
    source_rewrites = len(source_diff.splitlines())
    if source_rewrites != len(applied):
        raise ValueError(
            "applied-symbol arguments do not equal the measured source rewrite count"
        )
    report = {
        "schema_version": 2,
        "report_kind": "declaration-drift-reduction-proposal",
        "generated_by": "tools/declaration_drift_proposal.py",
        "generation_command": (
            f"python3 tools/declaration_drift_proposal.py --baseline-ref {args.baseline_ref} "
            f"--facts-log {args.facts_log} --verification-log {args.verification_log} "
            f"--session-id {args.session_id} --starting-target {args.starting_target} "
            f"--ending-next-target {args.ending_next_target} {disposition_args}"
            f"--output {args.output}"
        ),
        "session": {
            "session_id": args.session_id,
            "starting_target": args.starting_target,
            "ending_next_target": args.ending_next_target,
            "frontier_changed": False,
            "matched_bytes_added": 0,
            "nonmatching_bytes_added": 0,
            "match_counts_revised": False,
        },
        "selection_rule": (
            "Combine return-register contradictions and ABI-divergent parameter declarations, then rank by total declaration count descending and symbol ascending. "
            "Exclude cosmetic disagreements because the audit proves their return and parameter ABI shapes are equivalent. "
            "The rewrite blast radius is the set of TUs whose declaration disagrees with the grounded reading; total declaring TUs are reported separately as context."
        ),
        "rewrite_tu_cap": 12,
        "measurement_evidence": {
            "command": f"python3 tools/declaration_drift_proposal.py --baseline-ref {args.baseline_ref} --facts",
            "raw_output": recorded_facts,
        },
        "verification_evidence": {
            "report": str(args.verification_log),
            "detail": (
                "Verification is stored separately so the final validator output can be "
                "recorded without embedding a stale, pre-validation copy here."
            ),
        },
        "proposal_summary": {
            "source_rewrites_applied": source_rewrites,
            "measurement_evidence": {
                "command": " ".join(source_diff_command),
                "raw_output": source_diff,
            },
        },
        "rewrite_gate": {
            "rule": "Apply a high-confidence correction only when its disagreeing-TU rewrite set is at most the configured cap and all build, affected-object, relocation, and DOL gates pass.",
            "tested_reverted_symbols": sorted(tested_reverted),
        },
        "symbols": measurement["selected_symbols"],
    }
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
