import json, subprocess, hashlib, difflib
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
SRC = ROOT / 'src/game/game_fn_800A0140.c'
ID = 'c59a1443-b809-419b-b726-4d3272c89ce2'
REPORT = ROOT / 'reports/GEDE01'
base = subprocess.check_output(['git','show','3215b21547e8423246b673d4d6b9214e06b57040:eternal-darkness-decomp/src/game/game_fn_800A0140.c'], cwd=ROOT, text=True)
split = base.replace('    void* object;', '    void* object;\n    void* lateObject;\n    void* finalObject;').replace('            object = fn_80201814(state->resource);', '            lateObject = fn_80201814(state->resource);').replace('            object = fn_80201814(fn_80036D38(object)->resource);', '            finalObject = fn_80201814(fn_80036D38(lateObject)->resource);').replace('fn_802020B4(object, 0);','fn_802020B4(finalObject, 0);')
variants = {
 'baseline': base,
 'split_objects': split,
 'block_objects': split.replace('    void* lateObject;\n    void* finalObject;\n','').replace('        if (context->counter >= 40) {','        if (context->counter >= 40) {\n            void* lateObject;\n            void* finalObject;'),
 'remove_register': base.replace('register ', ''),
 'split_remove_register': split.replace('register ', ''),
 'register_loop': base.replace('    int i;', '    register int i;'),
 'register_object': base.replace('    void* object;', '    register void* object;'),
}
results=[]
best=base
bestscore=0
try:
 for name, source in variants.items():
  SRC.write_text(source)
  cmd=['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_800A0140.o']
  build=subprocess.run(cmd,cwd=ROOT,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
  rec={'name':name,'source_sha256':hashlib.sha256(source.encode()).hexdigest(),'patch_from_base':''.join(difflib.unified_diff(base.splitlines(True),source.splitlines(True))),'build_command':cmd,'build_exit':build.returncode,'build_raw':build.stdout}
  if build.returncode==0:
   out=REPORT/f'variant-{name}-{ID}.json'
   cmd=['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_800A0140','-o',str(out.relative_to(ROOT)),'fn_800A0140']
   run=subprocess.run(cmd,cwd=ROOT,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
   rec.update(objdiff_command=cmd,objdiff_exit=run.returncode,objdiff_raw=run.stdout,raw_file='eternal-darkness-decomp/'+str(out.relative_to(ROOT)))
   d=json.loads(out.read_text()); sym=next(s for s in d['left']['symbols'] if s['name']=='fn_800A0140'); right=next(s for s in d['right']['symbols'] if s['name']=='fn_800A0140')
   rec.update(score=sym['match_percent'],size=right['size'])
   if rec['score']>bestscore: bestscore=rec['score']; best=source
  results.append(rec)
  print(name,rec.get('score'),rec.get('size'),flush=True)
finally:
 SRC.write_text(best)
 (REPORT/f'experiments-{ID}.json').write_text(json.dumps(results,indent=2)+'\n')
