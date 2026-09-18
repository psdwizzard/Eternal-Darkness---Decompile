#!/usr/bin/env python3
"""Run from eternal-darkness-decomp. Each patch applies independently to the stated base."""
import difflib, json, subprocess
from pathlib import Path
BASE = "fd84719f7a898bb84e4cc9f7bda5efbb4d87e9e5"
OUT = Path("reports/GEDE01/attempt-9059de8c-c6c6-4d23-82ef-1ed56c6f93fd")
SOURCE = Path("src/game/game_fn_801A36C0.c")
original = subprocess.check_output(["git", "show", BASE + ":eternal-darkness-decomp/" + str(SOURCE)], text=True)
recovered = original.replace("    vertex_offset = 0;\n    for (i = 0; i < count; i++) {", "    for (i = 0, vertex_offset = 0; i < count; i++) {")
variants = {"baseline": original, "recovered-for-init": recovered}
variants["derived-offset"] = recovered.replace("    int vertex_offset;\n", "").replace("i = 0, vertex_offset = 0", "i = 0").replace("vertex_data + vertex_offset", "vertex_data + i * 0x18").replace("        vertex_offset += 0x18;\n", "")
variants["inner-derived-offset"] = recovered.replace("    int vertex_offset;\n", "").replace("i = 0, vertex_offset = 0", "i = 0").replace("        int j;", "        int j;\n        int vertex_offset = i * 0x18;").replace("        vertex_offset += 0x18;\n", "")
variants["for-step-offset"] = recovered.replace("i < count; i++)", "i < count; i++, vertex_offset += 0x18)").replace("        vertex_offset += 0x18;\n", "")
variants["for-step-cursors"] = recovered.replace("i < count; i++)", "i < count; i++, entries += 0x38, vertex_offset += 0x18)").replace("        entries += 0x38;\n        vertex_offset += 0x18;\n", "")
variants["typed-entry"] = recovered.replace("extern int lbl_8064D738;", "typedef struct Entry { u8 data[0x38]; } Entry;\n\nextern int lbl_8064D738;").replace("    u8* entries;", "    Entry* entries;").replace("entries = *(u8**)(self + 0x4C);", "entries = *(Entry**)(self + 0x4C);").replace("entries[0x21]", "entries->data[0x21]").replace("entries[0x20]", "entries->data[0x20]").replace("entries += 0x38;", "entries++;")

def run(args, log):
    with log.open("w") as f:
        f.write("$ " + __import__("shlex").join(args) + "\n"); f.flush()
        proc = subprocess.run(args, stdout=f, stderr=subprocess.STDOUT, text=True)
        f.write("\nexit=" + str(proc.returncode) + "\n")
    proc.check_returncode()

def measure(name, code):
    (OUT / (name + ".patch")).write_text("".join(difflib.unified_diff(original.splitlines(True), code.splitlines(True), fromfile="a/" + str(SOURCE), tofile="b/" + str(SOURCE))))
    SOURCE.write_text(code)
    run([".tools/bin/ninja", "-j2", "-v", "build/GEDE01/src/game/game_fn_801A36C0.o"], OUT / (name + "-compile.log"))
    output = OUT / (name + "-objdiff.json")
    run(["build/tools/objdiff-cli", "diff", "-p", ".", "-u", "main/game/game_fn_801A36C0", "fn_801A36C0", "-o", str(output), "--format", "json-pretty", "-c", "function_reloc_diffs=name_address"], OUT / (name + "-objdiff.log"))
    data = json.loads(output.read_text())
    l, r = [next(s for s in data[side]["symbols"] if s["name"] == "fn_801A36C0") for side in ("left", "right")]
    result = {"variant": name, "retail_bytes": l["size"], "generated_bytes": r["size"], "match_percent": l["match_percent"], "differing_rows": sum(i.get("diff_kind") not in (None, "DIFF_NONE") for i in l["instructions"])}
    print(json.dumps(result), flush=True)
    return result

if __name__ == "__main__":
    results = []
    try:
        for name, code in variants.items():
            results.append(measure(name, code))
    finally:
        SOURCE.write_text(recovered)
        (OUT / "measurements.json").write_text(json.dumps(results, indent=2) + "\n")
