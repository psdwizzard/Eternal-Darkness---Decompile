import hashlib,json,pathlib,subprocess
root=pathlib.Path(__file__).resolve().parents[3]
r=pathlib.Path(__file__).resolve().parent
out=root/'reports/GEDE01'
aid='321ea750-b0b4-4abc-a85a-12d19506d531'
commands=[['python3','configure.py'],['.tools/bin/ninja','-j2'],['sha1sum','build/GEDE01/main.dol'],['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80198850','fn_80198850','-o',f'reports/GEDE01/objdiff-{aid}.json','--format','json'],['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80198850','fn_80198850','-c','function_reloc_diffs=name_address','-o',f'reports/GEDE01/objdiff-strict-{aid}.json','--format','json'],['readelf','-r','-s','build/GEDE01/obj/game/game_fn_80198850.o','build/GEDE01/src/game/game_fn_80198850.o'],['python3','tools/legal_audit.py']]
records=[]
for cmd in commands:
 p=subprocess.run(cmd,cwd=root,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
 records.append({'cwd':'eternal-darkness-decomp','command':cmd,'exit_code':p.returncode,'output':p.stdout})
 (r/'verification.json').write_text(json.dumps(records,indent=2)+'\n')
 print('exit',p.returncode, ' '.join(cmd),flush=True)
 assert p.returncode==0
 if cmd[0]=='sha1sum':assert p.stdout.split()[0]=='ea24b6af954876ce072562ff39cdb4c81d32be1f'
for prefix in ['objdiff-','objdiff-strict-']:
 d=json.loads((out/(prefix+aid+'.json')).read_text())
 sym=next(x for x in d['left']['symbols'] if x['name']=='fn_80198850')
 assert sym['match_percent']==100.0,sym['match_percent']
 print(prefix,sym['match_percent'],sym['size'])
