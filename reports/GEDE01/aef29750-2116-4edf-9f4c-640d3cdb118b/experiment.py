import subprocess, json, difflib, hashlib
from pathlib import Path
root=Path(__file__).resolve().parents[3]
p=root/'src/game/game_fn_801D1F78.c'
out=Path(__file__).resolve().parent
base=p.read_text()
variants={
'indexed-projected': base.replace('    s32* projected_ptr;\n','').replace('    projected_ptr = projected;\n','').replace('*projected_ptr++ = screen.x;', 'projected[i] = screen.x;'),
'pointer-loop-increment': base.replace('for (i = 0; i < count; i++) {','for (i = 0; i < count; i++, projected_ptr++) {',1).replace('*projected_ptr++ = screen.x;', '*projected_ptr = screen.x;'),
'float-count-hoist': base.replace('    f32 angle;', '    f32 angle;\n    f32 float_count;').replace('    object = object_arg;', '    object = object_arg;\n    float_count = (f32)count;').replace('/ (f32)count;', '/ float_count;'),
}
results=[]
def run(args):
 r=subprocess.run(args,cwd=root,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
 return {'command':args,'exit_code':r.returncode,'output':r.stdout}
try:
 for name,source in [('baseline',base)]+list(variants.items()):
  p.write_text(source)
  record={'name':name,'patch': ''.join(difflib.unified_diff(base.splitlines(True),source.splitlines(True),fromfile='baseline',tofile=name))}
  record['build']=run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_801D1F78.externalized'])
  if record['build']['exit_code']==0:
   raw=out/(name+'.json')
   record['objdiff']=run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_801D1F78','-o',str(raw.relative_to(root)),'--format','json','fn_801D1F78'])
   if record['objdiff']['exit_code']==0:
    d=json.loads(raw.read_text())
    sym=next(s for s in d['left']['symbols'] if s['name']=='fn_801D1F78')
    record['match_percent']=sym.get('match_percent')
    record['object_sha256']=hashlib.sha256((root/'build/GEDE01/src/game/game_fn_801D1F78.o').read_bytes()).hexdigest()
  results.append(record)
  (out/'experiments.json').write_text(json.dumps(results,indent=2)+'\n')
  print(name,record.get('match_percent'),record['build']['exit_code'],flush=True)
finally:
 p.write_text(base)
