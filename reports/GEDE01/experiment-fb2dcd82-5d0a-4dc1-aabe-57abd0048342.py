"""Assignment-specific reproducible, sequential codegen probes; restores original C."""
import hashlib
import json
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
AID = 'fb2dcd82-5d0a-4dc1-aabe-57abd0048342'
REPORTS = ROOT / 'reports/GEDE01'
SOURCE = ROOT / 'src/game/game_fn_80063124.c'
original = SOURCE.read_text()
records = []

def run(cmd):
    p = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    record = dict(command=cmd, cwd='eternal-darkness-decomp', exit_code=p.returncode, stdout=p.stdout, stderr=p.stderr)
    return record

variants = [
    ('baseline', []),
    ('derive-special-at-use', [('    special = channels & 2;\n', ''), ('special != 0', '(channels & 2) != 0')]),
    ('derive-signed-step-at-use', [('    signed_step = (s16)step;\n', ''), ('remaining -= signed_step;', 'remaining -= (s16)step;')]),
    ('derive-both-at-use', [('    special = channels & 2;\n', ''), ('special != 0', '(channels & 2) != 0'), ('    signed_step = (s16)step;\n', ''), ('remaining -= signed_step;', 'remaining -= (s16)step;')]),
    ('derive-special-loop-entry', [('    special = channels & 2;\n', ''), ('        if ((channels', '        special = channels & 2;\n        if ((channels')]),
    ('derive-signed-loop-entry', [('    signed_step = (s16)step;\n', ''), ('        if ((channels', '        signed_step = (s16)step;\n        if ((channels')]),
]
try:
    for name, substitutions in variants:
        candidate = original
        for before, after in substitutions:
            assert before in candidate
            candidate = candidate.replace(before, after)
        SOURCE.write_text(candidate)
        item = dict(name=name, substitutions=substitutions, source_sha256=hashlib.sha256(candidate.encode()).hexdigest(), commands=[])
        records.append(item)
        item['commands'].append(run(['.tools/bin/ninja', '-j2', 'build/GEDE01/src/game/game_fn_80063124.o']))
        if item['commands'][-1]['exit_code']:
            continue
        cmd = ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_80063124', 'fn_80063124', '-o', '-', '--format', 'json', '-c', 'function_reloc_diffs=name_address']
        item['commands'].append(run(cmd))
        d = json.loads(item['commands'][-1]['stdout'])
        left = next(s for s in d['left']['symbols'] if s['name']=='fn_80063124')
        right = next(s for s in d['right']['symbols'] if s['name']=='fn_80063124')
        item['score'] = left['match_percent']
        item['target_size'] = left['size']
        item['candidate_size'] = right['size']
        print(name, item['score'], item['candidate_size'], flush=True)
        (REPORTS / f'experiments-{AID}.json').write_text(json.dumps(records, indent=2)+'\n')
finally:
    SOURCE.write_text(original)
    records.append(dict(name='restore-baseline',commands=[run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80063124.o'])]))
    (REPORTS / f'experiments-{AID}.json').write_text(json.dumps(records, indent=2)+'\n')
