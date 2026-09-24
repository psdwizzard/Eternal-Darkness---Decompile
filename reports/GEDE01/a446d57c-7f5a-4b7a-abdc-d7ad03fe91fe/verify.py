import pathlib, json, struct, hashlib, subprocess, collections
root=pathlib.Path(__file__).resolve().parents[3]
r=pathlib.Path(__file__).resolve().parent
assignment='a446d57c-7f5a-4b7a-abdc-d7ad03fe91fe'
prefix='eternal-darkness-decomp/'
def section(path,name):
 b=path.read_bytes(); assert b[:6]==b'\x7fELF\x01\x02'
 off=struct.unpack_from('>I',b,32)[0]; ents,n,idx=struct.unpack_from('>HHH',b,46)
 sections=[struct.unpack_from('>10I',b,off+i*ents) for i in range(n)]
 names=sections[idx]; names=b[names[4]:names[4]+names[5]]
 for s in sections:
  if names[s[0]:].split(b'\0',1)[0].decode()==name: return b[s[4]:s[4]+s[5]]
 raise ValueError(name)
objects=[root/'build/GEDE01/obj/game/game_fn_80088A04.o',root/'build/GEDE01/src/game/game_fn_80088A04.o']
texts=[section(p,'.text') for p in objects]
raw={ 'sizes':list(map(len,texts)), 'sha256':[hashlib.sha256(b).hexdigest() for b in texts], 'identical_bytes_at_same_offset':sum(a==b for a,b in zip(*texts)), 'differing_word_offsets':[hex(i) for i in range(0,256,4) if texts[0][i:i+4]!=texts[1][i:i+4]], 'exact_byte_match':texts[0]==texts[1] }
(r/'byte-comparison.json').write_text(json.dumps(raw,indent=2)+'\n')
relocs=[]
for side in ['retail','generated']:
 rows=[]
 for line in (r/(side+'-relocations.log')).read_text().splitlines():
  t=line.split()
  if len(t)==7 and t[2].startswith('R_PPC_'): rows.append({'offset':t[0],'type':t[2],'target':t[4],'addend':t[6]})
 assert len(rows)==8
 relocs.append(rows)
assert collections.Counter((x['type'],x['target'],x['addend']) for x in relocs[0])==collections.Counter((x['type'],x['target'],x['addend']) for x in relocs[1])
(r/'relocation-audit.json').write_text(json.dumps({'material_relocations_per_side':8,'none_annotations_per_side':4,'material_targets_and_addends_equal':True,'retail':relocs[0],'generated':relocs[1]},indent=2)+'\n')
for suffix in ['', '-relocation-strict']:
 d=json.loads((root/('reports/GEDE01/objdiff-'+assignment+suffix+'.json')).read_text())
 for side in ['left','right']:
  s=next(s for s in d[side]['symbols'] if s['name']=='fn_80088A04')
  assert s['match_percent']==89.6875 and int(s['size'])==256
  annotations=[i['instruction']['relocation'] for i in s['instructions'] if 'relocation' in i.get('instruction',{})]
  assert sum(x.get('type',0)==0 for x in annotations)==4
sha=subprocess.check_output(['sha1sum','build/GEDE01/main.dol'],cwd=root,text=True)
(r/'dol-sha1.log').write_text(sha)
assert sha.split()[0]=='ea24b6af954876ce072562ff39cdb4c81d32be1f'
print(json.dumps(raw,indent=2));print(sha.strip());print('Relocation and score assertions passed.')
