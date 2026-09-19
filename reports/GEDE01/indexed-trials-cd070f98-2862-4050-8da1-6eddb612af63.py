"""Assignment-local, reproducible register-priority experiments; run from project root."""
import difflib, json, subprocess
from pathlib import Path
A='cd070f98-2862-4050-8da1-6eddb612af63'
R=Path('reports/GEDE01')
S=Path('src/game/game_fn_801CE384.c')
base=(R/f'baseline-{A}.txt').read_text()
log=[]
def run(cmd):
 p=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
 log.append({'command':cmd,'returncode':p.returncode,'output':p.stdout})
 if p.returncode: raise RuntimeError(p.stdout)
 return p.stdout
variants={}
# Let MWCC create strength-reduced induction pointers from array indexing.
indexed=base.replace('    s16* index;\n','').replace('    void** output;\n','').replace('    output = objects;\n','').replace('    index = indices;\n','').replace('*index','indices[i]').replace('*output','objects[i]').replace('        index++;\n','').replace('        output++;\n','')
variants['indexed-both']=indexed
variants['indexed-input']=base.replace('    s16* index;\n','').replace('    index = indices;\n','').replace('*index','indices[i]').replace('        index++;\n','')
variants['indexed-output']=base.replace('    void** output;\n','').replace('    output = objects;\n','').replace('*output','objects[i]').replace('        output++;\n','')
try:
 for label,source in variants.items():
  S.write_text(source)
  (R/f'{label}-{A}.diff').write_text(''.join(difflib.unified_diff(base.splitlines(True),source.splitlines(True),fromfile='a/src/game/game_fn_801CE384.c',tofile='b/src/game/game_fn_801CE384.c',n=0)))
  run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_801CE384.o'])
  output=R/f'{label}-{A}.json'
  run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_801CE384','fn_801CE384','-c','functionRelocDiffs=all','-o',str(output),'--format','json'])
  d=json.loads(output.read_text()); l=d['left']['symbols'][0]; r=d['right']['symbols'][0]
  print(label,l.get('match_percent'),l['size'],r['size'],flush=True)
finally:
 S.write_text(base)
 (R/f'indexed-commands-{A}.json').write_text(json.dumps(log,indent=2)+'\n')
