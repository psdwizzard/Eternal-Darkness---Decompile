"""Run from eternal-darkness-decomp; verify bytes, ELF relocations, diffs and DOL."""
import hashlib
import json
import struct
import subprocess
from pathlib import Path

AID = '3f4891a1-7a09-49bc-b187-ec9c737dbb60'
REPORT = Path('reports/GEDE01')
TARGET = 'fn_8014ECD8'

def read_object(path):
    data = path.read_bytes()
    header = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    assert data[:6] == b'\x7fELF\x01\x02'
    sections = [struct.unpack_from('>10I', data, header[6] + i * header[11])
                for i in range(header[12])]
    def body(section):
        return data[section[4]:section[4] + section[5]]
    def string(table, offset):
        return table[offset:].split(b'\0', 1)[0].decode()
    names = body(sections[header[13]])
    text_index = next(i for i, s in enumerate(sections)
                      if string(names, s[0]) == '.text')
    code = body(sections[text_index])
    relocations = []
    for section in sections:
        if section[1] != 4 or section[7] != text_index:
            continue
        symtab = sections[section[6]]
        symbols = body(symtab)
        strings = body(sections[symtab[6]])
        for offset in range(0, section[5], section[9]):
            address, info, addend = struct.unpack_from('>IIi', body(section), offset)
            symbol = struct.unpack_from('>IIIBBH', symbols, (info >> 8) * symtab[9])
            relocations.append({'offset': address, 'type': info & 255,
                                'target': string(strings, symbol[0]), 'addend': addend})
    return code, relocations

paths = [Path(f'build/GEDE01/{kind}/game/game_fn_8014ECD8.o') for kind in ('obj', 'src')]
objects = [read_object(path) for path in paths]
assert objects[0][0] == objects[1][0]
assert len(objects[0][0]) == 432
assert objects[0][1] == objects[1][1]
measurements = []
for suffix, config in [('-canonical', []), ('', ['-c', 'functionRelocDiffs=all'])]:
    output = REPORT / f'objdiff-{AID}{suffix}.json'
    command = ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u',
               'main/game/game_fn_8014ECD8', TARGET, *config, '-o', str(output), '--format', 'json']
    subprocess.run(command, check=True)
    diff = json.loads(output.read_text())
    for side in ('left', 'right'):
        symbol = next(s for s in diff[side]['symbols'] if s['name'] == TARGET)
        assert symbol['match_percent'] == 100
        assert int(symbol['size']) == 432
        assert all(i.get('diff_kind', 'DIFF_NONE') == 'DIFF_NONE' for i in symbol['instructions'])
    measurements.append({'command': command, 'match_percent': 100.0})
dol = Path('build/GEDE01/main.dol')
sha1 = hashlib.sha1(dol.read_bytes()).hexdigest()
assert sha1 == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
result = {'target': TARGET, 'measurements': measurements,
          'text_bytes_equal': True, 'text_size': 432,
          'text_sha256': hashlib.sha256(objects[0][0]).hexdigest(),
          'relocations_equal': True,
          'objects': [{'path': str(p), 'relocations': obj[1]} for p, obj in zip(paths, objects)],
          'dol': str(dol), 'dol_sha1': sha1}
(REPORT / f'verification-{AID}.json').write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps({'text_size': 432, 'canonical': 100.0, 'strict': 100.0,
                  'elf_relocations': len(objects[0][1]), 'dol_sha1': sha1}))
