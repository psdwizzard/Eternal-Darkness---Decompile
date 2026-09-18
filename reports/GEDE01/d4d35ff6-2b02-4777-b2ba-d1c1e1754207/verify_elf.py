"""Run from eternal-darkness-decomp; compare the target unit's ELF32 bytes and RELA records."""
import hashlib
import json
import struct
from pathlib import Path


def read(path):
    data = Path(path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    hdr = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    shoff, shentsize, shnum, shstrndx = hdr[6], hdr[11], hdr[12], hdr[13]
    sections = [struct.unpack_from('>IIIIIIIIII', data, shoff + i * shentsize) for i in range(shnum)]
    def contents(section):
        return data[section[4]:section[4] + section[5]]
    def string(table, offset):
        return table[offset:table.index(b'\0', offset)].decode()
    names = contents(sections[shstrndx])
    text_index = next(i for i, sec in enumerate(sections) if string(names, sec[0]) == '.text')
    code = contents(sections[text_index])
    relocs = []
    for sec in sections:
        if sec[7] != text_index or sec[1] != 4:
            continue
        symbols = sections[sec[6]]
        strings = contents(sections[symbols[6]])
        for off in range(sec[4], sec[4] + sec[5], sec[9]):
            offset, info, addend = struct.unpack_from('>IIi', data, off)
            symbol = struct.unpack_from('>IIIBBH', data, symbols[4] + (info >> 8) * symbols[9])
            relocs.append({'offset': offset, 'type': info & 255, 'target': string(strings, symbol[0]), 'addend': addend})
    return code, {'path': path, 'text_size': len(code), 'text_sha256': hashlib.sha256(code).hexdigest(), 'elf_relocations': relocs}

left, left_info = read('build/GEDE01/obj/game/game_fn_80058394.o')
right, right_info = read('build/GEDE01/src/game/game_fn_80058394.o')
result = {'target': left_info, 'candidate': right_info, 'text_bytes_equal': left == right,
          'relocations_equal': left_info['elf_relocations'] == right_info['elf_relocations']}
print(json.dumps(result, indent=2))
assert result['text_bytes_equal']
assert result['relocations_equal']
