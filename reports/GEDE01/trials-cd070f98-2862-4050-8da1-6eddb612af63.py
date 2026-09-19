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
locals=base
for decl in ['u32 object_type;', 's16 count;', 's16* index;', 'void** output;', 'int i;']:
 locals=locals.replace('    '+decl,'    register '+decl)
variants['register-locals']=locals
variants['register-all']=locals.replace('fn_801CE384(u32 type, const Vec3f* position, u16 value, u32 value24,','fn_801CE384(register u32 type, register const Vec3f* position, register u16 value, register u32 value24,').replace('u8 value1C, void** objects)','register u8 value1C, register void** objects)')
variants['register-index']=base.replace('    s16* index;', '    register s16* index;')
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
 (R/f'trial-commands-{A}.json').write_text(json.dumps(log,indent=2)+'\n')
