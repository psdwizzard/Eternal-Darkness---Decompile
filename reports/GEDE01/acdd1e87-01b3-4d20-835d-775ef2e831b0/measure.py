import json, subprocess, sys, pathlib, hashlib
root=pathlib.Path(__file__).resolve().parents[3]
d=pathlib.Path(__file__).resolve().parent
name=sys.argv[1]
src=root/'src/game/game_fn_801599BC.c'
record={'name':name,'cwd':'eternal-darkness-decomp','source':src.read_text(),'source_sha256':hashlib.sha256(src.read_bytes()).hexdigest(),'runs':[]}
commands=[['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_801599BC.o']]
for mode in ['canonical','strict']:
    output=d/(name+'-'+mode+'.json')
    cmd=['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_801599BC','-o',str(output.relative_to(root)),'--format','json']
    if mode=='strict':cmd+=['-c','function_reloc_diffs=name_address']
    cmd+=['fn_801599BC']
    commands.append(cmd)
for cmd in commands:
    p=subprocess.run(cmd,cwd=root,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    record['runs'].append({'argv':cmd,'returncode':p.returncode,'output':p.stdout})
    if p.returncode:break
(d/(name+'-run.json')).write_text(json.dumps(record,indent=2)+'\n')
for mode in ['canonical','strict']:
    path=d/(name+'-'+mode+'.json')
    if not path.exists():continue
    diff=json.loads(path.read_text())
    l=next(s for s in diff['left']['symbols'] if s['name']=='fn_801599BC')
    r=next(s for s in diff['right']['symbols'] if s['name']=='fn_801599BC')
    print(name,mode,l.get('match_percent'),l['size'],r['size'])
    lines=[]
    for side,sym in [('retail',l),('generated',r)]:
        lines.append(side)
        for ins in sym['instructions']:
            ins=ins.get('instruction')
            if ins:lines.append(f"{int(ins.get('address','0')):04x} {ins['formatted']}" )
    (d/(name+'-'+mode+'.txt')).write_text('\n'.join(lines)+'\n')
