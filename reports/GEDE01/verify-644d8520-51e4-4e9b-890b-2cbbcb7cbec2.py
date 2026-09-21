"""Independent object-byte, relocation, and linked-retail checks for this assignment.

Run from eternal-darkness-decomp after the canonical build. No artifacts are modified.
"""
import hashlib
import json
import re
import struct
from pathlib import Path

ASSIGNMENT = '644d8520-51e4-4e9b-890b-2cbbcb7cbec2'
SYMBOL = 'fn_801952E8'
ADDRESS = 0x801952E8
SIZE = 1284
EXPECTED_DOL = 'ea24b6af954876ce072562ff39cdb4c81d32be1f'


def elf(path):
    data = path.read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    shoff = struct.unpack_from('>I', data, 32)[0]
    shsize, shnum, shstr = struct.unpack_from('>HHH', data, 46)
    headers = [struct.unpack_from('>10I', data, shoff + i * shsize) for i in range(shnum)]

    def contents(h):
        return data[h[4]:h[4] + h[5]]

    def string(table, offset):
        return table[offset:table.index(b'\0', offset)].decode()

    names = contents(headers[shstr])
    sections = {string(names, h[0]): (i, h) for i, h in enumerate(headers)}
    text_index, text_header = sections['.text']
    symheader = sections['.symtab'][1]
    strings = contents(headers[symheader[6]])
    symbols = []
    for offset in range(symheader[4], symheader[4] + symheader[5], symheader[9]):
        name, value, size, info, other, section = struct.unpack_from('>IIIBBH', data, offset)
        symbols.append((string(strings, name), value, size, section))
    function = next(s for s in symbols if s[0] == SYMBOL)
    assert function[2] == SIZE and function[3] == text_index
    relocations = []
    for h in headers:
        if h[1] != 4 or h[7] != text_index:
            continue
        for offset in range(h[4], h[4] + h[5], h[9]):
            at, info, addend = struct.unpack_from('>IIi', data, offset)
            if function[1] <= at < function[1] + SIZE:
                name = symbols[info >> 8][0]
                match = re.search(r'_([0-9A-Fa-f]{8})$', name)
                assert match, name
                relocations.append({'offset': at - function[1], 'type': info & 255,
                                    'target': name, 'target_address': int(match[1], 16),
                                    'addend': addend})
    payload = contents(text_header)[function[1]:function[1] + SIZE]
    return payload, relocations


def dol_function(data):
    for index in range(18):
        offset = struct.unpack_from('>I', data, index * 4)[0]
        address = struct.unpack_from('>I', data, 0x48 + index * 4)[0]
        size = struct.unpack_from('>I', data, 0x90 + index * 4)[0]
        if address <= ADDRESS and ADDRESS + SIZE <= address + size:
            start = offset + ADDRESS - address
            return data[start:start + SIZE]
    raise AssertionError('function not found in DOL')


def main():
    target, target_relocs = elf(Path('build/GEDE01/obj/game/game_fn_801952E8.o'))
    generated, generated_relocs = elf(Path('build/GEDE01/src/game/game_fn_801952E8.o'))
    assert target == generated
    assert target_relocs == generated_relocs and len(target_relocs) == 12
    output = {'object_text_bytes_equal': True, 'object_text_size': SIZE,
              'object_text_sha1': hashlib.sha1(generated).hexdigest(),
              'relocation_targets_types_offsets_and_addends_equal': True,
              'relocations': target_relocs}
    for mode in ('canonical', 'strict'):
        report = json.loads(Path(f'reports/GEDE01/{mode}-{ASSIGNMENT}.json').read_text())
        for side in ('left', 'right'):
            symbol = next(s for s in report[side]['symbols'] if s['name'] == SYMBOL)
            assert int(symbol['size']) == SIZE and symbol['match_percent'] == 100.0
        output[mode + '_percent'] = 100.0
    built = Path('build/GEDE01/main.dol').read_bytes()
    retail = Path('orig/GEDE01/sys/main.dol').read_bytes()
    assert hashlib.sha1(built).hexdigest() == EXPECTED_DOL
    assert dol_function(built) == dol_function(retail)
    output['dol_sha1'] = hashlib.sha1(built).hexdigest()
    output['linked_function_equals_retail'] = True
    output['linked_function_sha1'] = hashlib.sha1(dol_function(built)).hexdigest()
    print(json.dumps(output, indent=2))


if __name__ == '__main__':
    main()
