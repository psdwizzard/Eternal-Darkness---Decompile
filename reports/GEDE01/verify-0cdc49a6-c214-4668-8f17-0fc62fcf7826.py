#!/usr/bin/env python3
"""Capture final verification after the canonical configure/build, from project root."""
import hashlib, json, pathlib, struct, subprocess
ID='0cdc49a6-c214-4668-8f17-0fc62fcf7826'
P=pathlib.Path('reports/GEDE01/verification-'+ID+'.json')
r=json.loads(P.read_text())
def run(argv):
 p=subprocess.run(argv,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
 row={'argv':argv,'exit_code':p.returncode,'output':p.stdout}
 r['runs'].append(row);P.write_text(json.dumps(r,indent=2)+'\n')
 if p.returncode: raise RuntimeError(row)
 return p.stdout
for suffix,config in [('',[]),('-reloc-strict',['-c','function_reloc_diffs=name_address'])]:
 output='reports/GEDE01/objdiff-'+ID+suffix+'.json'
 run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80189C14','fn_80189C14','-o',output,'--format','json-pretty']+config)
 d=json.loads(pathlib.Path(output).read_text())
 a=next(s for s in d['left']['symbols'] if s['name']=='fn_80189C14')
 b=next(s for s in d['right']['symbols'] if s['name']=='fn_80189C14')
 r['canonical' if not suffix else 'relocation_strict']={'match_percent':a['match_percent'],'retail_size':a['size'],'generated_size':b['size'],'retail_instructions':sum('instruction' in i for i in a['instructions']),'generated_instructions':sum('instruction' in i for i in b['instructions'])}
run(['sha1sum','orig/GEDE01/sys/main.dol','build/GEDE01/main.dol'])
run(['sha256sum','compilers/GC/1.3/mwcceppc.exe','build/tools/objdiff-cli','src/game/game_fn_80189C14.c','build/GEDE01/src/game/game_fn_80189C14.o','build/GEDE01/obj/game/game_fn_80189C14.o'])
run(['.tools/bin/ninja','-t','commands','build/GEDE01/src/game/game_fn_80189C14.o'])
run(['.tools/bin/ninja','-t','commands','build/GEDE01/src/game/game_fn_80189C14.externalized'])
for obj in ['build/GEDE01/obj/game/game_fn_80189C14.o','build/GEDE01/src/game/game_fn_80189C14.o']:
 run(['build/binutils/powerpc-eabi-readelf','-Wr',obj])
run(['python3','tools/legal_audit.py'])
run(['git','diff','--check'])
def elf(path):
 data=pathlib.Path(path).read_bytes()
 assert data[:6]==b'\x7fELF\x01\x02'
 off=struct.unpack_from('>I',data,32)[0];es,num,strings=struct.unpack_from('>HHH',data,46)
 sh=[struct.unpack_from('>10I',data,off+i*es) for i in range(num)]
 def contents(h):return data[h[4]:h[4]+h[5]]
 names=contents(sh[strings])
 def name(table,offset):return table[offset:].split(b'\0',1)[0].decode()
 ti=next(i for i,h in enumerate(sh) if name(names,h[0])=='.text')
 text=contents(sh[ti]);rels=[]
 for h in sh:
  if h[1]!=4 or h[7]!=ti:continue
  symbols=sh[h[6]];strings=contents(sh[symbols[6]])
  for at in range(h[4],h[4]+h[5],h[9]):
   offset,info,addend=struct.unpack_from('>IIi',data,at)
   sym_at=symbols[4]+(info>>8)*symbols[9]
   sym=struct.unpack_from('>IIIBBH',data,sym_at)
   rels.append({'offset':offset,'type':info&255,'target':name(strings,sym[0]),'addend':addend})
 return text,rels
left,lr=elf('build/GEDE01/obj/game/game_fn_80189C14.o');right,rr=elf('build/GEDE01/src/game/game_fn_80189C14.o')
r['independent_elf_comparison']={'retail_text_sha256':hashlib.sha256(left).hexdigest(),'generated_text_sha256':hashlib.sha256(right).hexdigest(),'retail_relocations':lr,'generated_relocations':rr,'relocations_equal_including_offsets_types_targets_addends':lr==rr,'instruction_word_differences':[{'offset':hex(i),'retail':left[i:i+4].hex(),'generated':right[i:i+4].hex()} for i in range(0,max(len(left),len(right)),4) if left[i:i+4]!=right[i:i+4]]}
r['dol_scope']='Target remains NonMatching: DOL verification covers the canonical linked build, which uses the retail target object; it does not establish a linked C match.'
P.write_text(json.dumps(r,indent=2)+'\n')
print(json.dumps({k:r[k] for k in ['canonical','relocation_strict','independent_elf_comparison']},indent=2))
