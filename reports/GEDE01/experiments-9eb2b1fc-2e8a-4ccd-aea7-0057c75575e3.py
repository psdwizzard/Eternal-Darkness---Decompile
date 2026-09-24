"""Assignment-specific experiment recorder; run from project root."""
import difflib, hashlib, json, pathlib, struct, subprocess
ID='9eb2b1fc-2e8a-4ccd-aea7-0057c75575e3'
source=pathlib.Path('src/game/game_fn_801BA2A4.c')
report=pathlib.Path('reports/GEDE01/experiments-'+ID+'.json')
raw=pathlib.Path('reports/GEDE01/objdiff-'+ID+'.json')
baseline=subprocess.check_output(['git','show','07a5ed5:eternal-darkness-decomp/'+str(source)],text=True)
def command(args):
 p=subprocess.run(args,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
 return {'argv':args,'exit_code':p.returncode,'output':p.stdout}
def text_hash(path):
 data=pathlib.Path(path).read_bytes()
 shoff=struct.unpack_from('>I',data,32)[0]
 entsize,count,names=struct.unpack_from('>HHH',data,46)
 sections=[struct.unpack_from('>10I',data,shoff+i*entsize) for i in range(count)]
 ns=sections[names]; strings=data[ns[4]:ns[4]+ns[5]]
 for s in sections:
  if strings[s[0]:].split(b'\0')[0]==b'.text':
   return hashlib.sha256(data[s[4]:s[4]+s[5]]).hexdigest()
def measure(name,candidate):
 source.write_text(candidate)
 commands=[command(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_801BA2A4.o'])]
 if commands[-1]['exit_code']: raise RuntimeError(commands[-1])
 commands.append(command(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_801BA2A4','fn_801BA2A4','-o',str(raw),'--format','json-pretty','-c','function_reloc_diffs=name_address']))
 if commands[-1]['exit_code']: raise RuntimeError(commands[-1])
 d=json.loads(raw.read_text());syms=[next(s for s in d[k]['symbols'] if s['name']=='fn_801BA2A4') for k in ['left','right']]
 record={'name':name,'source_sha256':hashlib.sha256(candidate.encode()).hexdigest(),'patch_from_preserved_source':''.join(difflib.unified_diff(baseline.splitlines(True),candidate.splitlines(True),fromfile='preserved',tofile=name)), 'commands':commands,'retail_bytes':syms[0]['size'],'generated_bytes':syms[1]['size'],'strict_match_percent':syms[0]['match_percent'],'text_sha256':text_hash('build/GEDE01/src/game/game_fn_801BA2A4.o'),'generated_instructions':[s.get('instruction',{}).get('formatted','') for s in syms[1]['instructions']]}
 records=json.loads(report.read_text()) if report.exists() else []
 records.append(record);report.write_text(json.dumps(records,indent=2)+'\n')
 print(name,record['strict_match_percent'],record['generated_bytes'],record['text_sha256'],flush=True)
 return record

def recover(name):
 import re
 records=json.loads(report.read_text());e=next(e for e in records if e['name']==name)
 lines=baseline.splitlines(True);out=[];pos=0
 for line in e['patch_from_preserved_source'].splitlines(True)[2:]:
  if line.startswith('@@'):
   start=int(re.match(r'@@ -(\d+)',line)[1])-1;out.extend(lines[pos:start]);pos=start
  elif line.startswith(' '): out.append(line[1:]);pos+=1
  elif line.startswith('-'): pos+=1
  elif line.startswith('+'): out.append(line[1:])
 out.extend(lines[pos:]);return ''.join(out)
