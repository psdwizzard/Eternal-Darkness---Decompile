"""Bounded callback-loop lowering experiment, canonical compiler and flags."""
import json, subprocess, shlex, pathlib, hashlib
root=pathlib.Path('.')
src=root/'src/game/game_fn_8008DD78.c'
baseline=subprocess.check_output(['git','show','be9b37620e51a87bd8df8d5102a17ef2121e8375:eternal-darkness-decomp/src/game/game_fn_8008DD78.c'],text=True)
out=root/'build/GEDE01/attempt-ef0a6232'
out.mkdir(exist_ok=True)
cmd=subprocess.check_output(['.tools/bin/ninja','-t','commands','build/GEDE01/src/game/game_fn_8008DD78.o'],text=True).splitlines()[-1].split(' && ')[0]
args=shlex.split(cmd);args[-1]=str(out)
old='''            callback = 26;
            do {
                fn_801287C4(created, fn_8008DBA8, actor, callback);
                callback++;
            } while (callback < 35);'''
call='fn_801287C4(created, fn_8008DBA8, actor, callback);'
variants={
'baseline':old,
'for_lt':'            for (callback = 26; callback < 35; callback++) { '+call+' }',
'while_lt':'            callback = 26; while (callback < 35) { '+call+' callback++; }',
'do_ne':'            callback = 26; do { '+call+' callback++; } while (callback != 35);',
'for_ne':'            for (callback = 26; callback != 35; callback++) { '+call+' }',
'break_eq':'            callback = 26; for (;;) { '+call+' callback++; if (callback == 35) break; }',
'preincrement':'            callback = 25; while (++callback < 35) { '+call+' }',
'postincrement_arg':'            callback = 26; do { fn_801287C4(created, fn_8008DBA8, actor, callback++); } while (callback < 35);',
'do_le':'            callback = 26; do { '+call+' callback++; } while (callback <= 34);',
}
codes={name:baseline.replace(old,loop) for name,loop in variants.items()}
for name,decl in [('actor','void* actor;'),('object','void* object, void* resource'),('value','Data8008DD78* value;'),('data','void* data;'),('callback','int callback;'),('owner','int owner;'),('created','void* created;'),('target_id','int target_id;')]:
 codes['register_'+name]=baseline.replace(decl,'register '+decl)
codes['register_all']=baseline
for decl in ['void* actor;','void* object, void* resource','Data8008DD78* value;','void* data;','int callback;','int owner;','void* created;','int target_id;']:
 codes['register_all']=codes['register_all'].replace(decl,'register '+decl)
for where in ['loop','start','actor']:
 code=baseline.replace('    int callback;','    int callback;\n    void (*handler)(void);').replace('fn_801287C4(created, fn_8008DBA8, actor, callback);','fn_801287C4(created, handler, actor, callback);')
 anchor={'loop':'            callback = 26;','start':'    fn_8011F114(&position);','actor':'            actor = fn_801A717C(resource);'}[where]
 codes['explicit_handler_'+where]=code.replace(anchor,'    handler = fn_8008DBA8;\n'+anchor)
# Give the incoming object parameter the later actor live range, keeping an
# explicit original-object local for notification and final state updates.
codes['parameter_actor']=baseline.replace('int fn_8008DD78(void* object, void* resource)','int fn_8008DD78(void* actor, void* resource)').replace('    void* actor;','    void* object;').replace('    fn_8011F114(&position);','    object = actor;\n    fn_8011F114(&position);')
# Hold scope and lifetime fixed; vary only declaration order to test whether
# frontend symbol order breaks graph-coloring ties.
import random
rng=random.Random(8008)
decls=['    void* actor;','    void* created;','    void* target;','    Data8008DD78* value;','    void* data;','    int callback;','    int owner;','    int target_id;']
for n in range(2048):
 order=decls[:];rng.shuffle(order)
 codes['declaration_order_%02d'%n]=baseline.replace('\n'.join(decls),'\n'.join(order))
import sys
phase='refine' if '--refine' in sys.argv else ('followup' if '--followup' in sys.argv else 'initial')
if phase == 'followup':
 retained=src.read_text()
 codes={'retained':retained}
 for mask in range(1,16):
  code=retained
  for bit,name in enumerate(['actor','created','object','resource']):
   if mask & (1<<bit): code=code.replace('void* '+name,'struct Opaque8008DD78* '+name)
  codes['typed_%02d'%mask]='struct Opaque8008DD78;\n'+code
 # A separate resource result is a natural source-level alternative to reusing
 # the incoming resource parameter. Keep the argument ABI and call order.
 sep=baseline.replace('    void* actor;','    void* actor;\n    void* model;').replace('resource = fn_80072354','model = fn_80072354').replace('fn_801A717C(resource)','fn_801A717C(model)').replace('fn_800CF6AC(object, resource,','fn_800CF6AC(object, model,')
 decls2=decls[:];decls2.insert(1,'    void* model;')
 for n in range(2048):
  order=decls2[:];rng.shuffle(order)
  codes['separate_resource_%03d'%n]=sep.replace('\n'.join(decls2),'\n'.join(order))
if phase == 'refine':
 import itertools,re
 retained=src.read_text()
 block=retained.split('    Vec8008DD78 target_position;\n',1)[1].split('\n\n    fn_8011F114',1)[0]
 decls3=block.splitlines()
 codes={'retained':retained}
 # Keep actor, model, created and target declarations fixed; permute only
 # the five locals involved in the remaining early-phase color conflicts.
 slots=[i for i,line in enumerate(decls3) if any(line.endswith(' '+n+';') for n in ['owner','target_id','data','value','callback'])]
 for n,perm in enumerate(itertools.permutations([decls3[i] for i in slots])):
  order=decls3[:]
  for i,line in zip(slots,perm):order[i]=line
  codes['refine_%03d'%n]=retained.replace(block,'\n'.join(order))
results=[]
best_score=98.61789
best_code=baseline
best_name="baseline"
try:
 for name,code in codes.items():
  src.write_text(code)
  p=subprocess.run(args,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
  if p.returncode: raise RuntimeError(p.stdout)
  dest=out/(name+'.json')
  dc=['build/tools/objdiff-cli','diff','-1','build/GEDE01/obj/game/game_fn_8008DD78.o','-2',str(out/'game_fn_8008DD78.o'),'fn_8008DD78','-o',str(dest),'--format','json','-c','function_reloc_diffs=name_address']
  subprocess.run(dc,check=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
  d=json.loads(dest.read_text());l=d['left']['symbols'][0];r=d['right']['symbols'][0]
  row={'variant':name,'match_percent':l['match_percent'],'retail_bytes':l['size'],'candidate_bytes':r['size'],'source_sha256':hashlib.sha256(code.encode()).hexdigest(),'differences':sum('diff_kind' in i for i in l['instructions'])}
  results.append(row);print(json.dumps(row),flush=True)
  if row['match_percent'] > best_score:
   best_score=row['match_percent'];best_code=code;best_name=name
  if best_score == 100: break
finally:
 src.write_text(best_code)
 (out/(phase+'-results.json')).write_text(json.dumps({'compiler_command':args,'objdiff_command':dc,'results':results,'best_variant':best_name},indent=2)+'\n')
