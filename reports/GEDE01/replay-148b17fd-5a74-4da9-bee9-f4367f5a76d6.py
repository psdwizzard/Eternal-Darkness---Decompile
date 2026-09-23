#!/usr/bin/env python3
"""Validate each experimental patch against the assignment's accepted source."""
import hashlib, json, pathlib, subprocess, tempfile
ID = "148b17fd-5a74-4da9-bee9-f4367f5a76d6"
BASE = "01b43a2b8c74db42f2a9462b704c6a5d4da8fe2c"
ROOT = pathlib.Path(__file__).resolve().parents[3]
REPORTS = pathlib.Path("eternal-darkness-decomp/reports/GEDE01")
SOURCE = pathlib.Path("eternal-darkness-decomp/src/game/game_fn_801BACE8.c")
with (ROOT / REPORTS / f"replay-{ID}.log").open("w") as log:
    cmd = ["git", "show", f"{BASE}:{SOURCE}"]
    result = subprocess.run(cmd, cwd=ROOT, capture_output=True)
    log.write("argv: " + json.dumps(cmd) + "\n")
    log.write(result.stdout.decode() + result.stderr.decode())
    log.write(f"\nexit_status: {result.returncode}\n")
    result.check_returncode()
    original = result.stdout
    for name in ["member", "indexed", "stride", "array", "helper", "final"]:
        patch = REPORTS / f"{name}-{ID}.patch"
        with tempfile.TemporaryDirectory(prefix=f"replay-{ID}-", dir=ROOT / REPORTS) as directory:
            prefix = pathlib.Path(directory).relative_to(ROOT)
            target = ROOT / prefix / SOURCE
            target.parent.mkdir(parents=True)
            target.write_bytes(original)
            for option in [["--check"], []]:
                cmd = ["git", "apply"] + option + [f"--directory={prefix}", str(patch)]
                result = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
                log.write("argv: " + json.dumps(cmd) + "\n" + result.stdout + result.stderr)
                log.write(f"exit_status: {result.returncode}\n")
                result.check_returncode()
            log.write(f"{name} patched_source_sha256: {hashlib.sha256(target.read_bytes()).hexdigest()}\n")
            if name == "final":
                assert target.read_bytes() == (ROOT / SOURCE).read_bytes()
                log.write("final patched source equals retained source: true\n")
print("All six unified diffs apply cleanly to the accepted base; final replay equals retained source.")
