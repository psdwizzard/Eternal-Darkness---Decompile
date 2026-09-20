"""Replay the exact recorded candidates under unchanged canonical settings.
Run from the worktree root. Restores the function source even on failure.
"""
import json
import subprocess
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
ID = "5baa94f5-30a9-4fe4-b2e0-70c9b3517411"
SOURCE = ROOT / "src/game/game_fn_801C3E2C.c"
records = json.loads((ROOT / f"reports/GEDE01/trials-{ID}.json").read_text())
original = SOURCE.read_text()
try:
    for record in records:
        SOURCE.write_text(record["source"])
        for command in record["commands"]:
            subprocess.run(command["argv"], cwd=ROOT, check=True)
finally:
    SOURCE.write_text(original)
    subprocess.run([".tools/bin/ninja", "-j2", "build/GEDE01/src/game/game_fn_801C3E2C.o"], cwd=ROOT, check=True)
