"""Measure preserved objdiff outputs and resolve ELF relocation symbols explicitly."""
from pathlib import Path
import hashlib
import json
import struct

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[2]

def elf(path):
    data = path.read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    shoff = struct.unpack_from('>I', data, 32)[0]
    entsize, count, strings = struct.unpack_from('>HHH', data, 46)
    sections = [struct.unpack_from('>10I', data, shoff + i * entsize) for i in range(count)]
    def payload(section):
        return data[section[4]:section[4] + section[5]]
    def string(table, offset):
        return table[offset:table.index(0, offset)].decode()
    names = payload(sections[strings])
    named = {string(names, s[0]): s for s in sections}
    rel = named['.rela.text']
    symtab = sections[rel[6]]
    strtab = payload(sections[symtab[6]])
    symbols = [struct.unpack_from('>IIIBBH', payload(symtab), i) for i in range(0, symtab[5], symtab[9])]
    relocations = []
    for i in range(0, rel[5], rel[9]):
        offset, info, addend = struct.unpack_from('>IIi', payload(rel), i)
        symbol = symbols[info >> 8]
        relocations.append(dict(offset=offset, type=info & 255, target=string(strtab, symbol[0]), target_value=symbol[1], target_section=symbol[5], addend=addend))
    return payload(named['.text']), relocations

measurements = {}
for name in ['baseline', 'automatic-storage', 'derived-offset', 'canonical', 'relocation-strict']:
    data = json.loads((OUT / (name + '.json')).read_text())
    a, b = [next(s for s in data[side]['symbols'] if s['name'] == 'fn_8019C3B8') for side in ['left', 'right']]
    differences = []
    for left, right in zip(a['instructions'], b['instructions']):
        if left.get('diff_kind') or right.get('diff_kind'):
            differences.append(dict(offset=left.get('instruction', {}).get('address', '0'), kind=left.get('diff_kind', right.get('diff_kind')), retail=left.get('instruction', {}).get('formatted'), candidate=right.get('instruction', {}).get('formatted')))
    def relocations(symbol):
        return [dict(address=i['instruction'].get('address', '0'), **i['instruction']['relocation']) for i in symbol['instructions'] if 'relocation' in i.get('instruction', {})]
    measurements[name] = dict(retail_size=int(a['size']), candidate_size=int(b['size']), match_percent=a['match_percent'], differences=differences, objdiff_relocation_entries=len(relocations(a)), objdiff_relocation_metadata_equal=relocations(a) == relocations(b))

left, lr = elf(ROOT / 'build/GEDE01/obj/game/game_fn_8019C3B8.o')
right, rr = elf(ROOT / 'build/GEDE01/src/game/game_fn_8019C3B8.o')
measurements['elf'] = dict(retail_relocations=lr, candidate_relocations=rr, relocations_equal=lr == rr, retail_text_sha256=hashlib.sha256(left).hexdigest(), candidate_text_sha256=hashlib.sha256(right).hexdigest(), byte_differences=sum(a != b for a, b in zip(left, right)), word_differences=sum(left[i:i+4] != right[i:i+4] for i in range(0, len(left), 4)))
assert lr == rr
assert measurements['canonical']['match_percent'] == measurements['relocation-strict']['match_percent']
assert len(measurements['canonical']['differences']) == 20
assert all(d['kind'] == 'DIFF_ARG_MISMATCH' for d in measurements['canonical']['differences'])
(OUT / 'measurements.json').write_text(json.dumps(measurements, indent=2) + '\n')
print(json.dumps({name: {k: v for k, v in m.items() if k not in ['differences', 'retail_relocations', 'candidate_relocations']} for name, m in measurements.items()}, indent=2))
