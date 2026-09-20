import json, subprocess
from pathlib import Path
ID='73f318cb-9aa8-4de1-b57a-6b164c968a04'
root=Path(__file__).resolve().parents[2]
source=root/'src/game/game_fn_80194AC4.c'
base=subprocess.check_output(['git','show','47335122300de3ce6ae80b8ffa7d0690dd03617a:eternal-darkness-decomp/src/game/game_fn_80194AC4.c'],cwd=root,text=True)
original=source.read_text()
variants={}
variants['early-half']=base.replace('        half = (u8)width >> 1;\n','').replace('        fn_80186F70(outputs[0]', '        half = (u8)width >> 1;\n        fn_80186F70(outputs[0]',1)
shared=variants['early-half'].replace('    u8 type;','    u8 type;\n    int half;\n    int rest;\n    float step;\n    int endpoint;').replace('        int half;\n        int rest;\n        float step;\n        int endpoint;\n','').replace('        int half = width >> 1;\n        int rest;\n        float step;\n        int endpoint;','        half = width >> 1;')
variants['shared-temporaries']=shared
for name,code in [('inline-endpoints',base),('early-half-inline-endpoints',variants['early-half'])]:
 code=code.replace('        int endpoint;\n','')
 for axis in range(3):
  expr=f'(int)((float)half * step + (float)base[{axis}])'
  code=code.replace(f'        endpoint = {expr};\n','')
  code=code.replace(f'scale[{axis}] / (float)rest,\n                    endpoint, type);',f'scale[{axis}] / (float)rest,\n                    {expr}, type);')
 variants[name]=code
seed=variants['early-half-inline-endpoints']
for name,anchor in [('type-before-width','    width ='),('type-before-flags','    flags ='),('type-before-outputs','    outputs[0] =')]:
 code=seed.replace('    type = state[3];\n','')
 idx=code.index(anchor)
 variants[name]=code[:idx]+'    type = state[3];\n'+code[idx:]
variants['early-half-inline-promoted-type']=seed.replace('    u8 type;', '    int type;')
seed2=variants['early-half-inline-promoted-type']
variants['promoted-width']=seed2.replace('    u8 width;', '    int width;').replace('width = state[0xB] - 4;', 'width = (u8)(state[0xB] - 4);')
variants['byte-half']=seed2.replace('        int half;', '        u8 half;').replace('        int half = width >> 1;', '        u8 half = width >> 1;')
variants['shared-half']=seed2.replace('    int type;', '    int type;\n    int half;').replace('        int half;\n','').replace('        int half = width >> 1;', '        half = width >> 1;')
variants['shared-half']=variants['shared-half'].replace('        half = width >> 1;\n        int rest;\n        float step;', '        int rest;\n        float step;\n        half = width >> 1;')
seed3=variants['shared-half']
variants['shared-rest']=seed3.replace('    int half;', '    int half;\n    int rest;').replace('        int rest;\n','')
variants['shared-index']=seed3.replace('    int half;', '    int half;\n    int i;').replace('        int i;\n','')
variants['int-width-cast-shifts']=seed3.replace('    u8 width;', '    int width;').replace('width = state[0xB] - 4;', 'width = (u8)(state[0xB] - 4);').replace('half = width >> 1;', 'half = (u8)width >> 1;')
code=seed2
start=code.index('    if (flags & 0x100) {')
end=code.index('    } else if (flags & 0x400) {')
part=code[start:end].replace('int half;', 'int full;').replace('half = (u8)width >> 1;', 'full = width;\n        width >>= 1;').replace('outputs[0], width,','outputs[0], full,').replace('outputs[1], width,','outputs[1], full,').replace('rest = width - half;', 'rest = full - width;').replace('half','width')
variants['reuse-width']=code[:start]+part+code[end:]
records=[]
try:
 for name,code in variants.items():
  source.write_text(code)
  rec={'name':name,'source':code,'commands':[]}
  out=f'reports/GEDE01/experiment-{name}-{ID}.json'
  for cmd in [['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80194AC4.o'],['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80194AC4','fn_80194AC4','-o',out,'--format','json-pretty','-c','function_reloc_diffs=name_address']]:
   p=subprocess.run(cmd,cwd=root,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
   rec['commands'].append({'argv':cmd,'exit_code':p.returncode,'raw_output':p.stdout})
   if p.returncode:
    records.append(rec)
    raise RuntimeError(p.stdout)
  diff=json.loads((root/out).read_text())
  a=next(s for s in diff['left']['symbols'] if s['name']=='fn_80194AC4');b=next(s for s in diff['right']['symbols'] if s['name']=='fn_80194AC4')
  rec['measurement']={'score':a['match_percent'],'retail_size':a['size'],'candidate_size':b['size']}
  records.append(rec)
  print(name,rec['measurement'],flush=True)
finally:
 source.write_text(original)
 (root/f'reports/GEDE01/experiments-{ID}.json').write_text(json.dumps(records,indent=2)+'\n')
