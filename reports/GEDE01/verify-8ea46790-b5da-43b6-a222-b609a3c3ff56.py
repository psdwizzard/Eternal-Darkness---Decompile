#!/usr/bin/env python3
"""Run from eternal-darkness-decomp; writes only this assignment's evidence."""
import hashlib
from collections import Counter
import json
from pathlib import Path
import struct
import subprocess

ID = '8ea46790-b5da-43b6-a222-b609a3c3ff56'
OUT = Path('reports/GEDE01')
TARGET = 'fn_80068AAC'
commands = []

def run(argv):
    p = subprocess.run(argv, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    commands.append({'argv': argv, 'cwd': 'eternal-darkness-decomp',
                     'exit_code': p.returncode, 'stdout': p.stdout})
    if p.returncode:
        raise RuntimeError(p.stdout)
    return p.stdout

def symbol(data, side):
    return next(s for s in data[side]['symbols'] if s['name'] == TARGET)

def metrics(path):
    data = json.loads(path.read_text())
    a, b = (symbol(data, side) for side in ('left', 'right'))
    def count(s, reloc=False):
        return sum(bool(r.get('instruction', {}).get('relocation')) if reloc
                   else 'instruction' in r for r in s['instructions'])
    return {'match_percent': b['match_percent'],
            'retail_size': int(a['size']), 'generated_size': int(b['size']),
            'retail_instructions': count(a), 'generated_instructions': count(b),
            'retail_objdiff_relocation_bearing_instructions': count(a, True),
            'generated_objdiff_relocation_bearing_instructions': count(b, True)}

def elf_relocations(path):
    """Resolve ELF32 big-endian RELA symbol indices to names and signed addends."""
    data = Path(path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    offset = struct.unpack_from('>I', data, 32)[0]
    size, count, names = struct.unpack_from('>HHH', data, 46)
    sections = [struct.unpack_from('>10I', data, offset + i*size) for i in range(count)]
    def cstr(table, start):
        return table[start:table.index(b'\0', start)].decode()
    def contents(s):
        return data[s[4]:s[4]+s[5]]
    section_names = contents(sections[names])
    def section_name(i):
        return cstr(section_names, sections[i][0])
    rows = []
    for sec in sections:
        if sec[1] != 4:  # SHT_RELA
            continue
        syms = sections[sec[6]]
        strings = contents(sections[syms[6]])
        for pos in range(sec[4], sec[4]+sec[5], sec[9] or 12):
            at, info, addend = struct.unpack_from('>IIi', data, pos)
            name, value, length, kind, other, shndx = struct.unpack_from(
                '>IIIBBH', data, syms[4] + (info >> 8)*(syms[9] or 16))
            target = cstr(strings, name)
            if not target and shndx < len(sections):
                target = section_name(shndx)
            rows.append({'section': section_name(sec[7]), 'offset': at,
                         'type': info & 255, 'target': target, 'addend': addend})
    return rows

run(['python3', 'configure.py'])
run(['.tools/bin/ninja', '-j2'])
canonical = OUT / f'raw-{ID}.json'
strict = OUT / f'strict-{ID}.json'
base = ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u',
        'main/game/game_fn_80068AAC', TARGET]
run(base + ['-o', str(canonical), '--format', 'json'])
run(base + ['-c', 'function_reloc_diffs=all', '-o', str(strict), '--format', 'json'])
unit = next(u for u in json.loads(Path('objdiff.json').read_text())['units']
            if u['name'] == 'main/game/game_fn_80068AAC')
retail_reloc = elf_relocations(unit['target_path'])
generated_reloc = elf_relocations(unit['base_path'])
reloc = {'retail': retail_reloc, 'generated': generated_reloc,
         'sites_types_targets_and_addends_equal': retail_reloc == generated_reloc}
reloc_path = OUT / f'relocations-{ID}.json'
reloc_path.write_text(json.dumps(reloc, indent=2) + '\n')
hash_stdout = run(['sha1sum', 'orig/GEDE01/sys/main.dol', 'build/GEDE01/main.dol'])
run(['python3', 'tools/legal_audit.py'])
source = Path('src/game/game_fn_80068AAC.c').read_text()
import re
assert not re.search(r'\b(?:asm|__asm)\b|\.4byte|\.long', source)
assert 'Object(NonMatching, "game/game_fn_80068AAC.c", extra_cflags=["-use_lmw_stmw on"])' in Path('configure.py').read_text()
expected = 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
assert all(line.split()[0] == expected for line in hash_stdout.splitlines())
reloc_key = lambda rows: [(x['type'], x['target'], x['addend']) for x in rows]
report = {'version': 1, 'assignment_id': ID, 'attempt': 5, 'target': TARGET,
          'compiler': 'GC/1.3', 'unit_settings': unit, 'commands': commands,
          'canonical': metrics(canonical), 'relocation_strict': metrics(strict),
          'elf_relocations_equal': retail_reloc == generated_reloc,
          'relocation_type_target_addend_sequence_equal': reloc_key(retail_reloc) == reloc_key(generated_reloc),
          'relocation_type_target_addend_multiset_equal': Counter(reloc_key(retail_reloc)) == Counter(reloc_key(generated_reloc)),
          'retail_elf_relocation_count': len(retail_reloc),
          'generated_elf_relocation_count': len(generated_reloc),
          'raw_evidence': ['eternal-darkness-decomp/' + str(p) for p in (canonical, strict, reloc_path)],
          'reproduce': 'python3 reports/GEDE01/verify-' + ID + '.py',
          'measurement_query': 'metrics() and elf_relocations() in the reproduction script select fn_80068AAC by name and decode ELF relocation names/addends, respectively.',
          'legal_audit': {'passed': True, 'inline_assembly': False, 'independent_C_TU': True,
                          'registration': 'NonMatching; original object supplies DOL'},
          'source_sha256': hashlib.sha256(source.encode()).hexdigest(),
          'dol_sha1': expected}
(OUT / f'objdiff-{ID}.json').write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps({k: report[k] for k in ('canonical', 'relocation_strict',
      'elf_relocations_equal', 'retail_elf_relocation_count', 'generated_elf_relocation_count', 'dol_sha1')}, indent=2))
