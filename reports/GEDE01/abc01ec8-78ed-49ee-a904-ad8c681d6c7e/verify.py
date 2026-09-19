from pathlib import Path
import subprocess,json,hashlib,re,difflib
ROOT=Path(__file__).resolve().parents[3];R=Path(__file__).resolve().parent
ID='abc01ec8-78ed-49ee-a904-ad8c681d6c7e';TARGET='fn_8014B0F0'
records=[]
def run(name,cmd):
 p=subprocess.run(cmd,cwd=ROOT,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
 (R/(name+'.txt')).write_text(p.stdout)
 records.append({'cwd':'eternal-darkness-decomp','command':cmd,'exit_code':p.returncode,'raw_output_file':str(Path('eternal-darkness-decomp')/(R/(name+'.txt')).relative_to(ROOT))})
 (R/'verification-commands.json').write_text(json.dumps(records,indent=2)+'\n')
 if p.returncode:raise RuntimeError(p.stdout)
 return p.stdout
run('configure-final',['python3','configure.py'])
run('build-final',['.tools/bin/ninja','-j2'])
run('build-function',['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_8014B0F0.o'])
run('compiler-command',['.tools/bin/ninja','-t','commands','build/GEDE01/src/game/game_fn_8014B0F0.o'])
sha=run('dol-sha1',['sha1sum','build/GEDE01/main.dol']).split()[0]
assert sha=='ea24b6af954876ce072562ff39cdb4c81d32be1f'
for name,extra in [('canonical',[]),('strict',['-c','function_reloc_diffs=name_address'])]:
 dest=Path('reports/GEDE01')/('objdiff-'+ID+'.json') if name=='canonical' else R.relative_to(ROOT)/'strict.json'
 run('objdiff-'+name,['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_8014B0F0',TARGET,'-o',str(dest),'--format','json-pretty']+extra)
run('fndiff',['python3','tools/fndiff.py','game/game_fn_8014B0F0.c',TARGET])
rel=[]
for name,path in [('target','build/GEDE01/obj/game/game_fn_8014B0F0.o'),('candidate','build/GEDE01/src/game/game_fn_8014B0F0.o')]:
 raw=run('relocations-'+name,['readelf','-rW',path])
 # These ELF32 objects carry SHT_RELA: readelf prints each explicit signed addend.
 entries=[]
 for line in raw.splitlines():
  m=re.match(r'\s*([0-9a-f]+)\s+[0-9a-f]+\s+(R_PPC_\w+)\s+([0-9a-f]+)\s+(\S+)\s+([+-])\s+([0-9a-f]+)\s*$',line)
  if m:entries.append({'offset':int(m[1],16),'type':m[2],'target_value':int(m[3],16),'target':m[4],'addend':int(m[6],16)*(1 if m[5]=='+' else -1)})
 rel.append(entries)
assert len(rel[0])==len(rel[1])==18 and rel[0]==rel[1]
(R/'relocations.json').write_text(json.dumps({'representation':'ELF SHT_RELA explicit addends; parsed from preserved readelf -rW outputs','target':rel[0],'candidate':rel[1],'equal':True},indent=2)+'\n')
run('legal-audit',['python3','tools/legal_audit.py'])
run('scope-status',['git','status','--short'])
base=(R/'baseline.c.txt').read_text();source=(ROOT/'src/game/game_fn_8014B0F0.c').read_text()
(R/'final.patch').write_text(''.join(difflib.unified_diff(base.splitlines(True),source.splitlines(True),fromfile='a/eternal-darkness-decomp/src/game/game_fn_8014B0F0.c',tofile='b/eternal-darkness-decomp/src/game/game_fn_8014B0F0.c')))
summary={'dol_sha1':sha,'source_sha256':hashlib.sha256(source.encode()).hexdigest(),'comparisons':{}}
for name,path in [('canonical',ROOT/'reports/GEDE01'/('objdiff-'+ID+'.json')),('strict',R/'strict.json')]:
 d=json.loads(path.read_text());l=next(s for s in d['left']['symbols'] if s['name']==TARGET);r=next(s for s in d['right']['symbols'] if s['name']==TARGET)
 diffs=[]
 for a,b in zip(l['instructions'],r['instructions']):
  ai=a.get('instruction',{});bi=b.get('instruction',{})
  if ai.get('formatted')!=bi.get('formatted'):diffs.append({'target_address':ai.get('address'),'candidate_address':bi.get('address'),'target':ai.get('formatted'),'candidate':bi.get('formatted')})
 summary['comparisons'][name]={'target_size':l['size'],'candidate_size':r['size'],'match_percent':l['match_percent'],'formatted_instruction_differences':diffs}
(R/'verification-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print(json.dumps(summary,indent=2))
