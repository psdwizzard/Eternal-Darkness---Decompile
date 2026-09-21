"""Assignment-local experiment runner; patches are relative to accepted base."""
import pathlib, subprocess, json, difflib, sys
root=pathlib.Path(__file__).resolve().parents[3]
report=pathlib.Path(__file__).resolve().parent
source=root/'src/game/game_fn_801EFA68.c'
base=subprocess.check_output(['git','show','a83620c53978edc11586cc4634ba9c4bfb3775f4:eternal-darkness-decomp/src/game/game_fn_801EFA68.c'],cwd=root,text=True)
def run(name, text):
    source.write_text(text)
    patch=''.join(difflib.unified_diff(base.splitlines(True),text.splitlines(True),fromfile='a/eternal-darkness-decomp/src/game/game_fn_801EFA68.c',tofile='b/eternal-darkness-decomp/src/game/game_fn_801EFA68.c'))
    (report/(name+'.patch')).write_text(patch)
    commands=[]
    cmd=['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_801EFA68.o']
    p=subprocess.run(cmd,cwd=root,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    commands.append({'command':cmd,'cwd':'eternal-darkness-decomp','exit_code':p.returncode,'output':p.stdout})
    if p.returncode==0:
      for kind,extra in [('canonical',[]),('strict',['-c','functionRelocDiffs=all'])]:
        out=report/(name+'-'+kind+'.json')
        cmd=['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_801EFA68','fn_801EFA68','--format','json','-o',str(out.relative_to(root))]+extra
        p=subprocess.run(cmd,cwd=root,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
        commands.append({'command':cmd,'cwd':'eternal-darkness-decomp','exit_code':p.returncode,'output':p.stdout})
        if p.returncode==0:
          d=json.loads(out.read_text()); s=next(x for x in d['left']['symbols'] if x['name']=='fn_801EFA68'); t=next(x for x in d['right']['symbols'] if x['name']=='fn_801EFA68')
          print(name,kind,s['match_percent'],s['size'],t['size'],flush=True)
    (report/(name+'-commands.json')).write_text(json.dumps(commands,indent=2)+'\n')
if __name__=='__main__':
    run('baseline',base)
    one=base.replace('extern void fn_8015DAB0(char*, int, u32);','extern void fn_8015DAB0(void*);').replace('fn_8015DAB0(label, mode, initialValue);','fn_8015DAB0(label);').replace('void fn_801EFA68(DisplayConfig* config, int mode)','void fn_801EFA68(DisplayConfig* config)')
    run('one-pointer-call',one)
    two=one.replace('(((width + 15) & ~15) * height)','((u16)((width + 15) & ~15) * height)')
    run('u16-aligned-width',two)
