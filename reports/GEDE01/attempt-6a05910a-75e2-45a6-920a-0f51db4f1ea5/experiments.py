from pathlib import Path
import subprocess,json,difflib
D=Path(__file__).parent
P=Path('src/game/game_fn_8006B21C.c')
B=json.loads((D/'baseline.json').read_text())['source']
def run(name,hypothesis,s):
    P.write_text(s)
    commands=[['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_8006B21C.o'],['python3','tools/fndiff.py','game/game_fn_8006B21C.c','fn_8006B21C']]
    results=[]
    for cmd in commands:
        r=subprocess.run(cmd,text=True,capture_output=True)
        results.append({'command':cmd,'exit_code':r.returncode,'stdout':r.stdout,'stderr':r.stderr})
        if r.returncode: break
    (D/(name+'.json')).write_text(json.dumps({'hypothesis':hypothesis,'patch':''.join(difflib.unified_diff(B.splitlines(True),s.splitlines(True),fromfile='accepted-base',tofile=name)), 'results':results},indent=2)+'\n')
    if results[-1]['exit_code']==0:
        (D/(name+'-objdiff.json')).write_bytes(Path('build/GEDE01/fndiff_fn_8006B21C.json').read_bytes())
        print(name,results[-1]['stdout'].splitlines()[0],flush=True)
    else: print(name,results[-1],flush=True)
    return s
if __name__=='__main__':
    s=B.replace('extern u8 lbl_803108B8[];','extern GlobalState lbl_803108B8;').replace('(GlobalState *)lbl_803108B8','&lbl_803108B8')
    run('02-global-aggregate','Typed external aggregate may lower member addresses differently than cast from byte array',s)
    s=B.replace('&root->pad0','(u8 (*)[0x654])(unsigned int)root').replace('&root->state','(State *)((unsigned int)root + 0x654)').replace('(u8 *)state + 0x164','(void *)((unsigned int)root + 0x7B8)')
    run('03-integer-address','Integer/pointer conversion boundary may prevent base-displacement folding',s)
    s=B.replace('    State *state;','    register State *state;').replace('    GlobalState *root','    register GlobalState *root')
    run('04-register-locals','Explicit register storage may preserve separate local address nodes',s)
    s=B.replace('    State *state;','    union { State *state; unsigned int bits; } address;').replace('state = &root->state;','address.bits = (unsigned int)root + 0x654;').replace('state->','address.state->').replace('(u8 *)state','(u8 *)address.state').replace('fn_8006B364(state)','fn_8006B364(address.state)')
    run('05-union-address','A local union provides an integer-to-pointer representation boundary without volatile traffic',s)
    P.write_text(B)
