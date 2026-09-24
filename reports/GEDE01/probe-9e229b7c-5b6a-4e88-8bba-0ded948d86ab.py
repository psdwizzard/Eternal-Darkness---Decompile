"""Assignment-only measurement helper; all compiler options come from Ninja.
Executed by the recorded experiment commands. Does not change registration/policy.
"""
import difflib
import hashlib
import json
from pathlib import Path
import subprocess

assignment = '9e229b7c-5b6a-4e88-8bba-0ded948d86ab'
src = Path('src/game/game_fn_80195AEC.c')
report_path = Path(f'reports/GEDE01/experiments-{assignment}.json')
raw_path = Path(f'reports/GEDE01/objdiff-{assignment}.json')
report = json.loads(report_path.read_text())
compiler = report['compile_command']
baseline = subprocess.check_output(['git', 'show', 'a3a43533beeca2f41ebe1c170e5865dfe931eea1:eternal-darkness-decomp/src/game/game_fn_80195AEC.c'], text=True)
best_source = src.read_text()
best_raw = json.loads(raw_path.read_text())
best_score = next(s['match_percent'] for s in best_raw['left']['symbols'] if s['name'] == 'fn_80195AEC')

def probe(name, source):
    global best_source, best_raw, best_score
    src.write_text(source)
    build = subprocess.run(compiler, shell=True, text=True, capture_output=True)
    row = dict(name=name, source_sha256=hashlib.sha256(source.encode()).hexdigest(),
               patch=''.join(difflib.unified_diff(baseline.splitlines(True), source.splitlines(True))),
               compile_exit=build.returncode, compile_stdout=build.stdout, compile_stderr=build.stderr)
    if build.returncode == 0:
        result = subprocess.run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u',
                                 'main/game/game_fn_80195AEC', 'fn_80195AEC', '-o', '-', '--format', 'json'],
                                text=True, capture_output=True, check=True)
        raw = json.loads(result.stdout)
        left = next(s for s in raw['left']['symbols'] if s['name'] == 'fn_80195AEC')
        right = next(s for s in raw['right']['symbols'] if s['name'] == 'fn_80195AEC')
        row.update(score=left['match_percent'], target_size=left['size'], candidate_size=right['size'],
                   objdiff_stderr=result.stderr,
                   prologue=[i.get('instruction', {}).get('formatted') for i in right['instructions'][:8]])
        if row['score'] > best_score:
            best_source, best_raw, best_score = source, raw, row['score']
    report['variants'].append(row)
    report_path.write_text(json.dumps(report, indent=2) + '\n')
    print(name, row.get('score'), row.get('candidate_size'), flush=True)
    return row

def finish():
    src.write_text(best_source)
    raw_path.write_text(json.dumps(best_raw, indent=2) + '\n')
    subprocess.run(compiler, shell=True, check=True)
