"""Assignment-specific reproducible measurements; run from project directory.

Usage: python3 reports/GEDE01/experiment-7fc89737-8a24-47b7-b25f-f1405533f9ca.py LABEL
Measures the current target source without altering compiler policy.
"""
import hashlib
import json
from pathlib import Path
import subprocess
import sys

ID = '7fc89737-8a24-47b7-b25f-f1405533f9ca'
SOURCE = Path('src/game/game_fn_800D3598.c')
TARGET = 'build/GEDE01/obj/game/game_fn_800D3598.o'
BASE = 'build/GEDE01/src/game/game_fn_800D3598.o'
REPORT = Path(f'reports/GEDE01/objdiff-{ID}.json')

def run(argv):
    p = subprocess.run(argv, text=True, capture_output=True)
    result = dict(argv=argv, cwd='eternal-darkness-decomp', exit_code=p.returncode,
                  stdout=p.stdout, stderr=p.stderr)
    if p.returncode:
        print(json.dumps(result))
        raise RuntimeError('command failed')
    return result

def measure(label):
    record = dict(label=label, exact_source=SOURCE.read_text())
    record['compiler_commands'] = run(['.tools/bin/ninja', '-t', 'commands', BASE])
    # Source is freshly written by the experiment driver, so this executes MWCC.
    record['compile'] = run(['.tools/bin/ninja', '-j2', '-v', BASE])
    record['object_sha256'] = hashlib.sha256(Path(BASE).read_bytes()).hexdigest()
    for mode, options in [('canonical', []), ('relocation_strict', ['-c', 'functionRelocDiffs=name_address'])]:
        raw = run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u',
                   'main/game/game_fn_800D3598', *options, 'fn_800D3598', '-o', '-', '--format', 'json'])
        record[mode] = raw
        data = json.loads(raw['stdout'])
        left = next(s for s in data['left']['symbols'] if s['name'] == 'fn_800D3598')
        right = next(s for s in data['right']['symbols'] if s['name'] == 'fn_800D3598')
        record[mode + '_summary'] = dict(target_size=left['size'], base_size=right['size'], match_percent=left['match_percent'])
    record['retail_relocations'] = run(['readelf', '-rW', TARGET])
    record['generated_relocations'] = run(['readelf', '-rW', BASE])
    def entries(output):
        return [line.split()[0:1] + line.split()[2:] for line in output.splitlines() if 'R_PPC_' in line]
    record['all_relocation_offsets_types_targets_addends_equal'] = entries(record['retail_relocations']['stdout']) == entries(record['generated_relocations']['stdout'])
    report = json.loads(REPORT.read_text()) if REPORT.exists() else dict(version=1, assignment_id=ID, target='fn_800D3598', measurements=[])
    report['measurements'].append(record)
    REPORT.write_text(json.dumps(report, indent=2) + '\n')
    print(label, record['canonical_summary'], 'relocations:', record['all_relocation_offsets_types_targets_addends_equal'])

if __name__ == '__main__':
    measure(sys.argv[1])
