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
# Third batch: local typed state and initialization ordering with split lifetimes.
import itertools
alias = split.replace('register State800A0140* state)', 'void* argument)').replace('    int i;', '    State800A0140* state;\n    int i;').replace('    context = fn_8006ED98(state);', '    state = (State800A0140*)argument;\n    context = fn_8006ED98(state);')
decls = ['    State800A0140* state;\n','    int i;\n', '    register void* transform;\n', '    Context800A0140* context;\n']
old = ''.join(decls)
variants = {'split_objects': split}
for n, order in enumerate(itertools.permutations(decls)):
 variants[f'local_state_order_{n}'] = alias.replace(old, ''.join(order))
variants['initialized_context'] = split.replace('    Context800A0140* context;\n','').replace('    context = fn_8006ED98(state);','    Context800A0140* context = fn_8006ED98(state);')
variants['initialized_context_first'] = split.replace('    Context800A0140* context;\n','').replace('    int i;', '    Context800A0140* context = fn_8006ED98(state);\n    int i;').replace('    context = fn_8006ED98(state);\n','')
variants['initialized_transform'] = split.replace('    register void* transform;\n','').replace('    object = fn_80201814(state->resource);\n    transform = fn_80201BC8(object);','    { void* initialObject = fn_80201814(state->resource);\n    void* transform = fn_80201BC8(initialObject);').replace('    return 1;', '    }\n    return 1;')
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
 (REPORT/f'experiments-alias-{ID}.json').write_text(json.dumps(results,indent=2)+'\n')
