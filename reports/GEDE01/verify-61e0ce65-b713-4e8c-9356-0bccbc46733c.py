"""Run from eternal-darkness-decomp; record canonical checks and relocation identity."""
import json, pathlib, subprocess, sys, struct
A='61e0ce65-b713-4e8c-9356-0bccbc46733c'
r=pathlib.Path('reports/GEDE01')
reuse = '--reuse-checks' in sys.argv
log=json.loads((r/f'verification-{A}.json').read_text())['commands'] if reuse else []
commands=[['python3','configure.py'],['.tools/bin/ninja','-j2'],['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_8019C4E4','-o',str(r/f'canonical-{A}.json'),'--format','json'],['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_8019C4E4','-o',str(r/f'objdiff-{A}.json'),'--format','json','-c','function_reloc_diffs=name_address'],['sha1sum','build/GEDE01/main.dol'],['python3','tools/legal_audit.py'],['.tools/bin/ninja','-t','commands','build/GEDE01/src/game/game_fn_8019C4E4.o']]
for index,cmd in enumerate(commands):
 if reuse and index not in (2,3): continue
 x=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
 record={'argv':cmd,'exit_code':x.returncode,'raw_output':x.stdout}
 if reuse: log[index]=record
 else: log.append(record)
 print(json.dumps(record),flush=True)
 (r/f'verification-{A}.json').write_text(json.dumps({'commands':log},indent=2)+'\n')
 if x.returncode: raise SystemExit(x.returncode)
d=json.loads((r/f'objdiff-{A}.json').read_text())
measurements={}
relocs={}
for side in ['left','right']:
 s=next(s for s in d[side]['symbols'] if s['name']=='fn_8019C4E4')
 measurements[side]={k:s[k] for k in ['size','match_percent']}
 measurements[side]['instruction_count']=len(s['instructions'])
 measurements[side]['differing_rows']=sum(i.get('diff_kind','DIFF_NONE')!='DIFF_NONE' for i in s['instructions'])
 relocs[side]=[]
 for row in s['instructions']:
  i=row.get('instruction',{})
  if 'relocation' not in i:continue
  rel=i['relocation']
  relocs[side].append({'address':int(i.get('address',0)),'formatted':i['formatted'],'type':rel.get('type',0),'addend':str(rel.get('addend',0))})
def elf_relocs(path):
 b=pathlib.Path(path).read_bytes()
 assert b[:6] == b'\x7fELF\x01\x02'
 shoff=struct.unpack_from('>I',b,32)[0]
 entsize,num,shstr=struct.unpack_from('>HHH',b,46)
 sections=[struct.unpack_from('>10I',b,shoff+j*entsize) for j in range(num)]
 def section(j):
  sh=sections[j]; return b[sh[4]:sh[4]+sh[5]]
 def string(data,pos):return data[pos:data.index(b'\0',pos)].decode()
 names=section(shstr)
 result=[]
 for sh in sections:
  if sh[1]!=4:continue
  syms=section(sh[6]); strings=section(sections[sh[6]][6])
  for pos in range(sh[4],sh[4]+sh[5],sh[9]):
   offset,info,addend=struct.unpack_from('>IIi',b,pos)
   nameoff=struct.unpack_from('>I',syms,(info>>8)*16)[0]
   result.append({'section':string(names,sections[sh[7]][0]),'offset':offset,'type':info&255,'target':string(strings,nameoff),'addend':addend})
 return result
elf={'left':elf_relocs('build/GEDE01/obj/game/game_fn_8019C4E4.o'),'right':elf_relocs('build/GEDE01/src/game/game_fn_8019C4E4.o')}
summary={'elf_relocations':elf,'elf_relocations_equal':elf['left']==elf['right'],'measurements':measurements,'relocations':relocs,'relocations_equal':relocs['left']==relocs['right']}
print(json.dumps(summary),flush=True)
(r/f'verification-{A}.json').write_text(json.dumps({'commands':log,**summary},indent=2)+'\n')
