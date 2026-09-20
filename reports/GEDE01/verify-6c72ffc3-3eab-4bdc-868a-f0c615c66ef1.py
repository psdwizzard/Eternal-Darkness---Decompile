"""Assignment verification; run from eternal-darkness-decomp after experiments."""
import hashlib,json,re,subprocess,time
from pathlib import Path
ID='6c72ffc3-3eab-4bdc-868a-f0c615c66ef1'
R=Path('reports/GEDE01')
SOURCE=Path('src/game/game_fn_80120B58.c')
CANONICAL=R/('objdiff-'+ID+'.json')
STRICT=R/('objdiff-strict-'+ID+'.json')
VERIFY=R/('verification-'+ID+'.json')
LOG={'version':1,'assignment_id':ID,'target':'fn_80120B58','compiler_policy':'Unmodified canonical GC/1.3 settings from python3 configure.py; no pragmas, flag overrides, object transformations, or registration changes.','source':SOURCE.read_text(),'source_sha256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),'commands':[],'dol_scope':'The source remains NonMatching. The canonical matching build links the retail split object for this function; the DOL hash does not prove this C source matches.','started_utc':time.strftime('%Y-%m-%dT%H:%M:%SZ',time.gmtime())}

def save(): VERIFY.write_text(json.dumps(LOG,indent=2)+'\n')
def run(cmd):
    p=subprocess.run(cmd,capture_output=True,text=True)
    LOG['commands'].append({'cwd':'eternal-darkness-decomp','argv':cmd,'exit_code':p.returncode,'stdout':p.stdout,'stderr':p.stderr})
    save()
    print(' '.join(cmd), 'exit',p.returncode,flush=True)
    if p.returncode: raise RuntimeError(p.stderr or p.stdout)
    return p.stdout

run(['git','rev-parse','HEAD'])
run(['python3','configure.py'])
# Delete only generated local link outputs to require a fresh link and DOL conversion.
LOG['removed_generated_link_outputs']=[]
for name in ['build/GEDE01/main.elf','build/GEDE01/main.dol','build/GEDE01/ok']:
    p=Path(name)
    if p.exists(): p.unlink(); LOG['removed_generated_link_outputs'].append(name)
save()
run(['.tools/bin/ninja','-j2'])
run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80120B58.o'])
run(['.tools/bin/ninja','-t','commands','build/GEDE01/src/game/game_fn_80120B58.o'])
run(['build/tools/objdiff-cli','--version'])
run(['sha256sum','compilers/GC/1.3/mwcceppc.exe'])
common=['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80120B58','fn_80120B58']
run(common+['-o',str(CANONICAL),'--format','json-pretty'])
run(common+['-o',str(STRICT),'--format','json-pretty','-c','function_reloc_diffs=name_address'])
for label,path in [('canonical',CANONICAL),('relocation_strict',STRICT)]:
    d=json.loads(path.read_text())
    left=next(s for s in d['left']['symbols'] if s['name']=='fn_80120B58')
    right=next(s for s in d['right']['symbols'] if s['name']=='fn_80120B58')
    LOG[label]={'report':'eternal-darkness-decomp/'+str(path),'match_percent':left['match_percent'],'retail_size':left['size'],'generated_size':right['size']}
    if label=='canonical':
        LOG['instruction_differences']=[{'offset':hex(int(a['instruction'].get('address','0'))),'retail':a['instruction']['formatted'],'generated':b['instruction']['formatted']} for a,b in zip(left['instructions'],right['instructions']) if a['instruction']['formatted']!=b['instruction']['formatted']]
objects=['build/GEDE01/obj/game/game_fn_80120B58.o','build/GEDE01/src/game/game_fn_80120B58.o']
relocations=[]
for obj in objects:
    raw=run(['build/binutils/powerpc-eabi-readelf','-rW',obj])
    parsed=[]
    for line in raw.splitlines():
        m=re.match(r'^([0-9a-fA-F]+)\s+[0-9a-fA-F]+\s+(R_\S+)\s+[0-9a-fA-F]+\s+(\S+)\s+([+-])\s+(\S+)$',line)
        if m:
            offset,kind,target,sign,addend=m.groups()
            parsed.append({'offset':int(offset,16),'type':kind,'target':target,'addend':int(sign+addend,16)})
    relocations.append(parsed)
    run(['build/binutils/powerpc-eabi-objdump','-dr',obj])
assert len(relocations[0])==3 and relocations[0]==relocations[1]
LOG['relocations']={'retail':relocations[0],'generated':relocations[1],'equal_offsets_types_targets_and_addends':True}
raw=run(['sha1sum','build/GEDE01/main.dol'])
assert raw.split()[0]=='ea24b6af954876ce072562ff39cdb4c81d32be1f'
LOG['dol_sha1']=raw.split()[0]
run(['python3','tools/legal_audit.py'])
run(['git','diff','--exit-code','--','src/game/game_fn_80120B58.c','configure.py','config/GEDE01/splits.txt','reports/GEDE01/progress.json','README.md'])
run(['git','diff','--check'])
run(['git','status','--short'])
LOG['preserved_attempts_reviewed']=[]
for commit,assignment in [('e8d96369e80c8d545f7b385aed1523275516c553','08525565-6803-4a52-83d1-fecee86ed58c'),('13222fdf9e5c13708d8d9e07d74fcb2ebc50605f','be2ee0c6-fde1-4613-8f8d-08790017ae4f'),('8b6f07fa7b8d26ccd3d9134eadcad3dd326d6963','b56c13ff-dbe2-47db-aa18-c52325820125'),('bdd0497220229595e218dc67a83c0b04602ebb69','b0954b8f-aaa7-4c88-ac13-3ee97edc8f91'),('0db1dacd3051c88a4f3145ff9fcde93c807ab36f','f9393b4d-eb02-45e8-b573-2c121f93b4fc')]:
    raw=run(['git','show',commit+':eternal-darkness-decomp/reports/GEDE01/durable-'+assignment+'.json'])
    LOG['preserved_attempts_reviewed'].append({'commit':commit,'envelope':json.loads(raw)})
raw=run(['git','show','0db1dacd3051c88a4f3145ff9fcde93c807ab36f:eternal-darkness-decomp/src/game/game_fn_80120B58.c'])
assert raw==SOURCE.read_text()
LOG['reconciliation']='The accepted base already contains exactly the source preserved in 0db1dacd3051c88a4f3145ff9fcde93c807ab36f. The final source and NonMatching registration remain unchanged.'
LOG['finished_utc']=time.strftime('%Y-%m-%dT%H:%M:%SZ',time.gmtime())
save()
