import json, subprocess, hashlib
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
SRC = ROOT / "src/game/game_fn_8017D1E0.c"
REPORT = ROOT / "reports/GEDE01/experiments-85213feb-5dea-4ac4-a954-48077b0b59ee.json"
def run(cmd):
    p = subprocess.run(cmd, cwd=ROOT, text=True, capture_output=True)
    return {"command": cmd, "exit_code": p.returncode, "stdout": p.stdout, "stderr": p.stderr}
def measure(name, source, hypothesis):
    SRC.write_text(source)
    build = run([".tools/bin/ninja", "-j2", "build/GEDE01/src/game/game_fn_8017D1E0.o"])
    diff = run(["build/tools/objdiff-cli", "diff", "-p", ".", "-u", "main/game/game_fn_8017D1E0", "fn_8017D1E0", "-o", "-", "--format", "json"])
    result = {"name": name, "hypothesis": hypothesis, "source": source, "source_sha256": hashlib.sha256(source.encode()).hexdigest(), "build": build, "objdiff": diff}
    if diff["exit_code"] == 0 and build["exit_code"] == 0:
        data = json.loads(diff["stdout"])
        sym = next(x for x in data["left"]["symbols"] if x["name"] == "fn_8017D1E0")
        result["score"] = sym.get("match_percent")
    results = json.loads(REPORT.read_text()) if REPORT.exists() else []
    results.append(result)
    REPORT.write_text(json.dumps(results, indent=2)+"\n")
    print(name, result.get("score"), build["exit_code"], diff["stderr"], flush=True)
    return result
if __name__ == "__main__":
    baseline = subprocess.check_output(["git", "show", "86ba1fc029906f9fa1e15b35bc1476c49c396d60:eternal-darkness-decomp/src/game/game_fn_8017D1E0.c"], cwd=ROOT, text=True)
    measure("accepted-base", baseline, "Fresh control measurement of accepted source")
    shared = baseline.replace("    int result = 0;", "    int delta;\n    int result = 0;").replace("int delta = second", "delta = second")
    measure("shared-delta", shared, "Use one signed delta variable across axes to change coalescing/interference graph")
    SRC.write_text(baseline)
