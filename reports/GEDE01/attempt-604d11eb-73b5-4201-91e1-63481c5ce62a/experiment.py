#!/usr/bin/env python3
"""Run an assignment-local patch against the accepted source with canonical tools."""
import pathlib, subprocess, json, difflib, sys
ROOT=pathlib.Path(__file__).resolve().parents[3]
REPORT=pathlib.Path(__file__).resolve().parent
SOURCE=ROOT/'src/game/game_fn_801E504C.c'
BASE='f061dad5f31cdc03c9cf00de6b89a337c4d937d6'
def baseline():
    return subprocess.check_output(['git','show',BASE+':eternal-darkness-decomp/src/game/game_fn_801E504C.c'],cwd=ROOT,text=True)
def run(name, source, hypothesis):
    patch=''.join(difflib.unified_diff(baseline().splitlines(True),source.splitlines(True),fromfile='a/eternal-darkness-decomp/src/game/game_fn_801E504C.c',tofile='b/eternal-darkness-decomp/src/game/game_fn_801E504C.c'))
    (REPORT/(name+'.patch')).write_text(patch)
    SOURCE.write_text(source)
    commands=[['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_801E504C.o'],['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_801E504C','-o',str((REPORT/(name+'.json')).relative_to(ROOT)),'-c','function_reloc_diffs=name_address','fn_801E504C']]
    record={'hypothesis':hypothesis,'source_patch':str((REPORT/(name+'.patch')).relative_to(ROOT.parent)),'commands':[]}
    for cmd in commands:
        p=subprocess.run(cmd,cwd=ROOT,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
        record['commands'].append({'argv':cmd,'cwd':'eternal-darkness-decomp','exit_code':p.returncode,'raw_output':p.stdout})
        if p.returncode: break
    if not p.returncode:
        j=json.loads((REPORT/(name+'.json')).read_text()); f=next(s for s in j['left']['symbols'] if s['name']=='fn_801E504C'); r=next(s for s in j['right']['symbols'] if s['name']=='fn_801E504C')
        record['score']=f.get('match_percent'); record['sizes']=[f['size'],r['size']]
    (REPORT/(name+'.log.json')).write_text(json.dumps(record,indent=2)+'\n')
    print(name,record.get('score'),record.get('sizes'),flush=True)
    return record
if __name__=='__main__':
    name=sys.argv[1]
    patch=(REPORT/(name+'.patch')).read_text()
    SOURCE.write_text(baseline())
    subprocess.run(['git','apply','-'],cwd=ROOT.parent,input=patch,text=True,check=True)
    run(name,SOURCE.read_text(),'Reproduction of preserved patch')
