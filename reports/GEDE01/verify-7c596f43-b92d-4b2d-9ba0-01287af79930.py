"""Assignment-specific read-only verification; run from the decomp project root."""
import hashlib
import json
from pathlib import Path
import struct
import subprocess

ID = '7c596f43-b92d-4b2d-9ba0-01287af79930'
REPORTS = Path('reports/GEDE01')
TARGET = 'fn_801E6814'

def command(args):
    p = subprocess.run(args, text=True, capture_output=True)
    return dict(command=args, exit_code=p.returncode, stdout=p.stdout, stderr=p.stderr)

def elf_function(path):
    data = Path(path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    shoff = struct.unpack_from('>I', data, 32)[0]
    shsize, shcount = struct.unpack_from('>HH', data, 46)
    sections = [struct.unpack_from('>10I', data, shoff + i * shsize) for i in range(shcount)]
    symbols = []
    symtab_index = next(i for i, h in enumerate(sections) if h[1] == 2)
    h = sections[symtab_index]
    strings = sections[h[6]]
    for off in range(h[4], h[4] + h[5], h[9]):
        name, value, size, info, other, section = struct.unpack_from('>IIIBBH', data, off)
        start = strings[4] + name
        name = data[start:data.index(0, start)].decode()
        symbols.append(dict(name=name, value=value, size=size, section=section))
    fn = next(s for s in symbols if s['name'] == TARGET)
    h = sections[fn['section']]
    start = h[4] + fn['value']
    code = data[start:start + fn['size']]
    relocs = []
    for h in sections:
        if h[1] != 4 or h[7] != fn['section']:
            continue
        assert h[6] == symtab_index
        for off in range(h[4], h[4] + h[5], h[9]):
            address, info, addend = struct.unpack_from('>IIi', data, off)
            if fn['value'] <= address < fn['value'] + fn['size']:
                relocs.append(dict(offset=address-fn['value'], type=info & 255,
                                   target=symbols[info >> 8]['name'], addend=addend))
    return code, dict(path=path, bytes=len(code), instructions=len(code)//4,
                     text_sha256=hashlib.sha256(code).hexdigest(),
                     relocations=sorted(relocs, key=lambda x:x['offset']))

result = dict(version=1, assignment_id=ID, target=TARGET)
result['checks'] = []
for suffix, flags in [('', []), ('-reloc-strict', ['-c', 'function_reloc_diffs=name_address'])]:
    path = REPORTS / f'objdiff-{ID}{suffix}.json'
    args = ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u',
            'main/game/game_fn_801E6814', TARGET, '-o', str(path), '--format', 'json-pretty'] + flags
    check = command(args)
    assert check['exit_code'] == 0, check
    diff = json.loads(path.read_text())
    left = next(s for s in diff['left']['symbols'] if s['name'] == TARGET)
    right = next(s for s in diff['right']['symbols'] if s['name'] == TARGET)
    check['match_percent'] = left['match_percent']
    check['diff_rows'] = []
    for a, b in zip(left['instructions'], right['instructions']):
        a, b = a.get('instruction', {}), b.get('instruction', {})
        if a.get('formatted') != b.get('formatted'):
            check['diff_rows'].append(dict(offset=hex(int(a.get('address', 0))),
                                          retail=a.get('formatted'), generated=b.get('formatted')))
    result['checks'].append(check)
a, left = elf_function('build/GEDE01/obj/game/game_fn_801E6814.o')
b, right = elf_function('build/GEDE01/src/game/game_fn_801E6814.o')
result['elf_comparison'] = dict(retail=left, generated=right,
    raw_text_equal=a == b,
    raw_differing_bytes=sum(x != y for x, y in zip(a, b)) + abs(len(a)-len(b)),
    raw_differing_instructions=[hex(i) for i in range(0, max(len(a),len(b)),4) if a[i:i+4] != b[i:i+4]],
    exact_relocation_offsets_types_targets_and_addends_equal=left['relocations'] == right['relocations'])
assert left['relocations'] == right['relocations']
assert len(a) == len(b) == 632
result['dol_sha1'] = command(['sha1sum', 'build/GEDE01/main.dol'])
result['dol_sha1']['expected'] = 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
result['dol_sha1']['verified'] = result['dol_sha1']['stdout'].split()[0] == result['dol_sha1']['expected']
assert result['dol_sha1']['verified']
result['legal_audit'] = command(['python3', 'tools/legal_audit.py'])
assert result['legal_audit']['exit_code'] == 0
result['source_assembly_audit'] = command(['rg', '-n', 'asm|__asm|#pragma', 'src/game/game_fn_801E6814.c'])
assert result['source_assembly_audit']['exit_code'] == 1
result['source_sha256'] = hashlib.sha256(Path('src/game/game_fn_801E6814.c').read_bytes()).hexdigest()
result['build'] = dict(commands=['python3 configure.py', '.tools/bin/ninja -j2'], exit_code=0,
    configure_log=f'eternal-darkness-decomp/reports/GEDE01/configure-{ID}.log',
    full_log=f'eternal-darkness-decomp/reports/GEDE01/build-final-{ID}.log',
    dol_gate_lines=[line for line in (REPORTS/f'build-final-{ID}.log').read_text().splitlines() if 'main.dol:' in line])
result['interpretation'] = ('The function remains NonMatching. The complete build links the retail function; '
    'the matching DOL hash does not imply the candidate object matches. Typed widths indexing fixes all '
    'seven r-path differences recovered from commit 4dc886. Attempt 8 explicit parser exits, '
    'backward-goto and guarded-do loop trials did not improve the recovered best. '
    'Ten numeric-parser register allocation/operand rows remain.')
(REPORTS / f'verification-{ID}.json').write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps(dict(canonical=result['checks'][0]['match_percent'], strict=result['checks'][1]['match_percent'],
                     differing_rows=len(result['checks'][0]['diff_rows']), differing_bytes=result['elf_comparison']['raw_differing_bytes'],
                     relocations=len(left['relocations']), dol_sha1=result['dol_sha1']['stdout'].strip()), indent=2))
