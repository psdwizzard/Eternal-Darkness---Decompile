import pathlib,subprocess,json,hashlib
root=pathlib.Path(__file__).resolve().parents[3]
r=pathlib.Path(__file__).resolve().parent
src=root/'src/game/game_fn_80088A04.c'
entry_source=src.read_text()
original=subprocess.check_output(['git','show','2f48f2ee01abe95fadde42861598a098e747c86d:eternal-darkness-decomp/src/game/game_fn_80088A04.c'],cwd=root,text=True)
copy='''owner->position.x = output.x;
        owner->position.y = output.y;
        owner->position.z = output.z;'''
original=original.replace('random = fn_800FBFB0();','random = fn_800FBFB0() % 352;').replace('settings->phase = random % 352;','settings->phase = random;')
variants={
 'settings-after-call':original.replace('Settings* settings = &lbl_8031D3B8;', 'Settings* settings;').replace('owner = owner->owner;', 'settings = &lbl_8031D3B8;\n    owner = owner->owner;'),
 'settings-after-dereference':original.replace('Settings* settings = &lbl_8031D3B8;', 'Settings* settings;').replace('owner = owner->owner;', 'owner = owner->owner;\n    settings = &lbl_8031D3B8;'),
 'separate-input-owner':original.replace('Work* owner = work;', 'Work* owner;').replace('fn_8006ED3C(owner, 7, &index);','fn_8006ED3C(work, 7, &index);').replace('owner = owner->owner;', 'owner = work->owner;'),
 'early-return':original.replace('if (owner->active == 0 && lbl_8063D378 != 0) {','if (owner->active != 0) return 0;\n    if (lbl_8063D378 == 0) return 0;\n    {'),
 'split-conditions':original.replace('if (owner->active == 0 && lbl_8063D378 != 0) {','if (owner->active == 0) if (lbl_8063D378 != 0) {'),
 'owner-void-base':original.replace('Work* owner = work;', 'void* base = work;\n    Work* owner;').replace('fn_8006ED3C(owner, 7, &index);','fn_8006ED3C(base, 7, &index);').replace('owner = owner->owner;', 'owner = *(Work**)((u8*)base + 0xC4);'),
}

results=[]
try:
 for name,s in variants.items():
  src.write_text(s)
  cmd=['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80088A04.o']
  p=subprocess.run(cmd,cwd=root,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
  (r/(name+'.log')).write_text(p.stdout)
  if p.returncode: raise RuntimeError(p.stdout)
  cmd=['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80088A04','-o',str(r/(name+'.json')),'--format','json-pretty','-c','function_reloc_diffs=name_address','fn_80088A04']
  p=subprocess.run(cmd,cwd=root,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
  if p.returncode: raise RuntimeError(p.stdout)
  d=json.loads((r/(name+'.json')).read_text())
  syms=[next(x for x in d[side]['symbols'] if x['name']=='fn_80088A04') for side in ['left','right']]
  row={'name':name,'source_sha256':hashlib.sha256(s.encode()).hexdigest(),'score':syms[0]['match_percent'],'sizes':[x['size'] for x in syms]}
  results.append(row);print(row,flush=True)
finally:
 src.write_text(entry_source)
 (r/'experiments3.json').write_text(json.dumps(results,indent=2)+'\n')
