#!/usr/bin/env python3
"""Run from eternal-darkness-decomp. Exact patches are relative to the accepted base."""
import subprocess, pathlib, json, difflib, hashlib, sys, datetime
R=pathlib.Path('reports/GEDE01/attempt-77f3dc21-8bb9-44b7-a7b2-4d320672000a')
S=pathlib.Path('src/game/game_fn_8001DFEC.c')
BASE='f48469bc132dbbaa93922081ea48a08a401123be'
baseline=subprocess.check_output(['git','show',BASE+':eternal-darkness-decomp/'+str(S)],text=True)
name=sys.argv[1]
source=S.read_text()
(R/(name+'.patch')).write_text(''.join(difflib.unified_diff(baseline.splitlines(True),source.splitlines(True),fromfile='a/eternal-darkness-decomp/'+str(S),tofile='b/eternal-darkness-decomp/'+str(S))))
record={'name':name,'timestamp_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'source_sha256':hashlib.sha256(source.encode()).hexdigest(),'commands':[]}
def run(args,output):
    p=subprocess.run(args,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    (R/(name+'-'+output)).write_text(p.stdout)
    record['commands'].append({'argv':args,'exit_code':p.returncode,'output':str(R/(name+'-'+output))})
    if p.returncode: raise RuntimeError(p.stdout)
try:
    run(['.tools/bin/ninja','-j2','-v','build/GEDE01/src/game/game_fn_8001DFEC.o'],'compiler.log')
    for mode in ['canonical','strict']:
        args=['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_8001DFEC','fn_8001DFEC','-o',str(R/(name+'-'+mode+'.json')),'--format','json-pretty']
        if mode=='strict': args+=['-c','function_reloc_diffs=name_address']
        run(args,mode+'.log')
        j=json.loads((R/(name+'-'+mode+'.json')).read_text())
        sy=next(s for s in j['left']['symbols'] if s['name']=='fn_8001DFEC')
        record[mode+'_match_percent']=sy['match_percent']
    for side,path in [('retail','obj'),('generated','src')]:
        obj='build/GEDE01/'+path+'/game/game_fn_8001DFEC.o'
        run(['build/binutils/powerpc-eabi-objdump','-dr',obj],side+'-disassembly.txt')
        run(['build/binutils/powerpc-eabi-readelf','-rW',obj],side+'-relocations.txt')
    print(name,record.get('canonical_match_percent'),record.get('strict_match_percent'))
finally:
    (R/(name+'-run.json')).write_text(json.dumps(record,indent=2)+'\n')
