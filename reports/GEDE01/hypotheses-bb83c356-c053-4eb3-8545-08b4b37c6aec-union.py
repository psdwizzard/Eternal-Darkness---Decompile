import itertools, json, subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[2]
source=root/'src/game/game_fn_8014BEC4.c'
original=source.read_text()
report=root/'reports/GEDE01'
aid='bb83c356-c053-4eb3-8545-08b4b37c6aec'
old="""    offset.x = lbl_8023A718.x;
    offset.y = lbl_8023A718.y;
    offset.z = lbl_8023A718.z;"""
results=[]
def run(args):
    p=subprocess.run(args,cwd=root,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    return {'command':args,'returncode':p.returncode,'output':p.stdout}
try:
    for order in [(0,1,2),(0,2,1)]:
        tag=''.join(map(str,order))
        replacement='\n'.join('    offset.%s.bits = lbl_8023A718.%s.bits;'%('xyz'[i],'xyz'[i]) for i in order)
        source.write_text(original.replace('extern Vec3 lbl_8023A718;', 'typedef union Word { float value; unsigned int bits; } Word;\ntypedef struct WordVec { Word x, y, z; } WordVec;\nextern WordVec lbl_8023A718;').replace('Vec3 offset;', 'WordVec offset;').replace('&offset, &base', '(Vec3*)&offset, &base').replace(old,replacement))
        row={'order':order,'replacement':replacement}
        row['compile']=run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_8014BEC4.o'])
        assert row['compile']['returncode']==0, row
        out=report/('objdiff-'+aid+'-union-'+tag+'.json')
        row['comparison']=run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_8014BEC4','fn_8014BEC4','-o',str(out.relative_to(root)),'--format','json-pretty','-c','function_reloc_diffs=name_address'])
        assert row['comparison']['returncode']==0, row
        data=json.loads(out.read_text())
        row['score']=data['left']['symbols'][0]['match_percent']
        row['size']=data['right']['symbols'][0]['size']
        results.append(row)
        print(tag,row['score'],row['size'],flush=True)
finally:
    source.write_text(original)
    (report/('hypotheses-'+aid+'-union.json')).write_text(json.dumps(results,indent=2)+'\n')
