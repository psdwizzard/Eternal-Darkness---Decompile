import json, subprocess
from pathlib import Path
P=Path('reports/GEDE01/174d74e1-3fdf-41fd-99ed-047612b2963f')
S=Path('src/game/game_fn_8017CCD8.c')
base=S.read_text()
old='lbl_8060630C.entries += saved_count & 0xFFFF;'
variants={'baseline':base}
expressions={
 'byte-stride':'(Entry*)((u8*)lbl_8060630C.entries + 12 * (saved_count & 0xFFFF))',
 'byte-stride-signed':'(Entry*)((u8*)lbl_8060630C.entries + 12 * (int)(saved_count & 0xFFFF))',
 'byte-stride-shift':'(Entry*)((u8*)lbl_8060630C.entries + ((saved_count & 0xFFFF) << 3) + ((saved_count & 0xFFFF) << 2))',
 'integer-address':'(Entry*)((u32)lbl_8060630C.entries + 12 * (saved_count & 0xFFFF))',
 'reverse-byte-add':'(Entry*)(12 * (saved_count & 0xFFFF) + (u8*)lbl_8060630C.entries)',
}
for name,expr in expressions.items():variants[name]=base.replace(old,'lbl_8060630C.entries = '+expr+';')
variants['commute-entry-count']=base.replace('lbl_8060630C.entry_count += saved_count;','lbl_8060630C.entry_count = saved_count + lbl_8060630C.entry_count;')
variants['signed-entry-count-add']=base.replace('lbl_8060630C.entry_count += saved_count;','lbl_8060630C.entry_count += (int)saved_count;')
variants['pointer-manager-increment']=base.replace('(Manager*)((u8*)lbl_8060630C.managers + sizeof(Manager))','lbl_8060630C.managers + 1')
results=[]
try:
 for name,source in variants.items():
  S.write_text(source)
  commands=[['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_8017CCD8.o'],['build/tools/objdiff-cli','diff','-1','build/GEDE01/obj/game/game_fn_8017CCD8.o','-2','build/GEDE01/src/game/game_fn_8017CCD8.o','fn_8017CCD8','--format','json','-o',str(P/(name+'.json'))]]
  rec={'name':name,'source':source,'runs':[]}
  for cmd in commands:
   r=subprocess.run(cmd,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
   rec['runs'].append({'command':cmd,'returncode':r.returncode,'output':r.stdout})
   if r.returncode:break
  if not r.returncode:
   d=json.loads((P/(name+'.json')).read_text()); sym=next(s for s in d['left']['symbols'] if s['name']=='fn_8017CCD8')
   rec['score']=sym['match_percent']; rec['raw_objdiff']=str(P/(name+'.json'))
   print(name,rec['score'],flush=True)
  results.append(rec)
finally:
 S.write_text(base)
 (P/'experiments.json').write_text(json.dumps(results,indent=2)+'\n')
 subprocess.run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_8017CCD8.o'],check=True)
