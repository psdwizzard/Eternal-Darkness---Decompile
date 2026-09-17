"""Run from eternal-darkness-decomp; verify the final matching TU and linked DOL."""
import hashlib
import json
from pathlib import Path
import struct
import subprocess

AID = 'c010e819-de0c-4571-9ff6-e1b5de78aa5d'
PREFIX = Path('reports/GEDE01')
report = {'assignment_id': AID, 'commands': [], 'compiler': 'GC/1.3',
          'compiler_policy': 'Unchanged canonical settings, including -use_lmw_stmw on.',
          'build': {'commands': ['python3 configure.py', '.tools/bin/ninja -j2'],
                    'exit_code': 0, 'raw_output': f'eternal-darkness-decomp/reports/GEDE01/build-{AID}.log'},
          'preexisting_unrelated_change': 'CLAUDE.md was modified before work began and was not edited or staged.'}

def run(argv):
    p = subprocess.run(argv, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    report['commands'].append({'argv': argv, 'exit_code': p.returncode, 'output': p.stdout})
    p.check_returncode()
    return p.stdout

for label, extra, suffix in [('canonical', [], '-canonical'),
                             ('relocation_strict', ['-c', 'function_reloc_diffs=name_address'], '')]:
    path = PREFIX / f'objdiff-{AID}{suffix}.json'
    run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_801D76A8',
         'fn_801D76A8', *extra, '-o', str(path)])
    data = json.loads(path.read_text())
    summary = {}
    for side in ('left', 'right'):
        symbol = next(s for s in data[side]['symbols'] if s['name'] == 'fn_801D76A8')
        assert symbol['match_percent'] == 100.0 and int(symbol['size']) == 752
        assert len(symbol['instructions']) == 188
        assert all(row.get('diff_kind') in (None, 'DIFF_NONE') for row in symbol['instructions'])
        summary[side] = {'match_percent': symbol['match_percent'], 'size': int(symbol['size']),
                         'instructions': len(symbol['instructions'])}
    report[label] = summary

# Decode the raw ELF sections/RELA records without masking instructions or relocations.
def elf_evidence(filename):
    blob = Path(filename).read_bytes()
    assert blob[:6] == b'\x7fELF\x01\x02'
    shoff = struct.unpack_from('>I', blob, 32)[0]
    entsize, count, string_index = struct.unpack_from('>HHH', blob, 46)
    sections = [struct.unpack_from('>10I', blob, shoff+i*entsize) for i in range(count)]
    def contents(section):
        return blob[section[4]:section[4]+section[5]]
    def cstring(table, offset):
        return table[offset:].split(b'\0', 1)[0].decode()
    names = contents(sections[string_index])
    code = None
    relocs = []
    for section in sections:
        name = cstring(names, section[0])
        if name == '.text':
            code = contents(section)
        if name == '.rela.text':
            assert section[1] == 4
            symtab = sections[section[6]]
            strings = contents(sections[symtab[6]])
            for offset in range(section[4], section[4]+section[5], section[9]):
                address, info, addend = struct.unpack_from('>IIi', blob, offset)
                sym_offset = symtab[4] + (info >> 8)*symtab[9]
                sym_name = struct.unpack_from('>I', blob, sym_offset)[0]
                relocs.append({'offset': address, 'type': info & 255,
                               'target': cstring(strings, sym_name), 'addend': addend})
    assert code is not None
    return code, {'text_size': len(code), 'text_sha256': hashlib.sha256(code).hexdigest(),
                  'relocations': relocs}

left_bytes, left = elf_evidence('build/GEDE01/obj/game/game_fn_801D76A8.o')
right_bytes, right = elf_evidence('build/GEDE01/src/game/game_fn_801D76A8.o')
assert left_bytes == right_bytes
assert left['relocations'] == right['relocations'] and len(left['relocations']) == 27
report['raw_elf'] = {'retail': left, 'generated': right, 'text_bytes_equal': True,
                     'relocation_offsets_types_targets_addends_equal': True}
run(['sha1sum', 'build/GEDE01/main.dol'])
dol_sha1 = hashlib.sha1(Path('build/GEDE01/main.dol').read_bytes()).hexdigest()
assert dol_sha1 == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
report['dol_sha1'] = dol_sha1
link_rule = next(line for line in Path('build.ninja').read_text().replace('$\n', '').splitlines()
                 if line.startswith('build build/GEDE01/main.elf:'))
assert 'build/GEDE01/src/game/game_fn_801D76A8.o' in link_rule
assert 'build/GEDE01/obj/game/game_fn_801D76A8.o' not in link_rule
report['compiled_object_linked'] = True
run(['python3', 'tools/legal_audit.py'])
run(['git', 'diff', '--check'])
run(['git', 'diff', '--cached', '--check'])
for file in ['src/game/game_fn_801D76A8.c', 'configure.py']:
    report.setdefault('source_sha256', {})[file] = hashlib.sha256(Path(file).read_bytes()).hexdigest()
(PREFIX / f'verification-{AID}.json').write_text(json.dumps(report, indent=2)+'\n')
print('PASS: canonical and relocation-strict 100%; 752 identical text bytes; 27 identical relocations including addends; compiled object linked; DOL SHA-1 and legal audit passed.')
