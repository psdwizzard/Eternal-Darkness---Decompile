import json, subprocess, struct, re
from pathlib import Path
root = Path(__file__).resolve().parents[3]
r = Path(__file__).resolve().parent
assignment = r.name

def run(name, cmd):
    a = subprocess.run(cmd, cwd=root, text=True, capture_output=True)
    (r / (name + '.command.json')).write_text(json.dumps(dict(command=cmd, exit_code=a.returncode, stdout=a.stdout, stderr=a.stderr), indent=2) + '\n')
    assert a.returncode == 0, a.stderr
    return a.stdout

for name, options, output in [('canonical', [], r / 'canonical.json'), ('strict', ['-c', 'function_reloc_diffs=name_address'], root / ('reports/GEDE01/objdiff-' + assignment + '.json'))]:
    run(name, ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_80191034', '-o', str(output.relative_to(root)), '--format', 'json-pretty'] + options + ['fn_80191034'])
hash_output = run('dol-sha1', ['sha1sum', 'build/GEDE01/main.dol'])
assert hash_output.split()[0] == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
run('legal-audit', ['python3', 'tools/legal_audit.py'])
paths = ['build/GEDE01/obj/game/game_fn_80191034.o', 'build/GEDE01/src/game/game_fn_80191034.o']

def elf(path):
    data = (root / path).read_bytes()
    header = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    sections = [struct.unpack_from('>10I', data, header[6] + i * header[11]) for i in range(header[12])]
    def blob(s): return data[s[4]:s[4]+s[5]]
    def string(b, i): return b[i:b.index(b'\0', i)].decode()
    names = blob(sections[header[13]])
    text = next(blob(s) for s in sections if string(names,s[0]) == '.text')
    relocs = []
    for s in sections:
        if s[1] != 4 or string(names, sections[s[7]][0]) != '.text': continue
        symsec = sections[s[6]]
        strings = blob(sections[symsec[6]])
        for off in range(s[4], s[4]+s[5], s[9]):
            addr, info, addend = struct.unpack_from('>IIi', data, off)
            sym = struct.unpack_from('>IIIBBH', data, symsec[4] + (info >> 8) * symsec[9])
            relocs.append(dict(offset=addr, type=info & 255, target=string(strings,sym[0]), target_value=sym[1], addend=addend))
    return text, relocs

objects = [elf(path) for path in paths]
for name,path in zip(['retail-relocations', 'generated-relocations'],paths):
    run(name, ['readelf', '-rW', path])
canonical = json.loads((r / 'canonical.json').read_text())
strict = json.loads((root / ('reports/GEDE01/objdiff-' + assignment + '.json')).read_text())
symbols = [next(s for s in strict[side]['symbols'] if s['name'] == 'fn_80191034') for side in ['left','right']]
a,b = [s['instructions'] for s in symbols]
mismatches = [dict(offset=x['instruction'].get('address','0'), retail=x['instruction']['formatted'], generated=y['instruction']['formatted']) for x,y in zip(a,b) if x.get('diff_kind')]
def swap(s): return re.sub(r'\br(20|21)\b', lambda m: 'r21' if m[1]=='20' else 'r20', s)
summary = dict(canonical_score=canonical['left']['symbols'][0]['match_percent'], strict_score=symbols[0]['match_percent'], sizes=[s['size'] for s in symbols], canonical_equals_strict=canonical==strict, mismatch_count=len(mismatches), mismatches=mismatches, all_mismatches_are_r20_r21_swap=all(swap(m['retail']) == m['generated'] for m in mismatches), real_elf_relocations=[o[1] for o in objects], real_elf_relocations_equal=objects[0][1]==objects[1][1], objdiff_relocation_bearing_rows=[sum('relocation' in row.get('instruction',{}) for row in s['instructions']) for s in symbols], differing_instruction_byte_offsets=[i for i in range(0,len(objects[0][0]),4) if objects[0][0][i:i+4]!=objects[1][0][i:i+4]])
(r / 'measurements.json').write_text(json.dumps(summary,indent=2)+'\n')
print(json.dumps({k:v for k,v in summary.items() if k not in ['mismatches','real_elf_relocations','differing_instruction_byte_offsets']},indent=2))
