"""Assignment-specific verification; run from eternal-darkness-decomp."""
import hashlib
import json
from pathlib import Path
import struct
import subprocess

ID = 'da34faef-c09f-4102-84cd-15e6d8f2a990'
PREFIX = Path('reports/GEDE01')

def run(args):
    p = subprocess.run(args, text=True, capture_output=True)
    record = {'command': args, 'returncode': p.returncode,
              'stdout': p.stdout, 'stderr': p.stderr}
    assert p.returncode == 0, record
    return record

def elf(path):
    data = Path(path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    shoff = struct.unpack_from('>I', data, 32)[0]
    entsize, count, names_index = struct.unpack_from('>HHH', data, 46)
    sections = [struct.unpack_from('>10I', data, shoff+i*entsize) for i in range(count)]
    def contents(section):
        return data[section[4]:section[4]+section[5]]
    def string(table, offset):
        return table[offset:table.index(b'\0', offset)].decode()
    names = contents(sections[names_index])
    section_names = [string(names, section[0]) for section in sections]
    text_section = contents(sections[section_names.index('.text')])
    relocations = []
    for section in sections:
        if section[1] != 4:
            continue
        symtab = sections[section[6]]
        strings = contents(sections[symtab[6]])
        for off in range(section[4], section[4]+section[5], section[9]):
            address, info, addend = struct.unpack_from('>IIi', data, off)
            symbol_offset = symtab[4] + (info >> 8)*symtab[9]
            name, value, size, flags, other, index = struct.unpack_from('>IIIBBH', data, symbol_offset)
            relocations.append({'section': section_names[section[7]], 'offset': address,
                                'type': info & 255, 'target': string(strings, name),
                                'addend': addend, 'target_value': value})
    return {'path': path, 'text_size': len(text_section),
            'text_sha256': hashlib.sha256(text_section).hexdigest(),
            'relocations': relocations}, text_section

canonical = PREFIX / ('objdiff-'+ID+'-canonical.json')
strict = PREFIX / ('objdiff-'+ID+'.json')
commands = [run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u',
                 'main/game/game_fn_801DD71C', '-o', str(canonical), '--format', 'json-pretty']),
            run(['build/tools/objdiff-cli', 'diff', '-1', 'build/GEDE01/obj/game/game_fn_801DD71C.o',
                 '-2', 'build/GEDE01/src/game/game_fn_801DD71C.o', '-c', 'functionRelocDiffs=all',
                 '-o', str(strict), '--format', 'json-pretty'])]
scores = {}
for name, path in [('canonical', canonical), ('relocation_strict', strict)]:
    report = json.loads(path.read_text())
    symbol = next(s for s in report['left']['symbols'] if s['name'] == 'fn_801DD71C')
    scores[name] = symbol['match_percent']
    assert scores[name] == 100.0
retail, retail_text = elf('build/GEDE01/obj/game/game_fn_801DD71C.o')
generated, generated_text = elf('build/GEDE01/src/game/game_fn_801DD71C.o')
assert retail_text == generated_text
assert retail['relocations'] == generated['relocations']
dol = hashlib.sha1(Path('build/GEDE01/main.dol').read_bytes()).hexdigest()
assert dol == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
commands.append(run(['sha1sum', 'build/GEDE01/main.dol']))
commands.append(run(['python3', 'tools/legal_audit.py']))
report = {'assignment_id': ID, 'command_cwd': 'eternal-darkness-decomp',
          'scores': scores, 'raw_commands': commands,
          'retail': retail, 'generated': generated,
          'text_bytes_equal': True, 'relocations_equal_including_offsets_targets_types_addends': True,
          'dol_sha1': dol, 'source_sha256': hashlib.sha256(Path('src/game/game_fn_801DD71C.c').read_bytes()).hexdigest(),
          'compiler': 'GC/1.3', 'compiler_policy': 'Unchanged canonical flags, including -use_lmw_stmw on',
          'registration': 'Matching; generated C object linked into main.dol',
          'build_command': 'python3 configure.py && .tools/bin/ninja -j2',
          'historical_source': {'commit': 'eaebf8f52388c1324ec07a4db1a07e5ea74ae239',
                                'identical_to_accepted_base': True, 'strict_score': 87.9885},
          'findings': ['Corrected reversed fifth and tenth fn_801CE594 arguments.',
                       'Typed table indexing reproduces base/index temporary allocation.',
                       'Separated address-taken output locals and object lookup lifetime; reused scalar result for table identifier.',
                       'Narrow u16 constructor extents reproduce final argument scheduling.',
                       'Byte count and rows parameters reproduce first memcpy scheduling.']}
(PREFIX / ('verification-'+ID+'.json')).write_text(json.dumps(report, indent=2)+'\n')
print(json.dumps({'scores': scores, 'text_bytes_equal': True, 'relocations': len(retail['relocations']), 'dol_sha1': dol}))
