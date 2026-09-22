"""Read-only ELF32 BE code/relocation verification; run from project root."""
import hashlib, json, struct
from pathlib import Path
ID = 'c59a1443-b809-419b-b726-4d3272c89ce2'
def elf(path):
 data=Path(path).read_bytes()
 assert data[:6] == b'\x7fELF\x01\x02'
 shoff=struct.unpack_from('>I',data,32)[0]
 entsize,count,names=struct.unpack_from('>HHH',data,46)
 headers=[struct.unpack_from('>10I',data,shoff+i*entsize) for i in range(count)]
 def content(h): return data[h[4]:h[4]+h[5]]
 def string(table,offset): return table[offset:table.index(b'\x00',offset)].decode()
 table=content(headers[names])
 sections={string(table,h[0]):(i,h) for i,h in enumerate(headers)}
 idx,th=sections['.text']; code=content(th)
 reloc=[]
 for h in headers:
  if h[1]!=4 or h[7]!=idx: continue
  symh=headers[h[6]]; strings=content(headers[symh[6]])
  for off in range(h[4],h[4]+h[5],h[9]):
   address,info,addend=struct.unpack_from('>IIi',data,off)
   symbol=struct.unpack_from('>IIIBBH',data,symh[4]+(info>>8)*symh[9])
   reloc.append({'offset':address,'type':info&255,'target':string(strings,symbol[0]),'addend':addend})
 return {'path':'eternal-darkness-decomp/'+path,'text_bytes':len(code),'text_sha256':hashlib.sha256(code).hexdigest(),'relocations':reloc},code
left,a=elf('build/GEDE01/obj/game/game_fn_800A0140.o')
right,b=elf('build/GEDE01/src/game/game_fn_800A0140.o')
result={'target':left,'generated':right,'text_bytes_equal':a==b,'relocations_equal':left['relocations']==right['relocations']}
print(json.dumps(result,indent=2))
assert result['text_bytes_equal'] and result['relocations_equal']
for suffix in ['', '-strict']:
 d=json.loads(Path(f'reports/GEDE01/objdiff{suffix}-{ID}.json').read_text())
 sym=next(s for s in d['left']['symbols'] if s['name']=='fn_800A0140')
 assert sym['match_percent']==100
