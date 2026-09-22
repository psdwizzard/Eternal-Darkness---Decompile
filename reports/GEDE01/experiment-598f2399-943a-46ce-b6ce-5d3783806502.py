"""Assignment-local declaration/scope experiment; run from project root."""
import json, subprocess, hashlib, difflib
from pathlib import Path
root=Path.cwd()
src=root/'src/game/game_fn_8018F378.c'
base=subprocess.check_output(['git','show','63714bfb:eternal-darkness-decomp/src/game/game_fn_8018F378.c'],text=True)
prefix=root/'reports/GEDE01'
log=prefix/'experiments-598f2399-943a-46ce-b6ce-5d3783806502.json'
results=[]
variants=[('baseline',base)]
for name,decl in [('iterator','u8* iterator;'),('other_x','int other_x;'),('object','void* object;'),('owner','void* owner;')]:
    variants.append(('register_'+name,base.replace(decl,'register '+decl)))
variants.append(('iterator_function_scope',base.replace('        u8* iterator;\n','').replace('    u8* entry =','    u8* iterator;\n    u8* entry =')))
variants.append(('iterator_after_position',base.replace('        u8* iterator;\n        Vec3 position;','        Vec3 position;\n        u8* iterator;')))
for name,decl in [('other_x','int other_x;'),('object','void* object;'),('owner','void* owner;')]:
    for place in ['before_iterator','after_iterator']:
        v=base.replace('                '+decl+'\n','')
        marker='        u8* iterator;'
        v=v.replace(marker,('        '+decl+'\n'+marker) if place=='before_iterator' else (marker+'\n        '+decl))
        variants.append((name+'_'+place,v))
variants.append(('object_before_x',base.replace('                int other_x;\n                void* object;','                void* object;\n                int other_x;')))
variants.append(('x_after_deltas',base.replace('                int other_x;\n','').replace('                u32 delta_z;','                u32 delta_z;\n                int other_x;')))
best=base
bestscore=0
try:
    for name,code in variants:
        src.write_text(code)
        build=subprocess.run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_8018F378.o'],text=True,capture_output=True)
        row={'name':name,'patch':''.join(difflib.unified_diff(base.splitlines(True),code.splitlines(True))),'build_stdout':build.stdout,'build_stderr':build.stderr,'build_exit':build.returncode}
        if build.returncode==0:
            out=prefix/'variant-598f2399-943a-46ce-b6ce-5d3783806502.json'
            proc=subprocess.run(['build/tools/objdiff-cli','diff','-p','.', '-u','main/game/game_fn_8018F378','fn_8018F378','-o',str(out),'--format','json'],text=True,capture_output=True)
            data=json.loads(out.read_text())
            l=next(s for s in data['left']['symbols'] if s['name']=='fn_8018F378')
            r=next(s for s in data['right']['symbols'] if s['name']=='fn_8018F378')
            row.update(score=l['match_percent'],size=r['size'],diff_stdout=proc.stdout,diff_stderr=proc.stderr,differences=[{'left':a.get('instruction',{}).get('formatted'),'right':b.get('instruction',{}).get('formatted'),'offset':a.get('instruction',{}).get('address','0'),'kind':a.get('diff_kind')} for a,b in zip(l['instructions'],r['instructions']) if a.get('diff_kind') not in (None,'DIFF_NONE')])
            if row['score']>bestscore:
                bestscore=row['score'];best=code
            print(name,row['score'],row['size'],flush=True)
        results.append(row)
        log.write_text(json.dumps(results,indent=2)+'\n')
        if bestscore==100:break
finally:
    src.write_text(best)
