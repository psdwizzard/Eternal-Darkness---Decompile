from pathlib import Path
import struct,json
ROOT=Path(__file__).resolve().parents[3];R=Path(__file__).resolve().parent

def text_section(path):
 data=path.read_bytes()
 assert data[:6]==b'\x7fELF\x01\x02'
 h=struct.unpack_from('>16sHHIIIIIHHHHHH',data)
 off,entsize,count,names_index=h[6],h[11],h[12],h[13]
 sections=[struct.unpack_from('>10I',data,off+i*entsize) for i in range(count)]
 names=sections[names_index];st=data[names[4]:names[4]+names[5]]
 for s in sections:
  name=st[s[0]:].split(b'\0',1)[0]
  if name==b'.text':return data[s[4]:s[4]+s[5]]
 raise AssertionError('missing .text')
a=text_section(ROOT/'build/GEDE01/obj/game/game_fn_8014B0F0.o');b=text_section(ROOT/'build/GEDE01/src/game/game_fn_8014B0F0.o')
assert len(a)==len(b)==588
words=[{'offset':i,'target_word':a[i:i+4].hex(),'candidate_word':b[i:i+4].hex()} for i in range(0,len(a),4) if a[i:i+4]!=b[i:i+4]]
result={'command':'python3 reports/GEDE01/abc01ec8-78ed-49ee-a904-ad8c681d6c7e/bytes.py','cwd':'eternal-darkness-decomp','target_text_size':len(a),'candidate_text_size':len(b),'differing_bytes':sum(x!=y for x,y in zip(a,b)),'differing_instruction_words':len(words),'differences':words}
assert len(words)==15
(R/'bytes.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps(result,indent=2))
