"""Independent function byte and ELF relocation comparison for this assignment."""
from pathlib import Path
import hashlib, json, struct, subprocess
ID='ff31a8f4-27bc-4b2d-a516-c5b4bd2c49ad'
TARGET='fn_8000F774'
def elf(path):
 data=Path(path).read_bytes()
 assert data[:6]==b'\x7fELF\x01\x02'
 shoff=struct.unpack_from('>I',data,32)[0]
 shentsize,shnum,shstrndx=struct.unpack_from('>HHH',data,46)
 sh=[struct.unpack_from('>10I',data,shoff+i*shentsize) for i in range(shnum)]
 def sect(i):return data[sh[i][4]:sh[i][4]+sh[i][5]]
 def string(tab,off):return tab[off:tab.index(0,off)].decode()
 names=[string(sect(shstrndx),s[0]) for s in sh]
 symbols={}
 for i,s in enumerate(sh):
  if s[1]!=2:continue
  strings=sect(s[6]);symbols[i]=[]
  for off in range(s[4],s[4]+s[5],s[9]):
   name,value,size,info,other,index=struct.unpack_from('>IIIBBH',data,off)
   symbols[i].append({'name':string(strings,name),'value':value,'size':size,'section_index':index,'info':info})
 symbol=next(v for syms in symbols.values() for v in syms if v['name']==TARGET)
 start=symbol['value'];end=start+symbol['size'];text=sect(symbol['section_index'])[start:end]
 relocs=[]
 for s in sh:
  if s[1] not in (4,9) or s[7]!=symbol['section_index']:continue
  assert s[1]==4,'Require explicit ELF addends; do not guess implicit PPC addends'
  for off in range(s[4],s[4]+s[5],s[9]):
   site,info,addend=struct.unpack_from('>IIi',data,off)
   if not start<=site<end:continue
   target=symbols[s[6]][info>>8]
   name=target['name']
   # Resolve defined local/section symbols to section-relative addresses, preserving named externals.
   section=target['section_index']
   resolved={'name':name,'value':target['value'],'section':names[section] if 0<section<len(sh) else 'UND' if section==0 else str(section)}
   relocs.append({'site':site-start,'type':info&255,'target':resolved,'addend':addend})
 return {'path':path,'size':len(text),'text_sha256':hashlib.sha256(text).hexdigest(),'text_hex':text.hex(),'relocations':relocs}

def main():
 result={'version':1,'assignment_id':ID,'target':TARGET,'commands':[]}
 for mode,args in [('canonical',[]),('strict',['-c','function_reloc_diffs=name_address'])]:
  report='reports/GEDE01/'+('objdiff-canonical-' if mode=='canonical' else 'objdiff-')+ID+'.json'
  cmd=['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_8000F774',TARGET,'-o',report,'--format','json-pretty']+args
  p=subprocess.run(cmd,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
  result['commands'].append({'argv':cmd,'returncode':p.returncode,'raw_output':p.stdout})
  assert p.returncode==0,p.stdout
  diff=json.loads(Path(report).read_text())
  result[mode]={}
  for side in ['left','right']:
   s=next(x for x in diff[side]['symbols'] if x['name']==TARGET)
   result[mode][side]={'size':s['size'],'match_percent':s['match_percent'],'instruction_count':sum('instruction' in x for x in s['instructions']),'diff_rows':sum(bool(x.get('diff_kind')) for x in s['instructions'])}
   assert s['match_percent']==100,(mode,side,s['match_percent'])
 a=elf('build/GEDE01/obj/game/game_fn_8000F774.o');b=elf('build/GEDE01/src/game/game_fn_8000F774.o')
 result['retail']=a;result['compiled']=b
 result['bytes_equal']=a['text_hex']==b['text_hex']
 result['relocations_equal']=a['relocations']==b['relocations']
 result['source_sha256']=hashlib.sha256(Path('src/game/game_fn_8000F774.c').read_bytes()).hexdigest()
 result['compiler']='GC/1.3; canonical configure.py flags unchanged'
 out=Path('reports/GEDE01/verification-'+ID+'.json');out.write_text(json.dumps(result,indent=2)+'\n')
 print(json.dumps({k:v for k,v in result.items() if k not in ['commands','retail','compiled']},indent=2))
 print('retail_size',a['size'],'compiled_size',b['size'],'retail_relocations',len(a['relocations']),'compiled_relocations',len(b['relocations']))
 assert result['bytes_equal'] and result['relocations_equal']
if __name__=='__main__':main()
