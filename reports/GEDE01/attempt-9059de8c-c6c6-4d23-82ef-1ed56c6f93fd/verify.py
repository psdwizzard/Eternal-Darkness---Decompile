#!/usr/bin/env python3
"""Run from eternal-darkness-decomp after restoring the retained source."""
import difflib, hashlib, json, shlex, subprocess
from pathlib import Path
OUT = Path("reports/GEDE01/attempt-9059de8c-c6c6-4d23-82ef-1ed56c6f93fd")
REPORT = Path("reports/GEDE01/objdiff-9059de8c-c6c6-4d23-82ef-1ed56c6f93fd.json")
EXPECTED = "ea24b6af954876ce072562ff39cdb4c81d32be1f"
commands = []
def run(args, name, allowed=(0,)):
    proc = subprocess.run(args, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    (OUT / name).write_text(proc.stdout)
    commands.append({"argv": args, "cwd": "eternal-darkness-decomp", "exit": proc.returncode, "raw_output": str(OUT / name)})
    (OUT / "verification-commands.json").write_text(json.dumps(commands, indent=2) + "\n")
    if proc.returncode not in allowed:
        raise RuntimeError(shlex.join(args) + " failed: " + proc.stdout)
    return proc.stdout

run(["python3", "configure.py"], "final-configure.log")
run([".tools/bin/ninja", "-j2"], "final-build.log")
run([".tools/bin/ninja", "-t", "commands", "build/GEDE01/src/game/game_fn_801A36C0.o"], "canonical-compiler-command.log")
base = ["build/tools/objdiff-cli", "diff", "-p", ".", "-u", "main/game/game_fn_801A36C0", "fn_801A36C0", "--format", "json-pretty"]
canonical = OUT / "final-canonical.json"
run(base + ["-o", str(canonical)], "final-canonical.log")
run(base + ["-o", str(REPORT), "-c", "function_reloc_diffs=name_address"], "final-strict.log")
raw_retail = run(["readelf", "-Wr", "build/GEDE01/obj/game/game_fn_801A36C0.o"], "retail-readelf.txt")
raw_generated = run(["readelf", "-Wr", "build/GEDE01/src/game/game_fn_801A36C0.o"], "generated-readelf.txt")
def normalize(raw):
    records = []
    for line in raw.splitlines():
        parts = line.split()
        if len(parts) >= 7 and parts[2].startswith("R_PPC_"):
            # Ignore the ELF symbol-table index, but retain offset, relocation
            # type, symbol value, symbol name, addend sign, and addend value.
            records.append(" ".join([parts[0], parts[2]] + parts[3:]))
    return "\n".join(records) + "\n"
a, b = normalize(raw_retail), normalize(raw_generated)
(OUT / "retail-relocations.normalized.txt").write_text(a)
(OUT / "generated-relocations.normalized.txt").write_text(b)
run(["diff", "-u", str(OUT / "retail-relocations.normalized.txt"), str(OUT / "generated-relocations.normalized.txt")], "relocations.diff")
assert len(a.splitlines()) == len(b.splitlines()) == 25
sha_output = run(["sha1sum", "build/GEDE01/main.dol"], "dol-sha1.txt")
assert sha_output.split()[0] == EXPECTED
run(["python3", "tools/legal_audit.py"], "legal-audit.txt")

def symbol(data, side):
    return next(s for s in data[side]["symbols"] if s["name"] == "fn_801A36C0")
measurements = {}
for label, path in [("canonical", canonical), ("relocation_strict", REPORT)]:
    data = json.loads(path.read_text())
    left, right = symbol(data, "left"), symbol(data, "right")
    measurements[label] = {"retail_bytes": int(left["size"]), "generated_bytes": int(right["size"]), "retail_instructions": len(left["instructions"]), "generated_instructions": len(right["instructions"]), "match_percent": left["match_percent"], "differing_rows": sum(x.get("diff_kind") not in (None, "DIFF_NONE") for x in left["instructions"])}
    if label == "relocation_strict":
        rows = []
        for i, (x, y) in enumerate(zip(left["instructions"], right["instructions"])):
            ai, bi = x.get("instruction", {}), y.get("instruction", {})
            rows.append(f"{i*4:04x} {x.get('diff_kind', ''):20} {ai.get('formatted', ''):48} | {bi.get('formatted', '')}")
        (OUT / "final-instruction-comparison.txt").write_text("\n".join(rows) + "\n")
        differences = [{"offset": hex(i*4), "kind": x.get("diff_kind"), "retail": x["instruction"]["formatted"], "generated": y["instruction"]["formatted"]} for i, (x, y) in enumerate(zip(left["instructions"], right["instructions"])) if x.get("diff_kind") not in (None, "DIFF_NONE")]
        (OUT / "final-differences.json").write_text(json.dumps(differences, indent=2) + "\n")
        assert all(x["kind"] == "DIFF_ARG_MISMATCH" for x in differences)
measurements.update({"dol_sha1": sha_output.split()[0], "retail_relocations": len(a.splitlines()), "generated_relocations": len(b.splitlines()), "relocations_equal": a == b, "registration": "NonMatching", "dol_uses": "retail fallback for this NonMatching function; DOL equality does not certify the C candidate"})
(OUT / "verification.json").write_text(json.dumps(measurements, indent=2) + "\n")
print(json.dumps(measurements, indent=2))
