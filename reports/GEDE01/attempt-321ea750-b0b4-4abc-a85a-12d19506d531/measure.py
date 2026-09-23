import json, pathlib, subprocess, sys, hashlib
root=pathlib.Path(__file__).resolve().parents[3]
r=pathlib.Path(__file__).resolve().parent
name=sys.argv[1]
src=root/'src/game/game_fn_80198850.c'
record={'name':name,'source':src.read_text(),'source_sha256':hashlib.sha256(src.read_bytes()).hexdigest(),'runs':[]}
cmds=[['.tools/bin/ninja','-j2','-v','build/GEDE01/src/game/game_fn_80198850.o'], ['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80198850','fn_80198850','-o',str((r/(name+'.json')).relative_to(root)),'--format','json']]
for cmd in cmds:
 p=subprocess.run(cmd,cwd=root,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
 record['runs'].append({'command':cmd,'cwd':'eternal-darkness-decomp','exit_code':p.returncode,'output':p.stdout})
 if p.returncode: break
(r/(name+'-reproduction.json')).write_text(json.dumps(record,indent=2)+'\n')
if p.returncode: sys.exit(p.returncode)
d=json.loads((r/(name+'.json')).read_text())
print(name,[(s['name'],s.get('size'),s.get('match_percent')) for s in d['left']['symbols'] if s['name']=='fn_80198850'],[(s['name'],s.get('size')) for s in d['right']['symbols'] if s['name']=='fn_80198850'])
