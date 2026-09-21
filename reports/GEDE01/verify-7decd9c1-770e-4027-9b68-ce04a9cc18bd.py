"""Assignment-local read-only ELF byte and relocation verification.

Run from eternal-darkness-decomp after the canonical build completes.
"""
import hashlib
import json
import struct
import subprocess
from pathlib import Path

ASSIGNMENT = '7decd9c1-770e-4027-9b68-ce04a9cc18bd'


def inspect(path):
    data = Path(path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    shoff = struct.unpack_from('>I', data, 32)[0]
    shsize, count, names_index = struct.unpack_from('>HHH', data, 46)
    sections = [struct.unpack_from('>10I', data, shoff + i * shsize) for i in range(count)]

    def section_bytes(s):
        return data[s[4]:s[4] + s[5]]

    def string(table, offset):
        return table[offset:table.index(b'\0', offset)].decode()

    names = section_bytes(sections[names_index])
    text_index = next(i for i, s in enumerate(sections) if string(names, s[0]) == '.text')
    code = section_bytes(sections[text_index])
    relocations = []
    for section in sections:
        if section[1] != 4 or section[7] != text_index:
            continue
        symtab = sections[section[6]]
        strings = section_bytes(sections[symtab[6]])
        for pos in range(section[4], section[4] + section[5], section[9]):
            offset, info, addend = struct.unpack_from('>IIi', data, pos)
            symbol = struct.unpack_from('>IIIBBH', data, symtab[4] + (info >> 8) * symtab[9])
            name = string(strings, symbol[0])
            relocations.append(dict(offset=offset, type=info & 255, target=name, addend=addend))
    return code, sorted(relocations, key=lambda r: r['offset'])


left, left_relocs = inspect('build/GEDE01/obj/game/game_fn_801AB50C.o')
right, right_relocs = inspect('build/GEDE01/src/game/game_fn_801AB50C.o')
ninja_lines = Path('build.ninja').read_text().replace('$\n', '').splitlines()
link_inputs = next(line.split() for line in ninja_lines if line.startswith('build build/GEDE01/main.elf: link '))
result = {
    'target': 'fn_801AB50C',
    'linked_c_object': 'build/GEDE01/src/game/game_fn_801AB50C.o' in link_inputs,
    'linked_retail_object': 'build/GEDE01/obj/game/game_fn_801AB50C.o' in link_inputs,
    'source_sha256': hashlib.sha256(Path('src/game/game_fn_801AB50C.c').read_bytes()).hexdigest(),
    'text_bytes_equal': left == right,
    'retail_text_size': len(left),
    'generated_text_size': len(right),
    'retail_text_sha256': hashlib.sha256(left).hexdigest(),
    'generated_text_sha256': hashlib.sha256(right).hexdigest(),
    'relocations_equal': left_relocs == right_relocs,
    'retail_relocations': left_relocs,
    'generated_relocations': right_relocs,
    'dol_sha1': hashlib.sha1(Path('build/GEDE01/main.dol').read_bytes()).hexdigest(),
    'legal_audit': subprocess.check_output(['python3', 'tools/legal_audit.py'], text=True).strip(),
    'compiler_command': subprocess.check_output(['.tools/bin/ninja', '-t', 'commands', 'build/GEDE01/src/game/game_fn_801AB50C.o'], text=True).strip(),
}
for mode in ['canonical', 'objdiff']:
    raw = json.loads(Path(f'reports/GEDE01/{mode}-{ASSIGNMENT}.json').read_text())
    symbol = next(s for s in raw['left']['symbols'] if s['name'] == 'fn_801AB50C')
    result[mode + '_match_percent'] = symbol['match_percent']
assert result['canonical_match_percent'] == result['objdiff_match_percent'] == 100
assert result['linked_c_object'] and not result['linked_retail_object']
assert left == right and len(left) == 1948
assert left_relocs == right_relocs and len(left_relocs) == 57
assert result['dol_sha1'] == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
Path(f'reports/GEDE01/verification-{ASSIGNMENT}.json').write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps({k: v for k, v in result.items() if k not in ['retail_relocations', 'generated_relocations', 'compiler_command']}, indent=2))
