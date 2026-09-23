"""Read the final ELF32 relocation records without modifying either object."""
import json
import struct
from pathlib import Path
ROOT = Path(__file__).resolve().parents[3]
REPORT = Path(__file__).resolve().parent

def inspect(path):
    data = (ROOT / path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    header = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    sections = [struct.unpack_from('>IIIIIIIIII', data, header[6] + i * header[11]) for i in range(header[12])]
    names = sections[header[13]]
    strings = data[names[4]:names[4]+names[5]]
    def cstr(blob, start):
        return blob[start:blob.index(b'\0', start)].decode()
    section_names = [cstr(strings, s[0]) for s in sections]
    rel = sections[section_names.index('.rela.text')]
    symbols = sections[rel[6]]
    sym_strings = sections[symbols[6]]
    sym_blob = data[sym_strings[4]:sym_strings[4]+sym_strings[5]]
    rows = []
    for pos in range(rel[4], rel[4]+rel[5], rel[9]):
        offset, info, addend = struct.unpack_from('>IIi', data, pos)
        symbol = struct.unpack_from('>IIIBBH', data, symbols[4] + (info >> 8) * symbols[9])
        rows.append(dict(offset=offset, type=info & 255, target=cstr(sym_blob, symbol[0]), addend=addend))
    text = sections[section_names.index('.text')]
    return dict(path=path, text_size=text[5], relocations=rows)

left = inspect('build/GEDE01/obj/game/game_fn_801E7CBC.o')
right = inspect('build/GEDE01/src/game/game_fn_801E7CBC.o')
normalize = lambda row: {key: value for key, value in row.items() if key != 'offset'}
result = dict(target=left, candidate=right,
    exact_relocations_equal=left['relocations']==right['relocations'],
    relocation_types_targets_addends_equal=[normalize(r) for r in left['relocations']]==[normalize(r) for r in right['relocations']],
    shifted_sites=[{'target_offset':l['offset'], 'candidate_offset':r['offset'], 'target':l['target']} for l,r in zip(left['relocations'],right['relocations']) if l['offset']!=r['offset']])
print(json.dumps(result, indent=2))
