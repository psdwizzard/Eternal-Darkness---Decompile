#!/usr/bin/env python3
"""Summarize raw comparisons and independently check ELF relocation identities."""
import json
import struct
import subprocess
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
AID = "ea7e5010-0b7a-4585-b1d5-601533c74d30"
P = ROOT / "reports/GEDE01" / ("objdiff-" + AID + ".json")
d = json.loads(P.read_text())
def run(argv):
    r = subprocess.run(argv, cwd=ROOT, text=True, capture_output=True)
    d["commands"].append({"argv": argv, "cwd": "eternal-darkness-decomp", "exit_code": r.returncode, "stdout": r.stdout, "stderr": r.stderr})
    assert r.returncode == 0, r.stderr
    return r.stdout

def elf(path):
    raw = (ROOT/path).read_bytes()
    assert raw[:6] == b"\x7fELF\x01\x02"
    shoff = struct.unpack_from(">I", raw, 32)[0]
    shentsize, shnum, shstrndx = struct.unpack_from(">HHH", raw, 46)
    sections = [struct.unpack_from(">10I", raw, shoff+i*shentsize) for i in range(shnum)]
    def content(s): return raw[s[4]:s[4]+s[5]]
    def string(t, n): return t[n:t.index(b"\0", n)].decode()
    names = content(sections[shstrndx])
    syms = {}
    for i,s in enumerate(sections):
        if s[1] == 2:
            strings = content(sections[s[6]])
            syms[i] = [string(strings,struct.unpack_from(">I",raw,s[4]+n)[0]) for n in range(0,s[5],s[9])]
    relocations = []
    for s in sections:
        if s[1] == 4:
            for n in range(0,s[5],s[9]):
                offset,info,addend = struct.unpack_from(">IIi",raw,s[4]+n)
                relocations.append({"section":string(names,sections[s[7]][0]),"offset":offset,"type":info&255,"target":syms[s[6]][info>>8],"addend":addend})
    return next(iter(syms.values())),relocations

paths = ["build/GEDE01/obj/game/game_fn_80183F70.o", "build/GEDE01/src/game/game_fn_80183F70.o"]
elfs = []
for path in paths:
    run(["readelf", "-r", "-s", path])
    elfs.append(elf(path))
run([".tools/bin/ninja", "-t", "commands", paths[1]])
assert elfs[0][1] == elfs[1][1]
d["elf_relocation_verification"] = {"method":"ELF32 big-endian SHT_RELA records compared by section, offset, type, resolved symbol name, signed addend", "equal": True, "retail": elfs[0][1], "candidate": elfs[1][1]}
d["comparison_settings"] = {"canonical": "project defaults; no -c override", "strict": "function_reloc_diffs=name_address", "unit": next(u for u in json.loads((ROOT/"objdiff.json").read_text())["units"] if u["name"] == "main/game/game_fn_80183F70")}

def summarize(raw):
    syms = [next(s for s in raw[side]["symbols"] if s["name"] == "fn_80183F70") for side in ["left", "right"]]
    instructions = [s["instructions"] for s in syms]
    mismatches = []
    relocations = [[],[]]
    for side in range(2):
        # Objdiff indices are its internal symbols, not ELF symbol indices.
        # Resolve each through its physical ELF relocation at the same instruction.
        targets = {}
        for row in instructions[side]:
            i = row["instruction"]
            r = i.get("relocation")
            if r and r.get("type", 0):
                physical = next(x for x in elfs[side][1] if x["offset"] // 4 == int(i.get("address",0)) // 4)
                assert physical["type"] == r["type"]
                assert physical["addend"] == int(r.get("addend",0))
                targets[r["target_symbol"]] = physical["target"]
        for row in instructions[side]:
            i = row["instruction"]
            r = i.get("relocation")
            if r:
                relocations[side].append({"instruction_address":i.get("address","0"), "type":r.get("type",0), "target":targets[r["target_symbol"]], "addend":int(r.get("addend",0))})
    for a,b in zip(*instructions):
        if a.get("diff_kind"):
            mismatches.append({"offset":a["instruction"].get("address","0"),"kind":a["diff_kind"],"retail":a["instruction"]["formatted"],"candidate":b["instruction"]["formatted"]})
    assert relocations[0] == relocations[1]
    return {"retail_size":syms[0]["size"],"candidate_size":syms[1]["size"],"match_percent":syms[0]["match_percent"],"instruction_counts":list(map(len,instructions)), "relocation_bearing_instructions_equal": True, "resolved_relocations":relocations[0], "mismatches":mismatches}

d["retained_summary"] = {mode:summarize(raw) for mode,raw in d["retained_comparisons"].items()}
for e in d["experiments"]:
    e["summary"] = {mode:summarize(raw) for mode,raw in e["comparisons"].items()}
    e["identical_objdiff_to_baseline"] = e["comparisons"] == d["baseline_comparisons"]
assert (ROOT/"src/game/game_fn_80183F70.c").read_text() == d["baseline_source"]
assert any(c["argv"] == ["sha1sum","build/GEDE01/main.dol"] and c["stdout"].startswith("ea24b6af954876ce072562ff39cdb4c81d32be1f ") for c in d["commands"])
d["historical_review"] = {"preserved_commits":["2e71a98c0cdd6f4ed355bd5bd0be9375cca2d13a","7df87dc3a5bd94969d4252312a53e0891ed2fe0b","2dec8834117c517f3c73201d227317ccf6ff597c","4b976adc4c571edd96bf9bc00c48fdcdaefa6114","a9c357cf5610a22b5fa78d4bb2a0d3a88ec4fd37"],"closed_hypotheses":["K&R parameter declaration reordering", "direct typed parameters", "descriptor/self/entry staged initialization", "typed pointee record layouts"],"base_reconciliation":"Accepted base already has the same source as preserved commit 2e71a98c; retained it unchanged as NonMatching."}
d["conclusion"] = "Both distinct source variants compiled identically to the accepted baseline. Retained the existing single independent NonMatching C translation unit; no compiler/configuration changes. Full DOL hash validates the existing NonMatching build, which links the retail function, not proof of a candidate match."
P.write_text(json.dumps(d,indent=2)+"\n")
envelope = {"version":1,"assignment_id":AID,"attempt":6,"base_commit":"8b57bb8b104f8b89c059eb6406d9a17166f6d7a9","target":"fn_80183F70","status":"attempted","evidence":["eternal-darkness-decomp/reports/GEDE01/objdiff-"+AID+".json", "eternal-darkness-decomp/reports/GEDE01/experiment-"+AID+".py", "eternal-darkness-decomp/reports/GEDE01/finalize-"+AID+".py"],"divergence":"Canonical and relocation-strict objdiff: 98.15069%, 292/292 bytes, 73/73 instructions. All 17 relocation-bearing instructions agree by address, type, resolved target and addend; all 16 physical ELF RELA records agree. 27 instructions differ only by persistent-register rotation: retail descriptor/self/entry r31/r30/r29 versus candidate r29/r31/r30. Local pointer-aggregate scalarization and inverted final conditional with early return both produced identical output. Exact variant sources and raw configure/build/objdiff/hash/audit outputs preserved."}
(ROOT/"reports/GEDE01"/("durable-"+AID+".json")).write_text(json.dumps(envelope,indent=2)+"\n")
print(json.dumps(envelope,indent=2))
