"""Extract ELF32 PowerPC RELA type, symbol, value and signed addend directly."""
import json
import struct
from pathlib import Path

ID = '44042081-b701-405c-8e4d-c3f5c658d9a0'
def extract(path):
    data = Path(path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    header = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    sections = [struct.unpack_from('>IIIIIIIIII', data, header[6] + i * header[11])
                for i in range(header[12])]
    def section_bytes(index):
        s = sections[index]
        return data[s[4]:s[4] + s[5]]
    def string(blob, start):
        return blob[start:blob.index(b'\0', start)].decode()
    names = section_bytes(header[13])
    result = []
    for sec in sections:
        if sec[1] != 4 or string(names, sections[sec[7]][0]) != '.text':
            continue
        symtab = sections[sec[6]]
        strings = section_bytes(symtab[6])
        for offset in range(sec[4], sec[4] + sec[5], sec[9]):
            address, info, addend = struct.unpack_from('>IIi', data, offset)
            sym = struct.unpack_from('>IIIBBH', data, symtab[4] + (info >> 8) * symtab[9])
            result.append({'offset': address, 'type': info & 255,
                           'symbol': string(strings, sym[0]), 'symbol_value': sym[1],
                           'addend': addend})
    return result
left_path = 'build/GEDE01/obj/game/game_fn_80079D24.o'
right_path = 'build/GEDE01/src/game/game_fn_80079D24.o'
left, right = extract(left_path), extract(right_path)
helpers = [r for r in right if r['symbol'] in ('_savegpr_21', '_restgpr_21')]
filtered = [r for r in right if r not in helpers]
def key(r):
    return {k:v for k,v in r.items() if k != 'offset'}
report = {'reference_object': left_path, 'candidate_object': right_path,
          'reference_relocations': left, 'candidate_relocations': right,
          'exact_relocation_records_equal': left == right,
          'extra_candidate_helper_relocations': helpers,
          'ordered_target_type_value_addend_equal_after_excluding_helpers':
              [key(r) for r in left] == [key(r) for r in filtered],
          'explanation': 'The filtered comparison diagnoses the remaining difference; it is not the strict match gate. Offsets and extra helper relocations make exact records unequal.'}
p = Path('reports/GEDE01/relocations-' + ID + '.json')
p.write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps({'reference_count':len(left), 'candidate_count':len(right),
                  'exact_records_equal':left == right,
                  'filtered_targets_types_values_addends_equal':report['ordered_target_type_value_addend_equal_after_excluding_helpers']}))
