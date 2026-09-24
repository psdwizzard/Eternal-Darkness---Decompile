"""Record canonical build, strict comparison, bytes, relocations, hash and audit."""
import collections, hashlib, json, subprocess, sys
from pathlib import Path
root=Path(__file__).resolve().parents[2]
report=root/'reports/GEDE01'
aid='625a7dba-c44c-421d-8849-f453fcdeb340'
records=[]
def run(cmd):
    p=subprocess.run(cmd,cwd=root,text=True,capture_output=True)
    records.append({'cwd':'eternal-darkness-decomp','argv':cmd,'returncode':p.returncode,'stdout':p.stdout,'stderr':p.stderr})
    (report/f'verification-{aid}.json').write_text(json.dumps(records,indent=2)+'\n')
    if p.returncode: raise RuntimeError(records[-1])
    return p.stdout
run(['python3','configure.py'])
run(['.tools/bin/ninja','-j2'])
run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80198C8C.o'])
run(['.tools/bin/ninja','-t','commands','build/GEDE01/src/game/game_fn_80198C8C.o'])
run(['build/tools/objdiff-cli','--version'])
a='build/GEDE01/obj/game/game_fn_80198C8C.o'
b='build/GEDE01/src/game/game_fn_80198C8C.o'
for tag,opts in [('canonical',[]),('strict',['-c','function_reloc_diffs=name_address'])]:
    filename=f'objdiff-{aid}.json' if tag=='strict' else f'canonical-{aid}.json'
    run(['build/tools/objdiff-cli','diff','-1',a,'-2',b]+opts+['--format','json','-o','reports/GEDE01/'+filename,'fn_80198C8C'])
    j=json.loads((report/filename).read_text())
    sym=next(s for s in j['left']['symbols'] if s['name']=='fn_80198C8C')
    records.append({'comparison':tag,'score':sym.get('match_percent'),'diff_kinds':dict(collections.Counter(i.get('diff_kind','DIFF_NONE') for i in sym['instructions']))})
run(['sha1sum','build/GEDE01/main.dol'])
run(['sha1sum','-c','config/GEDE01/build.sha1'])
run(['python3','tools/legal_audit.py'])
sys.dont_write_bytecode=True
sys.path.insert(0,str(root.parent/'notes/pr18-evidence'))
from elfcmp import func_info
x=func_info(root/a,'fn_80198C8C'); y=func_info(root/b,'fn_80198C8C')
records.append({'raw_elf':{'target_size':x['size'],'generated_size':y['size'],'text_identical':x['text']==y['text'],'target_text_sha256':hashlib.sha256(bytes.fromhex(x['text'])).hexdigest(),'generated_text_sha256':hashlib.sha256(bytes.fromhex(y['text'])).hexdigest(),'relocations_identical':x['relas']==y['relas'],'relocation_columns':['offset','type','target','addend'],'target_relocations':x['relas'],'generated_relocations':y['relas'],'different_instruction_offsets':[i//2 for i in range(0,min(len(x['text']),len(y['text'])),8) if x['text'][i:i+8]!=y['text'][i:i+8]]}})
records.append({'source_sha256':hashlib.sha256((root/'src/game/game_fn_80198C8C.c').read_bytes()).hexdigest(),'registration':'NonMatching; existing GC/1.3 flags unchanged','dol_scope':'Canonical DOL uses retail object for NonMatching function; DOL hash does not prove candidate match.'})
(report/f'verification-{aid}.json').write_text(json.dumps(records,indent=2)+'\n')
print(json.dumps(records[-2:],indent=2))
