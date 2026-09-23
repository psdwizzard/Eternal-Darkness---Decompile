"""Run from eternal-darkness-decomp; retain raw canonical verification evidence."""
import hashlib
import json
from pathlib import Path
import struct
import subprocess

A='f52e444a-fa93-4010-be9f-cce8916b6953'
R=Path('reports/GEDE01')
OUT=R / ('objdiff-'+A+'.json')
doc=dict(assignment_id=A, commands=[], comparison_settings=dict(canonical='objdiff defaults from unchanged objdiff.json', strict='function_reloc_diffs=name_address'), experiments='eternal-darkness-decomp/'+str(R/('experiments-'+A+'.json')))

def save(): OUT.write_text(json.dumps(doc,indent=2)+'\n')
def run(args):
    p=subprocess.run(args, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    d=dict(argv=args,cwd='eternal-darkness-decomp',exit_code=p.returncode,stdout=p.stdout,stderr=p.stderr)
    doc['commands'].append(d);save()
    print('exit',p.returncode,' '.join(args),flush=True)
    if p.returncode: raise RuntimeError(d)
    return d

def relocations(path):
    b=Path(path).read_bytes()
    assert b[:6]==b'\x7fELF\x01\x02'
    h=struct.unpack_from('>16sHHIIIIIHHHHHH',b)
    shoff,shsize,shnum,shstr=h[6],h[11],h[12],h[13]
    sections=[struct.unpack_from('>10I',b,shoff+i*shsize) for i in range(shnum)]
    def data(s):return b[s[4]:s[4]+s[5]]
    def string(table,offset):return table[offset:table.index(b'\0',offset)].decode()
    names=data(sections[shstr]); result=[]
    for s in sections:
        if s[1]!=4:continue
        syms=sections[s[6]]; strings=data(sections[syms[6]])
        for offset in range(s[4],s[4]+s[5],s[9]):
            at,info,addend=struct.unpack_from('>IIi',b,offset)
            sym=struct.unpack_from('>IIIBBH',b,syms[4]+(info>>8)*syms[9])
            name=string(strings,sym[0])
            if not name and sym[5]<len(sections):name=string(names,sections[sym[5]][0])
            result.append(dict(section=string(names,sections[s[7]][0]),offset=at,type=info&255,target=name,target_value=sym[1],addend=addend))
    return dict(path='eternal-darkness-decomp/'+path,sha256=hashlib.sha256(b).hexdigest(),relocations=result)

run(['python3','configure.py'])
run(['.tools/bin/ninja','-j2'])
run(['.tools/bin/ninja','-j2','-v','build/GEDE01/src/game/game_fn_800D3620.o'])
run(['sha1sum','build/GEDE01/main.dol'])
assert hashlib.sha1(Path('build/GEDE01/main.dol').read_bytes()).hexdigest()=='ea24b6af954876ce072562ff39cdb4c81d32be1f'
for setting in ['canonical','strict']:
    tmp=R/('raw-'+A+'.json')
    cmd=['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_800D3620','fn_800D3620','--format','json-pretty','-o',str(tmp)]
    if setting=='strict':cmd+=['-c','function_reloc_diffs=name_address']
    run(cmd)
    doc[setting]=json.loads(tmp.read_text());tmp.unlink();save()
l=relocations('build/GEDE01/obj/game/game_fn_800D3620.o')
r=relocations('build/GEDE01/src/game/game_fn_800D3620.o')
doc['elf_relocations']=dict(retail=l,generated=r)
keys=['section','type','target','target_value','addend']
doc['relocation_targets_and_addends_equal']=([{k:x[k] for k in keys} for x in l['relocations']]==[{k:x[k] for k in keys} for x in r['relocations']])
assert doc['relocation_targets_and_addends_equal']
assert len(l['relocations'])==len(r['relocations'])==11
run(['python3','tools/legal_audit.py'])
save()
