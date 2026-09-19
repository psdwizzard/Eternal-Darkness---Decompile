import subprocess, json, difflib, hashlib
from pathlib import Path
ROOT=Path(__file__).resolve().parents[3]
OUT=Path(__file__).resolve().parent
SOURCE=ROOT/'src/game/game_fn_8019C3B8.c'
BASE=subprocess.check_output(['git','show','56f446013dede77667a6b2700dedcea0e70b6ede:eternal-darkness-decomp/src/game/game_fn_8019C3B8.c'],cwd=ROOT,text=True)
def run(name,args):
    p=subprocess.run(args,cwd=ROOT,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    (OUT/(name+'.log')).write_text('$ '+' '.join(args)+'\n'+p.stdout+'\nexit_code='+str(p.returncode)+'\n')
    print(name, p.returncode, p.stdout[-700:],flush=True)
    if p.returncode: raise RuntimeError(name)
def diff(name,strict=False):
    args=['build/tools/objdiff-cli','diff','-p','.']
    if strict: args+=['-c','function_reloc_diffs=name_address']
    args+=['-o',str((OUT/(name+'.json')).relative_to(ROOT)),'--format','json-pretty','fn_8019C3B8']
    run(name,args)
    d=json.loads((OUT/(name+'.json')).read_text())
    a=next(s for s in d['left']['symbols'] if s['name']=='fn_8019C3B8')
    b=next(s for s in d['right']['symbols'] if s['name']=='fn_8019C3B8')
    print(name, a['size'], b['size'], a.get('match_percent'),flush=True)
def variant(name,text):
    (OUT/(name+'.patch')).write_text(''.join(difflib.unified_diff(BASE.splitlines(True),text.splitlines(True),fromfile='a/eternal-darkness-decomp/src/game/game_fn_8019C3B8.c',tofile='b/eternal-darkness-decomp/src/game/game_fn_8019C3B8.c')))
    SOURCE.write_text(text)
    try:
        run(name+'-build',['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_8019C3B8.o'])
        diff(name)
    finally: SOURCE.write_text(BASE)
if __name__=='__main__':
    assert SOURCE.read_text() == BASE, 'Run from the retained assignment source'
    run('configure',['python3','configure.py'])
    run('compiler-command',['.tools/bin/ninja','-t','commands','build/GEDE01/src/game/game_fn_8019C3B8.o'])
    run('baseline-build',['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_8019C3B8.o'])
    diff('baseline')
    variant('automatic-storage',BASE.replace('register u8*','u8*'))
    variant('derived-offset',BASE.replace('    int vertex_offset;\n','').replace('    vertex_offset = 0;\n','').replace('vertex_data + vertex_offset','vertex_data + i * 0x18').replace('        vertex_offset += 0x18;\n',''))
    run('restored-build',['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_8019C3B8.o'])
    diff('canonical')
    diff('relocation-strict',True)
    run('full-build',['.tools/bin/ninja','-j2'])
    run('dol-sha1',['sha1sum','build/GEDE01/main.dol','orig/GEDE01/sys/main.dol'])
    run('retail-relocations',['readelf','-W','-r','-s','build/GEDE01/obj/game/game_fn_8019C3B8.o'])
    run('candidate-relocations',['readelf','-W','-r','-s','build/GEDE01/src/game/game_fn_8019C3B8.o'])
    run('legal-audit',['python3','tools/legal_audit.py'])
    run('measure',['python3',str((OUT/'measure.py').relative_to(ROOT))])
