import hashlib,json,pathlib,re,struct,subprocess
ROOT=pathlib.Path(__file__).resolve().parents[3]
OUT=pathlib.Path(__file__).resolve().parent
ID='6e03fb5d-5b25-4c44-80b1-c8bd68b2f435'
def section(path,name):
 b=path.read_bytes();h=struct.unpack_from('>16sHHIIIIIHHHHHH',b);off=h[6];size=h[11];count=h[12];stridx=h[13]
 entries=[struct.unpack_from('>IIIIIIIIII',b,off+i*size) for i in range(count)]
 st=entries[stridx];names=b[st[4]:st[4]+st[5]]
 for e in entries:
  n=names[e[0]:].split(b'\0',1)[0].decode()
  if n==name:return b[e[4]:e[4]+e[5]]
 raise ValueError(name)
measure={}
for mode,path in [('canonical',OUT/'canonical-final.json'),('strict',OUT.parent/('objdiff-'+ID+'.json'))]:
 d=json.loads(path.read_text());fs=[next(s for s in d[k]['symbols'] if s['name']=='fn_80131460') for k in ['left','right']]
 assert all(f['match_percent']==100 and int(f['size'])==1292 for f in fs)
 assert all(not i.get('diff_kind') for f in fs for i in f['instructions'])
 measure[mode+'_match_percent']=fs[0]['match_percent']
 measure['relocation_bearing_instruction_counts']=[sum('relocation' in i['instruction'] for i in f['instructions']) for f in fs]
rows={}
for side in ['target','candidate']:
 text=(OUT/('relocations-'+side+'.txt')).read_text()
 rows[side]=[dict(offset=int(m[0],16),type=m[1],symbol=m[2],addend=int(m[4],16)*(1 if m[3]=='+' else -1)) for m in re.findall(r'^([0-9a-f]+)\s+[0-9a-f]+\s+(R_\S+)\s+[0-9a-f]+\s+(\S+)\s+([+-])\s+([0-9a-f]+)\s*$',text,re.M)]
assert len(rows['target'])==len(rows['candidate'])==85
assert rows['target']==rows['candidate']
(OUT/'relocations-verified.json').write_text(json.dumps(dict(equal=True,**rows),indent=2)+'\n')
textbytes=[section(ROOT/('build/GEDE01/'+p+'/game/game_fn_80131460.o'),'.text') for p in ['obj','src']]
assert len(textbytes[0])==len(textbytes[1])==1292
assert textbytes[0]==textbytes[1]
measure.update(text_bytes_equal=True,text_size=1292,text_sha256=hashlib.sha256(textbytes[0]).hexdigest(),exact_elf_relocations=85)
dol=ROOT/'build/GEDE01/main.dol';sha=hashlib.sha1(dol.read_bytes()).hexdigest();assert sha=='ea24b6af954876ce072562ff39cdb4c81d32be1f';measure['dol_sha1']=sha
measure['source_sha256']=hashlib.sha256((ROOT/'src/game/game_fn_80131460.c').read_bytes()).hexdigest()
cmd=subprocess.check_output(['.tools/bin/ninja','-t','commands','build/GEDE01/src/game/game_fn_80131460.o'],cwd=ROOT,text=True).splitlines()[-1]
measure['canonical_compile_command']=cmd
measure['compiler_sha256']=hashlib.sha256((ROOT/'compilers/GC/1.3/mwcceppc.exe').read_bytes()).hexdigest()
(OUT/'verification.json').write_text(json.dumps(measure,indent=2)+'\n')
print(json.dumps(measure,indent=2))
