"""Reproduce inline-helper FPR allocation experiments; no compiler setting changes."""
import itertools
import json
from pathlib import Path
import subprocess
import time
ID='6c72ffc3-3eab-4bdc-868a-f0c615c66ef1'
SOURCE=Path('src/game/game_fn_80120B58.c')
BASELINE=SOURCE.read_text()
LOG={'assignment_id':ID, 'hypothesis':'Inlining private C arithmetic/clamp helpers may change virtual FPR allocation through parameter binding, without compiler-setting changes or an out-of-line helper in the final reconstruction.', 'variants':[]}

def measure(name, source):
    SOURCE.write_text(source)
    record={'name':name,'source':source,'commands':[]}
    LOG['variants'].append(record)
    for cmd in [['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80120B58.o'],['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80120B58','fn_80120B58','-o','-','--format','json']]:
        p=subprocess.run(cmd,capture_output=True,text=True)
        record['commands'].append({'cwd':'eternal-darkness-decomp','argv':cmd,'exit_code':p.returncode,'stdout':p.stdout,'stderr':p.stderr})
        if p.returncode: break
    if not p.returncode:
        data=json.loads(p.stdout)
        s=next(s for s in data['left']['symbols'] if s['name']=='fn_80120B58')
        record['match_percent']=s['match_percent']
        record['generated_size']=next(s['size'] for s in data['right']['symbols'] if s['name']=='fn_80120B58')
        print(name,record['match_percent'],record['generated_size'],flush=True)
    else: print(name,'error',p.stdout,p.stderr,flush=True)
    Path('reports/GEDE01/helpers-'+ID+'.json').write_text(json.dumps(LOG,indent=2)+'\n')

try:
    header=BASELINE[:BASELINE.index('void fn_')]
    body=BASELINE[BASELINE.index('void fn_'):]
    for order in itertools.permutations(['value','step','bound']):
        for preload in [False,True]:
            helpers=''
            newbody=body
            for direction,step,bound,expr,op,globalname,comparison in [('down','decrement','minimum','object->decrement','-','lbl_806500A0','object->value <= bound'),('up','increment','maximum','lbl_806500C4','+','lbl_806500C8','bound == object->value')]:
                params=', '.join('float '+p for p in order)
                helpers+=f'static inline void {direction}(Object* object, {params})\n{{\n    object->value = value {op} step;\n    if ({comparison}) {{\n        object->value = bound;\n'+('        object->state = 0;\n' if direction=='down' else '')+'    }\n}\n\n'
                original=f'        float value = object->value;\n        float {step} = {expr};\n        float {bound} = {globalname};\n        object->value = value {op} {step};\n        if ('+('object->value <= minimum' if direction=='down' else 'maximum == object->value')+') {\n            object->value = '+bound+';\n'+('            object->state = 0;\n' if direction=='down' else '')+'        }'
                arguments={'value':'object->value','step':expr,'bound':globalname}
                declarations=''
                if preload:
                    declarations=f'        float value = object->value;\n        float {step} = {expr};\n        float {bound} = {globalname};\n'
                    arguments={'value':'value','step':step,'bound':bound}
                replacement=declarations+f'        {direction}(object, '+', '.join(arguments[p] for p in order)+');'
                assert original in newbody
                newbody=newbody.replace(original,replacement)
            measure('helpers_'+'_'.join(order)+('_preloaded' if preload else '_direct'),header+helpers+newbody)
finally:
    SOURCE.write_text(BASELINE)
    p=subprocess.run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80120B58.o'],capture_output=True,text=True)
    LOG['restore']={'argv':['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80120B58.o'],'exit_code':p.returncode,'stdout':p.stdout,'stderr':p.stderr}
    Path('reports/GEDE01/helpers-'+ID+'.json').write_text(json.dumps(LOG,indent=2)+'\n')
