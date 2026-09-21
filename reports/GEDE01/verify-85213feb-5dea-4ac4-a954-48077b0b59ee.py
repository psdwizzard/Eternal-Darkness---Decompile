import hashlib, json, subprocess, struct
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
ID = "85213feb-5dea-4ac4-a954-48077b0b59ee"
REPORT = ROOT / ("reports/GEDE01/verification-"+ID+".json")
records = []
def run(cmd):
    p = subprocess.run(cmd, cwd=ROOT, text=True, capture_output=True)
    r = {"command":cmd,"cwd":"eternal-darkness-decomp","exit_code":p.returncode,"stdout":p.stdout,"stderr":p.stderr}
    records.append(r)
    REPORT.write_text(json.dumps(records,indent=2)+"\n")
    print(" ".join(cmd), "exit",p.returncode,flush=True)
    if p.returncode: raise RuntimeError(r)
    return r
run(["python3","configure.py"])
run([".tools/bin/ninja","-j2","-v","build/GEDE01/src/game/game_fn_8017D1E0.o"])
# Build through the canonical DOL/checksum gate; omit the global progress-writing target.
run([".tools/bin/ninja","-j2","build/GEDE01/ok"])
run([".tools/bin/ninja","-t","commands","build/GEDE01/src/game/game_fn_8017D1E0.o"])
base=["build/tools/objdiff-cli","diff","-p",".","-u","main/game/game_fn_8017D1E0","fn_8017D1E0","--format","json"]
run(base+["-o","reports/GEDE01/objdiff-"+ID+".json"])
run(base+["-c","functionRelocDiffs=all","-o","reports/GEDE01/objdiff-strict-"+ID+".json"])
for side in ["obj","src"]:
    run(["build/binutils/powerpc-eabi-readelf","-SWsr","build/GEDE01/"+side+"/game/game_fn_8017D1E0.o"])
run(["sha1sum","build/GEDE01/main.dol","orig/GEDE01/sys/main.dol"])
run(["cmp","build/GEDE01/main.dol","orig/GEDE01/sys/main.dol"])
run([".tools/bin/dtk","shasum","-c","config/GEDE01/build.sha1"])
run(["python3","tools/legal_audit.py"])
run(["git","diff","--check"])
