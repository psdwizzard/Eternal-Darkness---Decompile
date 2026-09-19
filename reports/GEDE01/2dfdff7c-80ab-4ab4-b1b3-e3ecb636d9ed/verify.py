import json,pathlib,re,hashlib
ROOT=pathlib.Path('.')
R=ROOT/'reports/GEDE01/2dfdff7c-80ab-4ab4-b1b3-e3ecb636d9ed'
rows={}
for side in ('target','candidate'):
 text=(R/('relocations-'+side+'.txt')).read_text()
 rows[side]=[{'offset':int(m[0],16),'type':m[1],'symbol':m[2],'addend':int(m[4],16)*(1 if m[3]=='+' else -1)} for m in re.findall(r'^([0-9a-f]+)\s+[0-9a-f]+\s+(R_\S+)\s+[0-9a-f]+\s+(\S+)\s+([+-])\s+([0-9a-f]+)\s*$',text,re.M)]
assert len(rows['target'])==len(rows['candidate'])==49
assert rows['target']==rows['candidate']
(R/'relocations-final.json').write_text(json.dumps({'equal':True,'target_count':49,'candidate_count':49,**rows},indent=2)+'\n')
measure={};diffs=[]
for mode in ('canonical','strict'):
 d=json.loads((R/(mode+'-final.json')).read_text())
 symbols=[next(s for s in d[side]['symbols'] if s.get('name')=='fn_80205914') for side in ('left','right')]
 assert all(int(s['size'])==900 for s in symbols)
 assert all(s['match_percent']==99.41333 for s in symbols)
 measure[mode+'_match_percent']=symbols[0]['match_percent']
 if mode=='strict':
  ins=[{int(x['instruction'].get('address',0)):x['instruction']['formatted'] for x in s['instructions'] if 'instruction' in x} for s in symbols]
  diffs=[{'offset':hex(a),'retail':ins[0][a],'candidate':ins[1][a]} for a in ins[0] if ins[0][a]!=ins[1][a]]
assert len(diffs)==6
sha=(R/'dol-sha1.txt').read_text().split()[0]
assert sha=='ea24b6af954876ce072562ff39cdb4c81d32be1f'
measure.update(target_size=900,candidate_size=900,different_instructions=6,exact_relocations=49,dol_sha1=sha)
(R/'measurements.json').write_text(json.dumps({'measurements':measure,'instruction_differences':diffs},indent=2)+'\n')
trials=0
for p in R.glob('experiments*.json'):
 for row in json.loads(p.read_text()):
  f=pathlib.Path(row['raw_objdiff']).relative_to('eternal-darkness-decomp')
  assert hashlib.sha256(f.read_bytes()).hexdigest()==row['raw_objdiff_sha256']
  trials+=1
print(json.dumps({'verification':'passed','trials_with_verified_raw_outputs':trials,**measure},indent=2))
