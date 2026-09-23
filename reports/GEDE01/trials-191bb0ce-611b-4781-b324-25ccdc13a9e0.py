import json, subprocess, difflib
from pathlib import Path
ID = "191bb0ce-611b-4781-b324-25ccdc13a9e0"
REPORT = Path("reports/GEDE01")
SRC = Path("src/game/game_fn_80130720.c")
LOG = REPORT / ("experiment-" + ID + ".json")
BASE = json.loads(LOG.read_text())["baseline_source"]
def measure(label, source):
    SRC.write_text(source)
    commands=[]
    out=REPORT/("objdiff-"+ID+"-trial.raw.json")
    for cmd in [[".tools/bin/ninja","-j2","build/GEDE01/src/game/game_fn_80130720.o"], ["build/tools/objdiff-cli","diff","-p",".","-u","main/game/game_fn_80130720","fn_80130720","-o",str(out),"--format","json-pretty","-c","function_reloc_diffs=name_address"]]:
        r=subprocess.run(cmd,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
        commands.append({"argv":cmd,"exit_code":r.returncode,"raw_output":r.stdout})
        if r.returncode: break
    item={"label":label,"source_patch":"".join(difflib.unified_diff(BASE.splitlines(True),source.splitlines(True),fromfile="baseline",tofile=label)),"commands":commands}
    if not r.returncode:
        d=json.loads(out.read_text())
        l=next(s for s in d["left"]["symbols"] if s["name"]=="fn_80130720")
        rr=next(s for s in d["right"]["symbols"] if s["name"]=="fn_80130720")
        item.update(score=l.get("match_percent"),target_size=l["size"],generated_size=rr["size"])
        item["instruction_comparison"]=[{"target":a.get("instruction",{}).get("formatted",""),"generated":b.get("instruction",{}).get("formatted",""),"diff_kind":a.get("diff_kind", "DIFF_NONE")} for a,b in zip(l["instructions"],rr["instructions"])]
    log=json.loads(LOG.read_text());log["experiments"].append(item);LOG.write_text(json.dumps(log,indent=2)+"\n")
    print(label, item.get("score"),item.get("generated_size"),flush=True)
    if r.returncode: print(r.stdout)
    return item
