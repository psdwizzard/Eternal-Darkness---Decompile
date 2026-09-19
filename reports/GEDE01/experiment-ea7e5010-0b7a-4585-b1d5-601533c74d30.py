#!/usr/bin/env python3
"""Reproduce this assignment's source variants and preserve raw command outputs."""
import hashlib
import json
import subprocess
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
AID = "ea7e5010-0b7a-4585-b1d5-601533c74d30"
REPORT = ROOT / "reports/GEDE01" / ("objdiff-" + AID + ".json")
SOURCE = ROOT / "src/game/game_fn_80183F70.c"
BASE = SOURCE.read_text()
data = {"version": 1, "assignment_id": AID, "target": "fn_80183F70", "baseline_source": BASE, "commands": [], "experiments": []}
def save():
    REPORT.write_text(json.dumps(data, indent=2) + "\n")
def run(args, sink=None):
    r = subprocess.run(args, cwd=ROOT, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    entry = {"argv": args, "cwd": "eternal-darkness-decomp", "exit_code": r.returncode, "stdout": r.stdout, "stderr": r.stderr}
    (data["commands"] if sink is None else sink).append(entry)
    save()
    print("exit", r.returncode, " ".join(args), flush=True)
    if r.returncode: raise RuntimeError(entry)
    return r

def compare(label, commands):
    result = {}
    for mode in ["canonical", "strict"]:
        output = "reports/GEDE01/objdiff-" + AID + "-" + label + "-" + mode + ".json"
        args = ["build/tools/objdiff-cli", "diff", "-p", ".", "-u", "main/game/game_fn_80183F70", "fn_80183F70", "-o", output, "--format", "json-pretty"]
        if mode == "strict": args += ["-c", "function_reloc_diffs=name_address"]
        run(args, commands)
        result[mode] = json.loads((ROOT/output).read_text())
        (ROOT/output).unlink()
    return result

try:
    run(["python3", "configure.py"])
    run([".tools/bin/ninja", "-j2"])
    data["baseline_comparisons"] = compare("baseline", data["commands"])
    save()
    variants = []
    aggregate = BASE.replace("    register u8* desc_local = desc;\n    register u8* self_local = self;\n    SixBytes setup;\n    register u8* entry;", "    struct { u8* desc; u8* self; u8* entry; } state;\n    SixBytes setup;\n    state.desc = desc;\n    state.self = self;")
    import re
    for old, new in [("desc_local", "state.desc"), ("self_local", "state.self"), ("entry", "state.entry")]:
        if old == "entry":
            before, after = aggregate.split("    (void)desc;", 1)
            aggregate = before + "    (void)desc;" + re.sub(r"\bentry\b", new, after)
        else: aggregate = re.sub(r"\b" + old + r"\b", new, aggregate)
    variants.append(("pointer_aggregate", "A local aggregate of the three pointer values may change scalar-replacement virtual-register creation and nonvolatile coloring; unlike prior experiments this does not change the pointee layouts.", aggregate))
    early = BASE.replace("    if (*(s16*)(desc_local + 4) >= 0) {\n        fn_801F5A04(self_local + 0x6C, *(s16*)(desc_local + 4), lbl_80606328,\n                    lbl_80606318);\n    }", "    if (*(s16*)(desc_local + 4) < 0) {\n        return;\n    }\n    fn_801F5A04(self_local + 0x6C, *(s16*)(desc_local + 4), lbl_80606328,\n                lbl_80606318);")
    variants.append(("early_return", "Invert the final conditional into an early return to alter CFG construction and live-range priorities while preserving observable operations.", early))
    for name, hypothesis, source in variants:
        ex = {"name": name, "hypothesis": hypothesis, "exact_source": source, "commands": []}
        data["experiments"].append(ex)
        SOURCE.write_text(source)
        run([".tools/bin/ninja", "-j2", "build/GEDE01/src/game/game_fn_80183F70.o"], ex["commands"])
        ex["comparisons"] = compare(name, ex["commands"])
        save()
finally:
    SOURCE.write_text(BASE)
    save()
run(["python3", "configure.py"])
run([".tools/bin/ninja", "-j2"])
data["retained_comparisons"] = compare("retained", data["commands"])
run(["sha1sum", "build/GEDE01/main.dol"])
run(["python3", "tools/legal_audit.py"])
save()
