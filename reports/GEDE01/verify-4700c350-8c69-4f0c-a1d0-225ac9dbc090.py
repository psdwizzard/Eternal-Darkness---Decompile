"""Measure this assignment's final objects without distributing binary inputs."""
import hashlib
import json
from pathlib import Path
import struct

ID = '4700c350-8c69-4f0c-a1d0-225ac9dbc090'
REPORTS = Path('reports/GEDE01')

def elf(path):
    data = path.read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    off = struct.unpack_from('>I', data, 32)[0]
    stride, count, string_index = struct.unpack_from('>HHH', data, 46)
    sections = [struct.unpack_from('>10I', data, off + i * stride) for i in range(count)]
    def contents(s):
        return data[s[4]:s[4]+s[5]]
    def string(s, offset):
        return s[offset:s.index(b'\0', offset)].decode()
    names = contents(sections[string_index])
    text_index = next(i for i,s in enumerate(sections) if string(names,s[0]) == '.text')
    relocs = []
    for s in sections:
        if s[1] != 4 or s[7] != text_index:
            continue
        symtab = sections[s[6]]
        strings = contents(sections[symtab[6]])
        for p in range(s[4],s[4]+s[5],s[9]):
            offset, info, addend = struct.unpack_from('>IIi',data,p)
            name, value, size, bind, other, section = struct.unpack_from('>IIIBBH',data,symtab[4]+(info>>8)*symtab[9])
            relocs.append({'offset':hex(offset),'type':info&255,'target':string(strings,name),'target_value':value,'addend':addend})
    text = contents(sections[text_index])
    return text, relocs

canonical = REPORTS / f'objdiff-{ID}.json'
strict = REPORTS / f'objdiff-strict-{ID}.json'
d = json.loads(canonical.read_text())
syms = {side:next(s for s in d[side]['symbols'] if s['name']=='fn_8019B4D4') for side in ['left','right']}
left_path = Path('build/GEDE01/obj/game/game_fn_8019B4D4.o')
right_path = Path('build/GEDE01/src/game/game_fn_8019B4D4.o')
left,lr = elf(left_path)
right,rr = elf(right_path)
assert len(left)==len(right)==540
assert lr == rr
rows = []
for a,b in zip(syms['left']['instructions'],syms['right']['instructions']):
    ai,bi = a.get('instruction',{}),b.get('instruction',{})
    if ai.get('formatted') != bi.get('formatted'):
        rows.append({'retail_offset':hex(int(ai.get('address',0))), 'generated_offset':hex(int(bi.get('address',0))), 'retail':ai.get('formatted'), 'generated':bi.get('formatted')})
report = {
    'assignment_id':ID,
    'canonical_command':f'build/tools/objdiff-cli diff -p . -u main/game/game_fn_8019B4D4 fn_8019B4D4 -o {canonical} --format json-pretty',
    'strict_command':f'build/tools/objdiff-cli diff -p . -u main/game/game_fn_8019B4D4 fn_8019B4D4 -c function_reloc_diffs=name_address -o {strict} --format json-pretty',
    'canonical_percent':syms['left']['match_percent'],
    'strict_percent':json.loads(strict.read_text())['left']['symbols'][0]['match_percent'],
    'canonical_strict_byte_identical':canonical.read_bytes()==strict.read_bytes(),
    'canonical_sha256':hashlib.sha256(canonical.read_bytes()).hexdigest(),
    'strict_sha256':hashlib.sha256(strict.read_bytes()).hexdigest(),
    'source_sha256':hashlib.sha256(Path('src/game/game_fn_8019B4D4.c').read_bytes()).hexdigest(),
    'retail_text_size':len(left),'generated_text_size':len(right),
    'retail_object':str(left_path),'generated_object':str(right_path),
    'raw_text_different_instruction_offsets':[hex(i) for i in range(0,len(left),4) if left[i:i+4]!=right[i:i+4]],
    'instruction_divergences':rows,
    'instruction_relocation_counts':{k:sum('relocation' in x.get('instruction',{}) for x in v['instructions']) for k,v in syms.items()},
    'elf_relocations_equal_including_targets_types_addends':lr==rr,
    'retail_elf_relocations':lr,'generated_elf_relocations':rr,
    'dol_sha1':hashlib.sha1(Path('build/GEDE01/main.dol').read_bytes()).hexdigest(),
    'required_dol_sha1':'ea24b6af954876ce072562ff39cdb4c81d32be1f',
    'build_commands':['python3 configure.py','.tools/bin/ninja -j2'],
    'build_log':f'eternal-darkness-decomp/reports/GEDE01/build-{ID}.log',
    'nonmatching_registration_retained':True,
}
assert report['dol_sha1'] == report['required_dol_sha1']
(REPORTS / f'verification-{ID}.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({k:report[k] for k in ['canonical_percent','strict_percent','canonical_strict_byte_identical','raw_text_different_instruction_offsets','instruction_relocation_counts','elf_relocations_equal_including_targets_types_addends','dol_sha1']},indent=2))
