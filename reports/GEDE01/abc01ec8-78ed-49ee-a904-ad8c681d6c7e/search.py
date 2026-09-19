from pathlib import Path
import subprocess,json,difflib,itertools
ROOT=Path(__file__).resolve().parents[3]; R=Path(__file__).resolve().parent; P=ROOT/'src/game/game_fn_8014B0F0.c'
start=(R/'search-start.c.txt').read_text(); (R/'search-start.c.txt').write_text(start)
base=(R/'baseline.c.txt').read_text()
a,tail=start.split('    int count;\n',1); old,body=tail.split('\n    if (left == 0)',1)
decls=['int count;']+[x.strip() for x in old.strip().splitlines()]
decls.remove('float *x, *y, *z;'); decls[-1:-1]=['float* x;','float* y;','float* z;']
# Explicit declaration list is the only search parameter; executable statements are fixed.
logs=[];seen=set();bestscore=99.45578;bestsource=start;bestorder=decls[:];bestname='initial'
cmds=[['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_8014B0F0.o'],['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_8014B0F0','fn_8014B0F0','-o',str((R/'search-current.json').relative_to(ROOT)),'--format','json']]
for iteration in range(4):
 oldbest=bestscore; current=bestorder[:]
 candidates=[]
 for i in range(len(current)):
  for j in range(len(current)):
   c=current[:];v=c.pop(i);c.insert(j,v);candidates.append(c)
 for order in candidates:
  key=tuple(order)
  if key in seen:continue
  seen.add(key)
  s=a+''.join('    '+d+'\n' for d in order)+'\n    if (left == 0)'+body
  P.write_text(s)
  raw=[]
  for cmd in cmds:
   p=subprocess.run(cmd,cwd=ROOT,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
   raw.append({'command':cmd,'exit_code':p.returncode,'output':p.stdout})
   if p.returncode:raise RuntimeError(p.stdout)
  d=json.loads((R/'search-current.json').read_text()); l=next(x for x in d['left']['symbols'] if x['name']=='fn_8014B0F0');r=next(x for x in d['right']['symbols'] if x['name']=='fn_8014B0F0')
  n=len(logs); score=l['match_percent']; logs.append({'order':order,'commands':raw,'raw_symbol_metadata':{'left':{k:v for k,v in l.items() if k!='instructions'},'right':{k:v for k,v in r.items() if k!='instructions'}}})
  if score>bestscore:
   bestscore=score;bestsource=s;bestorder=order;bestname='search-'+str(n)
   (R/(bestname+'.json')).write_text(json.dumps(d,indent=2)+'\n')
   (R/(bestname+'.patch')).write_text(''.join(difflib.unified_diff(base.splitlines(True),s.splitlines(True),fromfile='a/eternal-darkness-decomp/src/game/game_fn_8014B0F0.c',tofile='b/eternal-darkness-decomp/src/game/game_fn_8014B0F0.c')))
   print('improvement',n,bestscore,bestorder,flush=True)
  if score==100:break
 P.write_text(bestsource)
 (R/'search-log.json').write_text(json.dumps(logs,indent=2)+'\n')
 print('iteration',iteration,'tested',len(logs),'best',bestscore,flush=True)
 if bestscore==100 or bestscore==oldbest:break
(R/'search-best.txt').write_text(str((bestscore,bestname,bestorder))+'\n')
