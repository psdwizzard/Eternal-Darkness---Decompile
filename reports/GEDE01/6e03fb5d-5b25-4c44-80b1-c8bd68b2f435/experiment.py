import json, subprocess, pathlib, sys
ROOT=pathlib.Path(__file__).resolve().parents[3]
SRC=ROOT/'src/game/game_fn_80131460.c'
OUT=pathlib.Path(__file__).resolve().parent
BASE=subprocess.check_output(['git','show','4a4893bf:eternal-darkness-decomp/src/game/game_fn_80131460.c'],cwd=ROOT,text=True)
def run(name,s):
 SRC.write_text(s)
 p=subprocess.run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80131460.o'],cwd=ROOT,capture_output=True,text=True)
 (OUT/(name+'.log')).write_text(p.stdout+p.stderr)
 if p.returncode: print(name,'FAIL',flush=True); return -1
 subprocess.run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80131460','fn_80131460','-o',str(OUT/(name+'.json')),'--format','json'],cwd=ROOT,check=True,capture_output=True)
 d=json.loads((OUT/(name+'.json')).read_text()); f=next(x for x in d['left']['symbols'] if x['name']=='fn_80131460')
 score=f['match_percent']; print(name,score,flush=True); return score
if __name__=='__main__':
 variants={'baseline':BASE}
 for name,expr in [('commuted','kind + lbl_80241DE8'),('byte_offset','(Descriptor*)((char*)lbl_80241DE8 + kind * 0x28)'),('byte_commuted','(Descriptor*)(kind * 0x28 + (char*)lbl_80241DE8)'),('explicit_base','descriptor + kind')]:
  s=BASE.replace('descriptor = &lbl_80241DE8[kind];','descriptor = '+expr+';')
  s=s.replace('descriptor = &lbl_80241DE8[*(u8*)(lbl_8030F540 + 0x1DA)];','kind = *(u8*)(lbl_8030F540 + 0x1DA);\n        descriptor = '+expr+';')
  if name=='explicit_base': s=s.replace('descriptor = descriptor + kind;','descriptor = lbl_80241DE8;\n        descriptor += kind;')
  variants[name]=s
 old='''                    *(s16*)(lbl_8030F540 + 0x1D6) = transition - adjustment;
                    *(int*)(lbl_8030F540 + 0x1CC) = counter + adjustment;'''
 for name,new in [('inplace_temps','''                    transition -= adjustment;
                    counter += adjustment;
                    *(s16*)(lbl_8030F540 + 0x1D6) = transition;
                    *(int*)(lbl_8030F540 + 0x1CC) = counter;'''),('reuse_adjustment','''                    transition -= adjustment;
                    adjustment += counter;
                    *(s16*)(lbl_8030F540 + 0x1D6) = transition;
                    *(int*)(lbl_8030F540 + 0x1CC) = adjustment;'''),('commute_counter','''                    *(s16*)(lbl_8030F540 + 0x1D6) = transition - adjustment;
                    *(int*)(lbl_8030F540 + 0x1CC) = adjustment + counter;''')]:
  variants[name]=BASE.replace(old,new)
 scores={}
 for name,s in variants.items(): scores[name]=run(name,s)
 best=max(scores,key=scores.get); SRC.write_text(variants[best]); (OUT/'experiments.json').write_text(json.dumps(scores,indent=2)+'\n'); print('BEST',best)
