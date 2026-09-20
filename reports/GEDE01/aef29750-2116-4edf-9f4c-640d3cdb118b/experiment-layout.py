import subprocess, json, difflib, hashlib, struct
from pathlib import Path
root=Path(__file__).resolve().parents[3]
p=root/'src/game/game_fn_801D1F78.c'
out=Path(__file__).resolve().parent
base=p.read_text()
config=root/'configure.py'
config_base=config.read_text()
variants={}
v=base.replace('    s32 projected[9];\n    s32 order[9];','    struct { s32 order[9]; s32 projected[9]; } workspace;')
import re
start=v.index('    QueryResult query_a;')
v=v[:start]+re.sub(r'\b(projected|order)\b',r'workspace.\1',v[start:])
variants['grouped-arrays']=v
variants['count-u16']=base.replace('    u8 count;\n    volatile RingDefinition* ring;', '    unsigned short count;\n    volatile RingDefinition* ring;')
variants['field-volatiles']=base.replace('    u8 count;\n    u8 pad;\n    s16 radius;\n    Vec3 center;', '    volatile u8 count;\n    u8 pad;\n    volatile s16 radius;\n    volatile Vec3 center;').replace('volatile RingDefinition*','RingDefinition*')
def constant_symbols():
 data=(root/'build/GEDE01/src/game/game_fn_801D1F78.o').read_bytes()
 off=struct.unpack_from('>I',data,32)[0]
 size,count,strings=struct.unpack_from('>HHH',data,46)
 sections=[struct.unpack_from('>10I',data,off+i*size) for i in range(count)]
 found={}
 for sec in sections:
  if sec[1]!=2: continue
  st=sections[sec[6]]; names=data[st[4]:st[4]+st[5]]
  for pos in range(sec[4],sec[4]+sec[5],16):
   name,value,length,info,other,idx=struct.unpack_from('>IIIBBH',data,pos)
   name=names[name:].split(b'\0')[0].decode()
   if name.startswith('@') and idx<len(sections):
    target=sections[idx]; raw=data[target[4]+value:target[4]+value+length]
    if raw.hex()=='4330000080000000': found['signed']=name
    if raw.hex()=='4330000000000000': found['unsigned']=name
 return found
results=[]
def run(args):
 r=subprocess.run(args,cwd=root,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
 return {'command':args,'exit_code':r.returncode,'output':r.stdout}
try:
 for name,source in list(variants.items()):
  p.write_text(source)
  record={'name':name,'patch': ''.join(difflib.unified_diff(base.splitlines(True),source.splitlines(True),fromfile='baseline',tofile=name))}
  record['compile']=run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_801D1F78.o'])
  constants=constant_symbols()
  record['constant_symbols']=constants
  config.write_text(config_base.replace('[("@67", "lbl_80651070"), ("@69", "lbl_80651080")]', '[("'+constants['signed']+'", "lbl_80651070"), ("'+constants['unsigned']+'", "lbl_80651080")]'))
  record['configure']=run(['python3','configure.py'])
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
  (out/'experiments-layout.json').write_text(json.dumps(results,indent=2)+'\n')
  print(name,record.get('match_percent'),record['build']['exit_code'],flush=True)
finally:
 p.write_text(base)
 config.write_text(config_base)
 run(['python3','configure.py'])
