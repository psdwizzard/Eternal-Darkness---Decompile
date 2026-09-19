from pathlib import Path
import subprocess,json,difflib
ROOT=Path(__file__).resolve().parents[3]
R=Path(__file__).resolve().parent
P=ROOT/'src/game/game_fn_8014B0F0.c'
BASE=(R/'baseline.c.txt').read_text()
records=[]
def run(cmd):
    x=subprocess.run(cmd,cwd=ROOT,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    records.append({'command':cmd,'cwd':'eternal-darkness-decomp','exit_code':x.returncode,'output':x.stdout})
    if x.returncode: raise RuntimeError(x.stdout)
    return x.stdout

def measure(name,s):
    P.write_text(s)
    (R/(name+'.patch')).write_text(''.join(difflib.unified_diff(BASE.splitlines(True),s.splitlines(True),fromfile='a/eternal-darkness-decomp/src/game/game_fn_8014B0F0.c',tofile='b/eternal-darkness-decomp/src/game/game_fn_8014B0F0.c')))
    run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_8014B0F0.o'])
    out=R/(name+'.json')
    run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_8014B0F0','fn_8014B0F0','-o',str(out.relative_to(ROOT)),'--format','json-pretty'])
    d=json.loads(out.read_text())
    l=next(x for x in d['left']['symbols'] if x['name']=='fn_8014B0F0')
    r=next(x for x in d['right']['symbols'] if x['name']=='fn_8014B0F0')
    print(name,l['size'],r['size'],l['match_percent'],flush=True)
    (R/'experiment-commands.json').write_text(json.dumps(records,indent=2)+'\n')
    return l['match_percent']

wide=BASE.replace('    u16 bit;', '    u32 bit;').replace('for (i = 0; i < count; i++) {','for (i = 0; i < count; i++) {\n            bit = (u16)bit;').replace('bit <<= 1;', 'bit = (u16)(bit << 1);')
measure('wide-normalized',wide)
local=BASE.replace('    u16 bit;', '    u32 bit;').replace('for (i = 0; i < count; i++) {','for (i = 0; i < count; i++) {\n            u16 mask = (u16)bit;').replace('set->active & bit','set->active & mask').replace('~bit','~mask').replace('bit <<= 1;', 'bit = (u16)(mask << 1);')
measure('local-normalized',local)
measure('local-wide-normalized',local.replace('u16 mask =','u32 mask ='))
measure('short-normalized',wide.replace('u32 bit;', 'u16 bit;'))
parts=wide.split('    if (update == 0) {')
a=parts[0].replace('    u32 bit;', '    u32 bit1, bit2, bit3;')
import re
a=re.sub(r'\bbit\b','bit1',a)
b,c=parts[1].split('    {\n        void* context')
separate=a+'    if (update == 0) {'+re.sub(r'\bbit\b','bit2',b)+'    {\n        void* context'+re.sub(r'\bbit\b','bit3',c)
measure('separate-wide-normalized',separate)
short=wide.replace('u32 bit;', 'u16 bit;')
import itertools
old='    u16 bit;\n    int mode;\n    int i;\n    Set* entry;'
best=(0,None)
for order in itertools.permutations(['    u16 bit;', '    int mode;', '    int i;', '    Set* entry;']):
    name='short-order-'+''.join({'    u16 bit;':'b','    int mode;':'m','    int i;':'i','    Set* entry;':'e'}[v] for v in order)
    source=short.replace(old,'\n'.join(order))
    score=measure(name,source)
    if score>best[0]: best=(score,source)
    if score==100: break
P.write_text(best[1])
(R/'best-score.txt').write_text(str(best[0])+'\n')
