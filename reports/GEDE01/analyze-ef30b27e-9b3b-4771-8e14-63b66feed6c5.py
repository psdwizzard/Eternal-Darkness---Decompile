"""Summarize saved objdiff and inspect current target/generated ELF relocations."""
import collections
import json
from pathlib import Path
import re
import subprocess

ASSIGNMENT = "ef30b27e-9b3b-4771-8e14-63b66feed6c5"
REPORTS = Path(__file__).resolve().parent
ROOT = REPORTS.parents[1]

def symbol(data, side):
    return next(s for s in data[side]["symbols"] if s["name"] == "fn_80023258")

data = {}
for tag in ["baseline", "trial-inline", "objdiff", "objdiff-strict"]:
    d = json.loads((REPORTS / f"{tag}-{ASSIGNMENT}.json").read_text())
    data[tag] = d
    left, right = symbol(d, "left"), symbol(d, "right")
    counts = collections.Counter(r.get("diff_kind", "DIFF_NONE") for r in left["instructions"])
    print(tag, json.dumps({"retail_size": left["size"], "generated_size": right["size"],
                          "match_percent": left["match_percent"], "diff_kinds": counts}))
def relative_instructions(d):
    sym = symbol(d, "right")
    base = int(sym.get("address", 0))
    result = []
    for row in sym["instructions"]:
        ins = row.get("instruction", {})
        formatted = ins.get("formatted", "")
        if "branch_dest" in ins:
            formatted = formatted.split(" ")[0] + " " + str(int(ins["branch_dest"]) - base)
        reloc = ins.get("relocation", {})
        result.append((formatted, reloc.get("type"), reloc.get("addend", "0")))
    return result
print("trial_relative_instructions_equal_baseline", relative_instructions(data["trial-inline"]) == relative_instructions(data["baseline"]))
print("trial_emitted_symbols", [(s["name"], s.get("size")) for s in data["trial-inline"]["right"]["symbols"]])
print("retained_generated_json_equals_baseline", data["objdiff-strict"]["right"] == data["baseline"]["right"])

relocations = []
for side in ["obj", "src"]:
    cmd = ["build/binutils/powerpc-eabi-readelf", "-rW", f"build/GEDE01/{side}/game/game_fn_80023258.o"]
    raw = subprocess.check_output(cmd, cwd=ROOT, text=True)
    entries = []
    for line in raw.splitlines():
        fields = line.split()
        if len(fields) >= 7 and re.fullmatch(r"[0-9a-f]{8}", fields[0]) and fields[2].startswith("R_PPC_"):
            entries.append((fields[0], fields[2], fields[4], " ".join(fields[5:])))
    relocations.append(entries)
    print(side, "real_relocation_count", len(entries))
print("ordered_type_target_addend_equal", [r[1:] for r in relocations[0]] == [r[1:] for r in relocations[1]])
print("relocation_offsets_equal", [r[0] for r in relocations[0]] == [r[0] for r in relocations[1]])
print("all_addends_zero", all(r[3] == "+ 0" for seq in relocations for r in seq))

left, right = symbol(data["objdiff-strict"], "left"), symbol(data["objdiff-strict"], "right")
print("Aligned differences (addresses are actual instruction addresses, not alignment-row indices):")
for l, r in zip(left["instructions"], right["instructions"]):
    if l.get("diff_kind", "DIFF_NONE") != "DIFF_NONE":
        li, ri = l.get("instruction", {}), r.get("instruction", {})
        print(json.dumps({"kind": l.get("diff_kind"), "retail": [li.get("address", "0"), li.get("formatted")],
                          "generated": [ri.get("address", "0"), ri.get("formatted")]}))
