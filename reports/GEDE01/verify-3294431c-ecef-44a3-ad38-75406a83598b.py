"""Capture canonical verification without committing binaries or disassembly."""
import hashlib, json, subprocess
from pathlib import Path
ID = "3294431c-ecef-44a3-ad38-75406a83598b"
TARGET = "fn_8008D5D4"
out = Path(f"reports/GEDE01/objdiff-{ID}.json")
evidence = {"version":1, "assignment_id":ID, "target":TARGET, "command_cwd":"eternal-darkness-decomp", "commands":[], "checks":{}}
def save():
    out.write_text(json.dumps(evidence,indent=2)+"\n")
def run(cmd):
    p = subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    r = {"argv":cmd, "exit_code":p.returncode, "raw_output":p.stdout}
    evidence["commands"].append(r)
    save()
    print(" ".join(cmd), "exit",p.returncode,flush=True)
    if p.returncode: raise RuntimeError(r)
    return r
run(["python3","configure.py"])
run([".tools/bin/ninja","-j2"])
evidence["compiler_command"] = run([".tools/bin/ninja","-t","commands","build/GEDE01/src/game/game_fn_8008D5D4.o"])["raw_output"]
for config in ["canonical","relocation-strict"]:
    path = f"build/GEDE01/{ID}-{config}.json"
    cmd = ["build/tools/objdiff-cli","diff","-p",".","-u","main/game/game_fn_8008D5D4",TARGET,"-o",path,"--format","json-pretty"]
    if config == "relocation-strict": cmd += ["-c","function_reloc_diffs=name_address"]
    run(cmd)
    raw = Path(path).read_bytes()
    d = json.loads(raw)
    check = {"configuration": "project defaults" if config=="canonical" else "function_reloc_diffs=name_address", "raw_report_sha256":hashlib.sha256(raw).hexdigest(), "extraction":"Objdiff metadata and relocation tuples; instruction disassembly omitted under docs/legal-clean-room.md."}
    for side in ["left","right"]:
        sym = next(s for s in d[side]["symbols"] if s["name"]==TARGET)
        relocs = []
        for item in sym["instructions"]:
            ins = item.get("instruction",{})
            if "relocation" not in ins: continue
            reloc = ins["relocation"]
            relocs.append({"offset":int(ins.get("address",0)),"type":reloc["type_name"],"target":ins["formatted"].split(None, 1)[1],"addend":int(reloc.get("addend",0))})
        check[side] = {"raw_symbol_metadata":{k:v for k,v in sym.items() if k!="instructions"}, "relocations":relocs}
    check["relocations_identical"] = check["left"]["relocations"] == check["right"]["relocations"]
    evidence["checks"][config]=check
    save()
for side in ["obj","src"]:
    run(["readelf","-rW",f"build/GEDE01/{side}/game/game_fn_8008D5D4.o"])
run(["sha1sum","build/GEDE01/main.dol","orig/GEDE01/sys/main.dol"])
run(["cmp","-s","build/GEDE01/main.dol","orig/GEDE01/sys/main.dol"])
run(["python3","tools/legal_audit.py"])
evidence["source_sha256"]=hashlib.sha256(Path("src/game/game_fn_8008D5D4.c").read_bytes()).hexdigest()
evidence["linkage"]="NonMatching; canonical link uses retail object for this function. DOL equality does not establish a match for the C reconstruction."
evidence["probe_evidence"] = f"eternal-darkness-decomp/reports/GEDE01/probes-{ID}.json"
save()
