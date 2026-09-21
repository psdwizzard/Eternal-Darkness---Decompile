"""Run from eternal-darkness-decomp after restoring the retained source."""
import hashlib
import json
import subprocess
from pathlib import Path

AID = '3f5313be-e7de-46b2-bfbf-2794eb1cf1b8'
OUT = Path(f'reports/GEDE01/objdiff-{AID}.json')
evidence = {'version': 1, 'assignment_id': AID, 'commands': [], 'compiler': 'GC/1.3; unchanged canonical configure.py settings', 'source': Path('src/game/game_fn_8018CB70.c').read_text()}
def save():
    OUT.write_text(json.dumps(evidence, indent=2) + '\n')
def run(args):
    p = subprocess.run(args, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    record = {'command': args, 'cwd': 'eternal-darkness-decomp', 'exit_code': p.returncode, 'raw_output': p.stdout}
    evidence['commands'].append(record)
    save()
    print(' '.join(args), 'exit', p.returncode, flush=True)
    if p.returncode: raise RuntimeError(record)
    return p.stdout
run(['python3', 'configure.py'])
run(['.tools/bin/ninja', '-j2'])
run(['sha1sum', 'build/GEDE01/main.dol'])
evidence['dol_sha1'] = hashlib.sha1(Path('build/GEDE01/main.dol').read_bytes()).hexdigest()
assert evidence['dol_sha1'] == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
run(['python3', 'tools/legal_audit.py'])
for side in ['obj', 'src']:
    path = f'build/GEDE01/{side}/game/game_fn_8018CB70.o'
    run(['build/binutils/powerpc-eabi-readelf', '-r', path])
    run(['.tools/bin/dtk', 'elf', 'info', path])
    run(['build/binutils/powerpc-eabi-objdump', '-dr', path])
for mode in ['canonical', 'relocation_strict']:
    tmp = Path(f'reports/GEDE01/.verify-{AID}.json')
    cmd = ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_8018CB70', '-o', str(tmp), '--format', 'json']
    if mode == 'relocation_strict': cmd.extend(['-c', 'function_reloc_diffs=name_address'])
    cmd.append('fn_8018CB70')
    run(cmd)
    evidence[mode] = json.loads(tmp.read_text())
    tmp.unlink()
    for side in ['left', 'right']:
        sym = next(s for s in evidence[mode][side]['symbols'] if s['name'] == 'fn_8018CB70')
        print(mode, side, sym.get('size'), sym.get('match_percent'), flush=True)
save()
