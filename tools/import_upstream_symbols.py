#!/usr/bin/env python3
"""Import symbol names from the unending-occlusion decomp (CC0).

unending-occlusion (https://github.com/PattyTrish/unending-occlusion) targets the
same GEDE01 rev 0 DOL, and its symbols.txt shares this project's address map.
This tool renames our auto-generated fn_XXXXXXXX / lbl_XXXXXXXX symbols to
upstream's names wherever both sides agree on the address and symbol type, then
rewrites every whole-word reference in the source tree, configure.py and tools.

Names are only imported when they are safe as C identifiers: no conflicts with
names we already use, no duplicates, no compiler intrinsics, and no clash with
any identifier already present in a file that references the symbol.

Usage:
    python3 tools/import_upstream_symbols.py --upstream path/to/upstream/symbols.txt [--dry-run]

Writes docs/upstream-symbol-map.csv (old name, new name, address, type) so the
old addresses stay searchable.
"""

import argparse
import csv
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SYMBOLS = ROOT / "config/GEDE01/symbols.txt"
MAP_OUT = ROOT / "docs/upstream-symbol-map.csv"

LINE_RE = re.compile(r"^(\S+) = (\S+):0x([0-9A-Fa-f]+); // (.*)$")
AUTO_RE = re.compile(r"^(fn|lbl)_8[0-9A-F]{7}$")
IDENT_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
WORD_RE = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")
COMMENT_RE = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
# Hand-written aliases such as "#define ResetNotes fn_801B244C".
ALIAS_RE = re.compile(r"^[ \t]*#define[ \t]+(\w+)[ \t]+((?:fn|lbl)_8[0-9A-F]{7})[ \t]*(?:/\*.*?\*/|//.*)?\n", re.M)

# Names MWCC may treat as intrinsics or that C reserves; renaming a call to one
# of these could change codegen, so they are never imported.
RESERVED = {
    "abs", "labs", "fabs", "fabsf", "__abs", "__labs", "__fabs", "__fabsf",
    "__fnabs", "__fnabsf", "memcpy", "memset", "memcmp", "strlen", "strcpy",
    "strcmp", "alloca", "__alloca", "sqrt", "sqrtf", "__frsqrte", "__fres",
    "__fsel", "__cntlzw", "__lhbrx", "__lwbrx", "__sthbrx", "__stwbrx",
    "__rlwinm", "__rlwimi", "__mftb", "__sync", "__eieio", "__isync",
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
    "while", "asm", "main",
}

# Where symbol names are referenced.
REWRITE_GLOBS = [
    "src/**/*.c", "src/**/*.cpp", "src/**/*.h", "src/**/*.s",
    "include/**/*.h", "include/**/*.inc", "tools/*.py", "tools/*.sh",
    "configure.py", "config/GEDE01/*.txt", "config/GEDE01/*.yml",
    "config/GEDE01/*.json", "docs/*.md",
]
SKIP_FILES = {Path(__file__).resolve()}


def load(path):
    entries = []
    for line in path.read_text().splitlines():
        m = LINE_RE.match(line.strip())
        if not m:
            entries.append((line, None))
            continue
        name, sec, addr, meta = m.groups()
        t = re.search(r"type:(\w+)", meta)
        entries.append((line, (name, int(addr, 16), t.group(1) if t else "?")))
    return entries


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--upstream", type=Path, required=True)
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    mine = load(SYMBOLS)
    upstream = {}
    for _, e in load(args.upstream):
        if e:
            upstream.setdefault((e[1], e[2]), e[0])

    used_names = {e[0] for _, e in mine if e}
    upstream_counts = {}
    for n in upstream.values():
        upstream_counts[n] = upstream_counts.get(n, 0) + 1

    candidates = {}
    skipped = {}
    for _, e in mine:
        if not e or not AUTO_RE.match(e[0]):
            continue
        new = upstream.get((e[1], e[2]))
        if not new or AUTO_RE.match(new) or new.startswith(("fn_", "lbl_")):
            continue
        if not IDENT_RE.match(new):
            skipped[e[0]] = (new, "not a C identifier")
        elif new in RESERVED:
            skipped[e[0]] = (new, "reserved/intrinsic")
        elif new in used_names:
            skipped[e[0]] = (new, "name already used here")
        elif upstream_counts[new] > 1:
            skipped[e[0]] = (new, "duplicate upstream name")
        else:
            candidates[e[0]] = (new, e[1], e[2])

    files = sorted({p for g in REWRITE_GLOBS for p in ROOT.glob(g)
                    if p.is_file() and p.resolve() not in SKIP_FILES})
    texts = {p: p.read_text(errors="surrogateescape") for p in files}

    # Drop any name that already appears as an identifier in a file that
    # references the symbol being renamed (local variables, struct fields...).
    # C comments are ignored; docs and config data are not compiled.
    for p, text in texts.items():
        if p.suffix in (".md", ".txt", ".json", ".yml"):
            continue
        # Uses of a hand-written alias already mean the symbol itself.
        aliased = set()
        if p.suffix in (".c", ".cpp", ".h"):
            for m in ALIAS_RE.finditer(text):
                if candidates.get(m.group(2), (None,))[0] == m.group(1):
                    aliased.add(m.group(2))
            text = COMMENT_RE.sub(" ", text)
        words = set(WORD_RE.findall(text))
        for old in (words & candidates.keys()) - aliased:
            new = candidates[old][0]
            if new in words:
                skipped[old] = (new, f"identifier clash in {p.relative_to(ROOT)}")
                del candidates[old]

    rename = {old: v[0] for old, v in candidates.items()}
    pattern = re.compile(r"\b(?:fn|lbl)_8[0-9A-F]{7}\b")
    changed = 0
    for p, text in texts.items():
        if p.suffix in (".c", ".cpp", ".h"):
            # An alias of a symbol to its own upstream name is now redundant.
            text_in = text
            text = ALIAS_RE.sub(
                lambda m: "" if rename.get(m.group(2)) == m.group(1) else m.group(0), text)
            if text != text_in and not args.dry_run:
                p.write_text(text, errors="surrogateescape")
        new_text = pattern.sub(lambda m: rename.get(m.group(0), m.group(0)), text)
        if new_text != text:
            changed += 1
            if not args.dry_run:
                p.write_text(new_text, errors="surrogateescape")

    fns = sum(1 for v in candidates.values() if v[2] == "function")
    print(f"renamed {len(rename)} symbols ({fns} functions, {len(rename) - fns} data) "
          f"across {changed} files; skipped {len(skipped)}")
    reasons = {}
    for old, (new, why) in sorted(skipped.items()):
        key = why.split(" in ")[0]
        reasons[key] = reasons.get(key, 0) + 1
    for why, n in sorted(reasons.items(), key=lambda x: -x[1]):
        print(f"  skipped {n:5d}: {why}")
    for old, (new, why) in sorted(skipped.items()):
        if "clash" in why or "used" in why:
            print(f"    {old} -> {new}: {why}")

    if not args.dry_run:
        with MAP_OUT.open("w", newline="") as f:
            w = csv.writer(f)
            w.writerow(["old_name", "new_name", "address", "type"])
            for old, (new, addr, typ) in sorted(candidates.items(), key=lambda x: x[1][1]):
                w.writerow([old, new, f"0x{addr:08X}", typ])


if __name__ == "__main__":
    main()
