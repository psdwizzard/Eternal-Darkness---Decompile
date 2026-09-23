#!/usr/bin/env python3
"""Capture unabridged command output and exit status for this assignment."""
import json, pathlib, subprocess, sys, time
ROOT = pathlib.Path(__file__).resolve().parents[2]
ID = "148b17fd-5a74-4da9-bee9-f4367f5a76d6"
label = sys.argv[1]
commands = [
    ["python3", "configure.py"],
    [".tools/bin/ninja", "-j2"],
    ["build/tools/objdiff-cli", "diff", "-p", ".", "-u", "main/game/game_fn_801BACE8", "fn_801BACE8", "-o", f"reports/GEDE01/objdiff-{ID}-{label}-canonical.json", "--format", "json-pretty"],
    ["build/tools/objdiff-cli", "diff", "-p", ".", "-u", "main/game/game_fn_801BACE8", "fn_801BACE8", "-o", f"reports/GEDE01/objdiff-{ID}-{label}-strict.json", "--format", "json-pretty", "-c", "function_reloc_diffs=name_address"],
    ["sha1sum", "build/GEDE01/main.dol", "orig/GEDE01/sys/main.dol"],
    ["python3", "tools/legal_audit.py"],
]
if "--quick" in sys.argv:
    commands = [[".tools/bin/ninja", "-j2", "build/GEDE01/src/game/game_fn_801BACE8.o"]] + commands[2:4]
with (ROOT / f"reports/GEDE01/commands-{ID}-{label}.log").open("w") as log:
    for cmd in commands:
        log.write("cwd: eternal-darkness-decomp\nargv: " + json.dumps(cmd) + "\n")
        log.flush()
        result = subprocess.run(cmd, cwd=ROOT, stdout=log, stderr=subprocess.STDOUT)
        log.write(f"\nexit_status: {result.returncode}\n\n")
        log.flush()
        print(json.dumps(cmd), "exit_status:", result.returncode, flush=True)
        if result.returncode:
            sys.exit(result.returncode)
for mode in ["canonical", "strict"]:
    data = json.loads((ROOT / f"reports/GEDE01/objdiff-{ID}-{label}-{mode}.json").read_text())
    for side in ["left", "right"]:
        sym = next(x for x in data[side]["symbols"] if x["name"] == "fn_801BACE8")
        print(label, mode, side, "size", sym["size"], "match_percent", sym.get("match_percent"))
