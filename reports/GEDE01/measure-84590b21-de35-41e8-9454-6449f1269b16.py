"""Read-only verification. Run from eternal-darkness-decomp after the canonical build."""
import hashlib
import json
import struct
from pathlib import Path

ID = '84590b21-de35-41e8-9454-6449f1269b16'


def elf(path):
    data = Path(path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    shoff = struct.unpack_from('>I', data, 32)[0]
    shentsize, shnum, shstrndx = struct.unpack_from('>HHH', data, 46)
    sections = [struct.unpack_from('>10I', data, shoff + i * shentsize) for i in range(shnum)]

    def payload(section):
        return data[section[4]:section[4] + section[5]]

    def string(table, offset):
        return table[offset:table.index(b'\0', offset)].decode()

    names = payload(sections[shstrndx])
    by_name = {string(names, s[0]): s for s in sections}
    symtab = by_name['.symtab']
    symdata = payload(symtab)
    strings = payload(sections[symtab[6]])
    symbols = [string(strings, struct.unpack_from('>I', symdata, i)[0]) for i in range(0, len(symdata), 16)]
    relocs = []
    reladata = payload(by_name['.rela.text'])
    for i in range(0, len(reladata), 12):
        offset, info, addend = struct.unpack_from('>IIi', reladata, i)
        relocs.append({'offset': offset, 'type': info & 255, 'target': symbols[info >> 8], 'addend': addend})
    return payload(by_name['.text']), relocs


def dol(path):
    data = Path(path).read_bytes()
    header = struct.unpack_from('>54I', data)
    address = 0x80650608
    constants = []
    for i in range(18):
        offset, start, size = header[i], header[18 + i], header[36 + i]
        if start <= address and address + 4 <= start + size:
            position = offset + address - start
            raw = data[position:position + 4]
            constants.append({'address': hex(address), 'file_offset': position, 'bytes_hex': raw.hex(), 'float32': struct.unpack('>f', raw)[0]})
    return {'path': path, 'sha1': hashlib.sha1(data).hexdigest(), 'divisor': constants}


paths = ['build/GEDE01/obj/game/game_fn_80154F74.o', 'build/GEDE01/src/game/game_fn_80154F74.o']
left, lr = elf(paths[0])
right, rr = elf(paths[1])
keys = lambda rels: [(r['type'], r['target'], r['addend']) for r in rels]
canonical = json.loads(Path(f'reports/GEDE01/objdiff-{ID}-canonical.json').read_text())
strict = json.loads(Path(f'reports/GEDE01/objdiff-{ID}.json').read_text())
result = {
    'target_object': paths[0], 'candidate_object': paths[1],
    'canonical_percent': canonical['left']['sections'][0]['match_percent'],
    'relocation_strict_percent': strict['left']['sections'][0]['match_percent'],
    'target_text_size': len(left), 'candidate_text_size': len(right),
    'target_text_sha256': hashlib.sha256(left).hexdigest(),
    'candidate_text_sha256': hashlib.sha256(right).hexdigest(),
    'text_byte_identical': left == right,
    'equal_bytes_at_same_offset': sum(a == b for a, b in zip(left, right)),
    'unequal_instruction_offsets': [i for i in range(0, max(len(left), len(right)), 4) if left[i:i+4] != right[i:i+4]],
    'target_relocations': lr, 'candidate_relocations': rr,
    'relocation_type_target_addend_sequence_equal': keys(lr) == keys(rr),
    'relocation_offsets_equal': [r['offset'] for r in lr] == [r['offset'] for r in rr],
    'dol': [dol('orig/GEDE01/sys/main.dol'), dol('build/GEDE01/main.dol')],
}
print(json.dumps(result, indent=2))
assert len(left) == len(right) == 340
assert keys(lr) == keys(rr) and len(lr) == 6
assert all(x['sha1'] == 'ea24b6af954876ce072562ff39cdb4c81d32be1f' for x in result['dol'])
assert all(x['divisor'][0]['bytes_hex'] == '42900000' for x in result['dol'])
