import pathlib,subprocess,json,hashlib
root=pathlib.Path(__file__).resolve().parents[3]
r=pathlib.Path(__file__).resolve().parent
src=root/'src/game/game_fn_80088A04.c'
entry_source=src.read_text()
original=subprocess.check_output(['git','show','2f48f2ee01abe95fadde42861598a098e747c86d:eternal-darkness-decomp/src/game/game_fn_80088A04.c'],cwd=root,text=True)
copy='''owner->position.x = output.x;
        owner->position.y = output.y;
        owner->position.z = output.z;'''
variants={
 'baseline':original,
 'aggregate-position':original.replace(copy,'owner->position = output;'),
 'array-position-loop':original.replace('float x;\n    float y;\n    float z;','float v[3];').replace(copy,'{ int i; for (i = 0; i < 3; ++i) owner->position.v[i] = output.v[i]; }'),
 'array-position-unrolled':original.replace('float x;\n    float y;\n    float z;','float v[3];').replace(copy,'owner->position.v[0] = output.v[0];\n        owner->position.v[1] = output.v[1];\n        owner->position.v[2] = output.v[2];'),
 'position-local':original.replace(copy,'{ Vec3* position = &owner->position;\n        position->x = output.x;\n        position->y = output.y;\n        position->z = output.z; }'),
 'position-float-temporaries':original.replace(copy,'{ float x = output.x; float y = output.y; float z = output.z;\n        owner->position.x = x; owner->position.y = y; owner->position.z = z; }'),
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
 (r/'experiments.json').write_text(json.dumps(results,indent=2)+'\n')
