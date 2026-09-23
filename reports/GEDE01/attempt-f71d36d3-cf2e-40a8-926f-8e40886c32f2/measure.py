import json, subprocess, sys, time
from pathlib import Path
ROOT=Path(__file__).resolve().parents[3]
REPORT=Path(__file__).resolve().parent
SRC=ROOT/'src/game/game_fn_801E7CBC.c'
def run(args, name):
    start=time.time()
    p=subprocess.run(args,cwd=ROOT,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
    (REPORT/(name+'.log')).write_text('$ '+ ' '.join(args)+'\n'+p.stdout+'\nexit_code='+str(p.returncode)+'\n')
    print(name, p.returncode, p.stdout[-600:],flush=True)
    if p.returncode: raise SystemExit(p.returncode)
    return p.stdout
name=sys.argv[1]
if name=='configure':
    run(['python3','configure.py'],'configure')
elif name=='build':
    run(['.tools/bin/ninja','-j2'],'full-build')
    run(['sha1sum','build/GEDE01/main.dol','orig/GEDE01/sys/main.dol'],'dol-sha1')
else:
    (REPORT/(name+'.c.txt')).write_text(SRC.read_text())
    run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_801E7CBC.o'],name+'-build')
    for mode, config in [('canonical',[]),('strict',['-c','function_reloc_diffs=name_address'])]:
        out=REPORT/(name+'-'+mode+'.json')
        run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_801E7CBC','-o',str(out.relative_to(ROOT)),'--format','json-pretty',*config,'fn_801E7CBC'],name+'-'+mode)
        data=json.loads(out.read_text())
        for side in ['left','right']:
            sym=next(x for x in data[side]['symbols'] if x['name']=='fn_801E7CBC')
            print(mode, side, sym.get('size'),sym.get('match_percent'),flush=True)
