"""Run from eternal-darkness-decomp; preserve this assignment's raw verification."""
import hashlib
import json
import struct
import subprocess
from pathlib import Path

A = '0041c35a-89db-44d2-900f-76a23235ebfe'
R = Path('reports/GEDE01')
results = {'version': 1, 'assignment_id': A, 'commands': []}

def run(args):
    p = subprocess.run(args, capture_output=True, text=True)
    results['commands'].append({'argv': args, 'exit_code': p.returncode,
                                'stdout': p.stdout, 'stderr': p.stderr})
    (R / ('verification-' + A + '.json')).write_text(json.dumps(results, indent=2) + '\n')
    print('exit', p.returncode, ' '.join(args), flush=True)
    if p.returncode:
        raise SystemExit(p.returncode)
    return p

run(['python3', 'configure.py'])
run(['.tools/bin/ninja', '-j2'])
for suffix, config in [('', []), ('-reloc-strict', ['-c', 'function_reloc_diffs=all'])]:
    run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_800A78E0',
         *config, '-o', str(R / ('objdiff-' + A + suffix + '.json')), '--format', 'json-pretty', 'fn_800A78E0'])

objects = ['build/GEDE01/obj/game/game_fn_800A78E0.o', 'build/GEDE01/src/game/game_fn_800A78E0.o']
for obj in objects:
    run(['build/binutils/powerpc-eabi-readelf', '-Wr', obj])
    run(['build/binutils/powerpc-eabi-objdump', '-dr', obj])

# Parse big-endian ELF32 RELA entries independently, resolving symbol names.
def relocs(path):
    data = Path(path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    off = struct.unpack_from('>I', data, 32)[0]
    size, count = struct.unpack_from('>HH', data, 46)
    sections = [struct.unpack_from('>10I', data, off + i * size) for i in range(count)]
    entries = []
    for sh in sections:
        if sh[1] != 4:
            continue
        syms = sections[sh[6]]
        strings = sections[syms[6]]
        for pos in range(sh[4], sh[4] + sh[5], sh[9]):
            address, info, addend = struct.unpack_from('>IIi', data, pos)
            index = info >> 8
            name_offset = struct.unpack_from('>I', data, syms[4] + index * syms[9])[0]
            start = strings[4] + name_offset
            name = data[start:data.index(b'\0', start)].decode()
            entries.append({'offset': address, 'type': info & 255, 'target': name, 'addend': addend})
    return entries
left, right = [relocs(p) for p in objects]
normalize = lambda rs: [(r['type'], r['target'], r['addend']) for r in rs]
results['relocation_comparison'] = {'target': left, 'candidate': right,
    'ordered_type_target_addend_equal': normalize(left) == normalize(right),
    'note': 'Offsets retained; source is four bytes longer, so later relocations are shifted.'}
assert normalize(left) == normalize(right)
run(['sha1sum', 'build/GEDE01/main.dol', 'orig/GEDE01/sys/main.dol'])
run(['cmp', 'build/GEDE01/main.dol', 'orig/GEDE01/sys/main.dol'])
expected = 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
assert hashlib.sha1(Path('build/GEDE01/main.dol').read_bytes()).hexdigest() == expected
results['source_sha256'] = hashlib.sha256(Path('src/game/game_fn_800A78E0.c').read_bytes()).hexdigest()
results['compiler_policy'] = 'Unmodified GC/1.3 canonical flags, including existing -use_lmw_stmw on registration; NonMatching.'
results['dol_scope'] = 'NonMatching reconstruction is not linked into the verified DOL; retail split object remains in the full link.'
run(['python3', 'tools/legal_audit.py'])
