"""Reproduce assignment verification from eternal-darkness-decomp/. Read-only on inputs."""
import hashlib, json, struct, subprocess
from datetime import datetime, timezone
from pathlib import Path

assignment = 'f4fb9fd0-4574-4a86-a8ab-ee5358f036f4'
report = Path(f'reports/GEDE01/verification-{assignment}.json')
result = {'assignment_id':assignment, 'cwd':'eternal-darkness-decomp', 'started_utc':datetime.now(timezone.utc).isoformat(), 'commands':[]}

def run(args):
    proc = subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    result['commands'].append({'argv':args,'exit_code':proc.returncode,'output':proc.stdout})
    report.write_text(json.dumps(result,indent=2)+'\n')
    if proc.returncode:
        raise SystemExit(f'Command failed: {args}')
    return proc.stdout

run(['python3','configure.py'])
run(['.tools/bin/ninja','-j2'])
run(['.tools/bin/ninja','-t','commands','build/GEDE01/src/game/game_fn_8006330C.o'])
for name, config in [('canonical',[]),('strict',['-c','functionRelocDiffs=all'])]:
    path = f'reports/GEDE01/objdiff-{assignment}'+('-canonical' if name=='canonical' else '')+'.json'
    run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_8006330C','fn_8006330C','-o',path,'--format','json']+config)
    data = json.loads(Path(path).read_text())
    result[name] = {side:{key:symbol.get(key) for key in ['size','match_percent']} for side in ['left','right'] for symbol in data[side]['symbols'] if symbol['name']=='fn_8006330C'}
sha = run(['sha1sum','build/GEDE01/main.dol','orig/GEDE01/sys/main.dol'])
assert all(line.split()[0]=='ea24b6af954876ce072562ff39cdb4c81d32be1f' for line in sha.splitlines())
result['dol_note'] = 'The function remains registered NonMatching. The full DOL build uses its retail object, not this unmatched candidate; the hash verifies the required canonical project build.'
run(['python3','tools/legal_audit.py'])
run(['git','diff','--check'])
run(['sha256sum','src/game/game_fn_8006330C.c','compilers/GC/1.3/mwcceppc.exe'])
run(['git','diff','--','configure.py','config/GEDE01/splits.txt'])

def read_object(path):
    data = Path(path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    shoff=struct.unpack_from('>I',data,32)[0]
    entsize,count,stridx=struct.unpack_from('>HHH',data,46)
    sections=[struct.unpack_from('>10I',data,shoff+i*entsize) for i in range(count)]
    def string(section, offset):
        begin=sections[section][4]+offset
        return data[begin:data.index(b'\0',begin)].decode('ascii')
    def secname(i): return string(stridx,sections[i][0])
    ti=next(i for i in range(count) if secname(i)=='.text')
    text_section=sections[ti]
    text=data[text_section[4]:text_section[4]+text_section[5]]
    relocs=[]
    for sec in sections:
        if sec[1]!=4 or sec[7]!=ti: continue
        symtab=sections[sec[6]]
        for off in range(sec[4],sec[4]+sec[5],sec[9] or 12):
            address,info,addend=struct.unpack_from('>IIi',data,off)
            name,value,size,flags,other,section=struct.unpack_from('>IIIBBH',data,symtab[4]+(info>>8)*(symtab[9] or 16))
            symbol=string(symtab[6],name)
            relocs.append({'offset':address,'type':info&255,'target':symbol,'addend':addend,'target_value':value,'target_section':secname(section) if 0<section<count else section})
    return text,relocs
left,lr=read_object('build/GEDE01/obj/game/game_fn_8006330C.o')
right,rr=read_object('build/GEDE01/src/game/game_fn_8006330C.o')
result['relocations']={'retail':lr,'candidate':rr,'retail_count':len(lr),'candidate_count':len(rr),'exact_offset_type_target_addend_match':lr==rr}
result['bytes']={'retail_size':len(left),'candidate_size':len(right),'exact_match':left==right,'retail_sha256':hashlib.sha256(left).hexdigest(),'candidate_sha256':hashlib.sha256(right).hexdigest(),'differing_bytes':sum(a!=b for a,b in zip(left,right))+abs(len(left)-len(right)),'different_instruction_words':[{'offset':i,'retail':left[i:i+4].hex(),'candidate':right[i:i+4].hex()} for i in range(0,max(len(left),len(right)),4) if left[i:i+4]!=right[i:i+4]]}
result['finished_utc']=datetime.now(timezone.utc).isoformat()
report.write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps({k:result[k] for k in ['canonical','strict','bytes']},indent=2))
print('Relocation entries:',len(lr),len(rr),'exact:',lr==rr)
