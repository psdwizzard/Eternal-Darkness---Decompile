"""Run from the project directory; capture exact patch, commands and raw measurements."""
import difflib, hashlib, json, subprocess, sys
from pathlib import Path
assignment = 'f4fb9fd0-4574-4a86-a8ab-ee5358f036f4'
source = Path('src/game/game_fn_8006330C.c')
report = Path(f'reports/GEDE01/experiments-{assignment}.json')
name, hypothesis = sys.argv[1:3]
base = subprocess.check_output(['git', 'show', 'bdd16be340554b66efc12987d07eaf45fb03e2a3:eternal-darkness-decomp/'+str(source)], text=True)
current = source.read_text()
entry = {'name':name, 'hypothesis':hypothesis, 'cwd':'eternal-darkness-decomp', 'source_sha256':hashlib.sha256(current.encode()).hexdigest(), 'patch_from_base':''.join(difflib.unified_diff(base.splitlines(True),current.splitlines(True),fromfile=str(source),tofile=str(source))), 'commands':[], 'raw_reports':[]}
commands = [['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_8006330C.o']]
for mode in ['canonical','strict']:
 output = f'reports/GEDE01/objdiff-{assignment}-{name}-{mode}.json'
 command = ['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_8006330C','fn_8006330C','-o',output,'--format','json']
 if mode == 'strict': command += ['-c','functionRelocDiffs=all']
 commands.append(command)
 entry['raw_reports'].append('eternal-darkness-decomp/'+output)
for command in commands:
 result = subprocess.run(command,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
 entry['commands'].append({'argv':command,'exit_code':result.returncode,'output':result.stdout})
 if result.returncode: break
else:
 entry['measurements']={}
 for mode,path in zip(['canonical','strict'],entry['raw_reports']):
  data=json.loads(Path(path.removeprefix('eternal-darkness-decomp/')).read_text())
  sides={side:next(s for s in data[side]['symbols'] if s['name']=='fn_8006330C') for side in ['left','right']}
  entry['measurements'][mode]={side:{k:s.get(k) for k in ['size','match_percent']} for side,s in sides.items()}
data=json.loads(report.read_text())
data['experiments'].append(entry)
report.write_text(json.dumps(data,indent=2)+'\n')
print(json.dumps(entry.get('measurements',entry),indent=2))
