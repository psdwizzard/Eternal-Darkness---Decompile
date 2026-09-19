"""Run from eternal-darkness-decomp; preserve trial patches and raw objdiffs."""
import difflib, json, pathlib, subprocess
A='61e0ce65-b713-4e8c-9356-0bccbc46733c'
p=pathlib.Path('src/game/game_fn_8019C4E4.c')
r=pathlib.Path('reports/GEDE01')
base=subprocess.check_output(['git','show','7de526f843b500166b14fc2667e767b9eb85606e:eternal-darkness-decomp/'+str(p)],text=True)
assignment='    cfg = config;\n    base = first;\n    self = object;\n'
late=base.replace(assignment,'').replace('    count = cfg[0];\n    entry = *(u8**)(self + 0x4C);','    count = config[0];\n    entry = *(u8**)(object + 0x4C);\n'+assignment.rstrip())
variants={'delayed-alias':late}
# Change the CFG's source traversal order without changing loop semantics.
variants['explicit-loop']=base.replace('    for (; (u8)i < count; entry += 0x38, i++) {','    goto test;\nloop:\n    {').replace('    }\n\n    fn_8018CEC0','    }\n    entry += 0x38;\n    i++;\ntest:\n    if ((u8)i < count) goto loop;\n\n    fn_8018CEC0')
# Aggregate declaration initializers precede scalar initializers, preserving load order
# while giving count/entry initialized declarations before the parameter aliases.
aggregate=base.replace('    register u8 count;\n    register u8* entry;\n','')
aggregate=aggregate.replace('    struct { u32 word; u16 half; } setup;', '    struct { u32 word; u16 half; } setup = { lbl_80651E00, lbl_80651E04 };').replace('    struct { u32 word; u16 half; } value;', '    struct { u32 word; u16 half; } value = { lbl_80651E08, lbl_80651E0C };\n    register u8 count = config[0];\n    register u8* entry = *(u8**)(object + 0x4C);')
for line in ['    setup.word = lbl_80651E00;\n','    setup.half = lbl_80651E04;\n','    value.word = lbl_80651E08;\n','    value.half = lbl_80651E0C;\n','    count = cfg[0];\n','    entry = *(u8**)(self + 0x4C);\n']:
 aggregate=aggregate.replace(line,'')
variants['aggregate-initializers']=aggregate
log=[]
try:
 for name,source in variants.items():
  p.write_text(source)
  (r/f'experiment-{A}-{name}.diff').write_text(''.join(difflib.unified_diff(base.splitlines(True),source.splitlines(True),fromfile=str(p),tofile=str(p))))
  commands=[]
  for cmd in [['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_8019C4E4.o'],['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_8019C4E4','fn_8019C4E4','-o',str(r/f'experiment-{A}-{name}.json'),'--format','json','-c','function_reloc_diffs=name_address']]:
   x=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
   commands.append({'argv':cmd,'exit_code':x.returncode,'raw_output':x.stdout})
   if x.returncode:break
  result={'variant':name,'commands':commands}
  if x.returncode==0:
   d=json.loads((r/f'experiment-{A}-{name}.json').read_text())
   result['measurement']=[{'side':side,**{k:v for k,v in next(s for s in d[side]['symbols'] if s['name']=='fn_8019C4E4').items() if k in ['size','match_percent']}} for side in ['left','right']]
  log.append(result)
  print(json.dumps(result),flush=True)
finally:
 p.write_text(base)
 (r/f'experiment-{A}-log.json').write_text(json.dumps(log,indent=2)+'\n')
