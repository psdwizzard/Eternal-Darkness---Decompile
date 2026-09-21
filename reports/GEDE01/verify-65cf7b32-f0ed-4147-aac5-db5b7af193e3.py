"""Independent byte, explicit RELA addend, and linked DOL verification."""
import hashlib
import json
import struct
from pathlib import Path


def elf(path):
    data = Path(path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    shoff = struct.unpack_from('>I', data, 32)[0]
    size, count, names_index = struct.unpack_from('>HHH', data, 46)
    sections = [struct.unpack_from('>10I', data, shoff + i * size) for i in range(count)]
    def body(s):
        return data[s[4]:s[4] + s[5]]
    def string(blob, pos):
        return blob[pos:blob.index(b'\0', pos)].decode()
    names = body(sections[names_index])
    named = {string(names, s[0]): s for s in sections}
    symbols_section = named['.symtab']
    strings = body(sections[symbols_section[6]])
    symbols = []
    for offset in range(0, symbols_section[5], symbols_section[9]):
        name, value, length, info, other, section = struct.unpack_from('>IIIBBH', body(symbols_section), offset)
        symbols.append({'name': string(strings, name), 'value': value, 'size': length, 'section': section})
    relocations = []
    section = named['.rela.text']
    for offset in range(0, section[5], section[9]):
        address, info, addend = struct.unpack_from('>IIi', body(section), offset)
        target = symbols[info >> 8]
        relocations.append({'offset': address, 'type': info & 255, 'target': target['name'], 'target_value': target['value'], 'addend': addend})
    return body(named['.text']), relocations

left, lr = elf('build/GEDE01/obj/game/game_fn_800A3E94.o')
right, rr = elf('build/GEDE01/src/game/game_fn_800A3E94.o')
assert len(left) == len(right) == 560
assert left == right
assert lr == rr and len(lr) == 29
expected = 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
retail = Path('orig/GEDE01/sys/main.dol').read_bytes()
built = Path('build/GEDE01/main.dol').read_bytes()
assert hashlib.sha1(built).hexdigest() == expected
assert built == retail
print(json.dumps({'text_bytes': len(left), 'text_equal': left == right,
                  'text_sha256': hashlib.sha256(left).hexdigest(),
                  'relocations_equal': lr == rr, 'explicit_relocations': lr,
                  'relocation_note': 'Undefined ELF target values are zero in both objects; full linked DOL equality verifies resolved target addresses.',
                  'dol_equal': built == retail, 'dol_sha1': hashlib.sha1(built).hexdigest()}, indent=2))
