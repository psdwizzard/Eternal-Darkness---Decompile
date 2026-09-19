"""Reproduce this assignment's canonical build, strict diff and byte/relocation audit."""
import hashlib
import json
import struct
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
AID = 'fb2dcd82-5d0a-4dc1-aabe-57abd0048342'
REPORTS = ROOT / 'reports/GEDE01'
records = []

def run(cmd):
    p = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    records.append(dict(command=cmd, cwd='eternal-darkness-decomp', exit_code=p.returncode, stdout=p.stdout, stderr=p.stderr))
    print(' '.join(cmd), 'exit', p.returncode, flush=True)
    assert p.returncode == 0, p.stderr
    return p.stdout

def elf(path):
    data = (ROOT / path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    shoff = struct.unpack_from('>I', data, 32)[0]
    entsize, count, strings = struct.unpack_from('>HHH', data, 46)
    headers = [struct.unpack_from('>10I', data, shoff + i * entsize) for i in range(count)]
    def section(i):
        h = headers[i]
        return data[h[4]:h[4]+h[5]]
    def name(table, offset):
        return table[offset:table.index(b'\0', offset)].decode()
    names = [name(section(strings), h[0]) for h in headers]
    text = section(names.index('.text'))
    relocs = []
    for idx,h in enumerate(headers):
        if h[1] != 4 or names[h[7]] != '.text':
            continue
        symtab = section(h[6]); strtab = section(headers[h[6]][6])
        for off in range(h[4],h[4]+h[5],h[9]):
            offset, info, addend = struct.unpack_from('>IIi',data,off)
            sym = struct.unpack_from('>IIIBBH', symtab, (info>>8)*16)
            relocs.append(dict(offset=offset,type=info&255,target=name(strtab,sym[0]),symbol_value=sym[1],addend=addend))
    return text,relocs

run(['python3','configure.py'])
run(['.tools/bin/ninja','-j2'])
run(['.tools/bin/ninja','-t','commands','build/GEDE01/src/game/game_fn_80063124.o'])
run(['build/tools/objdiff-cli','--version'])
run(['sha256sum','compilers/GC/1.3/mwcceppc.exe','src/game/game_fn_80063124.c'])
run(['git','diff','3a9f1d06d1b5271fdf5167b8ac12d0fab7591318','--','src/game/game_fn_80063124.c'])
config=json.loads((ROOT/'objdiff.json').read_text())
unit=next(x for x in config['units'] if x['name']=='main/game/game_fn_80063124')
scores={}
for strict in [False,True]:
    filename = f'objdiff-{AID}.json' if strict else f'objdiff-canonical-{AID}.json'
    cmd=['build/tools/objdiff-cli','diff','-p','.','-u',unit['name'],'fn_80063124','-o',f'reports/GEDE01/{filename}','--format','json-pretty']
    if strict:cmd += ['-c','function_reloc_diffs=name_address']
    run(cmd)
    d=json.loads((REPORTS/filename).read_text())
    s=next(s for s in d['left']['symbols'] if s['name']=='fn_80063124')
    scores['strict' if strict else 'canonical']=s['match_percent']
run(['sha1sum','build/GEDE01/main.dol','orig/GEDE01/sys/main.dol'])
run(['sha1sum','-c','config/GEDE01/build.sha1'])
run(['python3','tools/legal_audit.py'])
for path in [unit['target_path'],unit['base_path']]:
    run(['readelf','-rW',path])
a,ar=elf(unit['target_path']);b,br=elf(unit['base_path'])
mismatches=[]
for offset in range(0,min(len(a),len(b)),4):
    if a[offset:offset+4] != b[offset:offset+4]:
        mismatches.append(dict(offset=hex(offset),target_word=a[offset:offset+4].hex(),candidate_word=b[offset:offset+4].hex()))
assert ar==br and len(ar)==19
assert hashlib.sha1((ROOT/'build/GEDE01/main.dol').read_bytes()).hexdigest()=='ea24b6af954876ce072562ff39cdb4c81d32be1f'
result=dict(commands=records,unit=unit,objdiff_project_options={k:v for k,v in config.items() if k!='units'},scores=scores,target_text_size=len(a),candidate_text_size=len(b),instruction_word_mismatches=mismatches,target_relocations=ar,candidate_relocations=br,relocations_equal=ar==br,nonmatching_note='The canonical build links the retail split for this NonMatching TU. Its correct DOL hash does not establish a match for the C candidate.')
(REPORTS/f'verification-{AID}.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps(dict(scores=scores,mismatches=mismatches,relocations=len(ar)),indent=2))
