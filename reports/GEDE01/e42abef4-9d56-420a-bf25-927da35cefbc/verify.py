from experiment import *
commands=[]
for name,cmd in [('configure',['python3','configure.py']),('build',['.tools/bin/ninja','-j2']),('sha1',['sha1sum','build/GEDE01/main.dol']),('compiler-command',['.tools/bin/ninja','-t','commands','build/GEDE01/src/game/game_fn_801EFA68.o'])]:
    p=subprocess.run(cmd,cwd=root,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    (report/(name+'.log')).write_text(p.stdout)
    commands.append({'command':cmd,'cwd':'eternal-darkness-decomp','exit_code':p.returncode,'output_file':str((report/(name+'.log')).relative_to(root.parent))})
    (report/'verification-commands.json').write_text(json.dumps(commands,indent=2)+'\n')
    print(name,p.returncode,p.stdout[-1200:],flush=True)
    if p.returncode: raise SystemExit(p.returncode)
run('retained',source.read_text())
