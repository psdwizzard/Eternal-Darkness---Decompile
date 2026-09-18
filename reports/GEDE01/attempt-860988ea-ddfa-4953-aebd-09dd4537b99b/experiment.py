#!/usr/bin/env python3
"""Run from eternal-darkness-decomp; preserve patches and raw canonical measurements."""
import difflib
import hashlib
import json
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parent.relative_to(Path.cwd())
SOURCE = Path('src/game/game_fn_801ED5F4.c')
BASE_REV = 'f3b6f8b90a4f23e609b0b7783934b4cd404a95e4'
base = subprocess.check_output(['git', 'show', BASE_REV + ':eternal-darkness-decomp/' + str(SOURCE)], text=True)

def run(command, log):
    p = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    log.append({'command': command, 'exit_code': p.returncode, 'output': p.stdout})
    return p.returncode

def measure(name, source, hypothesis):
    SOURCE.write_text(source)
    (ROOT / (name + '.patch')).write_text(''.join(difflib.unified_diff(base.splitlines(True), source.splitlines(True), fromfile=str(SOURCE), tofile=str(SOURCE))))
    log = []
    record = {'name': name, 'hypothesis': hypothesis, 'base_commit': BASE_REV,
              'source_sha256': hashlib.sha256(source.encode()).hexdigest(), 'commands': log}
    rc = run(['.tools/bin/ninja', '-j2', 'build/GEDE01/src/game/game_fn_801ED5F4.externalized'], log)
    if rc == 0:
        output = ROOT / (name + '.objdiff.json')
        rc = run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_801ED5F4', 'fn_801ED5F4', '-o', str(output), '--format', 'json'], log)
        if rc == 0:
            d = json.loads(output.read_text())
            a, b = [next(s for s in d[side]['symbols'] if s['name'] == 'fn_801ED5F4') for side in ('left', 'right')]
            record.update(score=a['match_percent'], target_size=a['size'], candidate_size=b['size'])
            record['differences'] = [{'offset': hex(i*4), 'target': x.get('instruction', {}).get('formatted'), 'candidate': y.get('instruction', {}).get('formatted')} for i, (x, y) in enumerate(zip(a['instructions'], b['instructions'])) if x.get('diff_kind') not in (None, 'DIFF_NONE')]
    (ROOT / (name + '.measurement.json')).write_text(json.dumps(record, indent=2) + '\n')
    print(name, record.get('score'), record.get('candidate_size'), flush=True)
    return record

if __name__ == '__main__':
    try:
        measure('baseline', base, 'Reproduce strongest preserved source under unchanged canonical settings.')
        for name, indices in [('compound-last', [(1,0)]), ('compound-first', [(0,0)]), ('compound-all', [(0,0),(0,1),(1,0)])]:
            source = base
            for row,col in indices:
                constant = {(0,0): '1C', (0,1): '30', (1,0): '34'}[(row,col)]
                old = f'transform[{row}][{col}] = lbl_806513{constant} / divisor;'
                new = f'transform[{row}][{col}] = lbl_806513{constant};\n                transform[{row}][{col}] /= divisor;'
                assert old in source
                source = source.replace(old, new)
            measure(name, source, 'In-place matrix-field division may coalesce numerator and result registers differently from a direct quotient assignment.')
    finally:
        SOURCE.write_text(base)
