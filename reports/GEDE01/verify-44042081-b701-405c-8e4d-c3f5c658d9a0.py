"""Assignment-specific reproducible evidence capture. Run from project root."""
import json
import subprocess
from pathlib import Path

ID = '44042081-b701-405c-8e4d-c3f5c658d9a0'
OUT = Path('reports/GEDE01')
records = []

def run(argv):
    p = subprocess.run(argv, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    records.append({'argv': argv, 'working_directory': 'eternal-darkness-decomp',
                    'exit_status': p.returncode, 'raw_output': p.stdout})
    (OUT / ('verification-' + ID + '.json')).write_text(json.dumps(records, indent=2) + '\n')
    print('exit', p.returncode, ' '.join(argv), flush=True)
    if p.returncode:
        raise SystemExit(p.returncode)
    return p.stdout

run(['python3', 'configure.py'])
run(['.tools/bin/ninja', '-j2'])
run(['sha1sum', '-c', 'config/GEDE01/build.sha1'])
hash_output = run(['sha1sum', 'build/GEDE01/main.dol'])
assert hash_output.split()[0] == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
run(['build/tools/objdiff-cli', '--version'])
run(['.tools/bin/ninja', '-t', 'commands', 'build/GEDE01/src/game/game_fn_80079D24.o'])
common = ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u',
          'main/game/game_fn_80079D24', 'fn_80079D24']
run(common + ['-o', str(OUT / ('objdiff-' + ID + '-canonical.json')), '--format', 'json-pretty'])
run(common + ['-c', 'function_reloc_diffs=name_address', '-o',
              str(OUT / ('objdiff-' + ID + '.json')), '--format', 'json-pretty'])
for side in ('obj', 'src'):
    run(['readelf', '-rW', '-sW', 'build/GEDE01/' + side + '/game/game_fn_80079D24.o'])
run(['python3', 'tools/legal_audit.py'])
run(['git', 'diff', '--check'])

run(['python3', 'reports/GEDE01/relocations-44042081-b701-405c-8e4d-c3f5c658d9a0.py'])
