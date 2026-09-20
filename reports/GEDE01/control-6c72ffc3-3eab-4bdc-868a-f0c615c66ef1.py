"""Reproduce equivalent control-flow formulations under canonical flags."""
import itertools,json,subprocess
from pathlib import Path
ID='6c72ffc3-3eab-4bdc-868a-f0c615c66ef1'
SOURCE=Path('src/game/game_fn_80120B58.c')
BASELINE=SOURCE.read_text()
LOG={'assignment_id':ID,'hypothesis':'Equivalent guard/exit CFG construction may change virtual-register visitation and coloring while preserving final instruction order. Negated <= is retained to preserve unordered-float behavior.','variants':[]}

def measure(name,source):
    SOURCE.write_text(source)
    r={'name':name,'source':source,'commands':[]}
    LOG['variants'].append(r)
    for cmd in [['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80120B58.o'],['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80120B58','fn_80120B58','-o','-','--format','json']]:
        p=subprocess.run(cmd,capture_output=True,text=True)
        r['commands'].append({'cwd':'eternal-darkness-decomp','argv':cmd,'exit_code':p.returncode,'stdout':p.stdout,'stderr':p.stderr})
        if p.returncode: break
    if not p.returncode:
        d=json.loads(p.stdout)
        r['match_percent']=next(s['match_percent'] for s in d['left']['symbols'] if s['name']=='fn_80120B58')
        r['generated_size']=next(s['size'] for s in d['right']['symbols'] if s['name']=='fn_80120B58')
        print(name,r['match_percent'],r['generated_size'],flush=True)
    else: print(name,'error',p.stdout,p.stderr,flush=True)
    Path('reports/GEDE01/control-'+ID+'.json').write_text(json.dumps(LOG,indent=2)+'\n')

try:
    header=BASELINE[:BASELINE.index('void fn_')]
    for dec_guard,dec_clamp,inc_guard,inc_clamp in itertools.product([False,True],repeat=4):
        s=header+'void fn_80120B58(Object* object)\n{\n'
        s+=('    if (!(object->state & 2)) goto up;\n    if (object->state & 0x200) goto up;\n    {\n' if dec_guard else '    if ((object->state & 2) && !(object->state & 0x200)) {\n')
        s+='        float value = object->value;\n        float decrement = object->decrement;\n        float minimum = lbl_806500A0;\n        object->value = value - decrement;\n'
        s+=('        if (!(object->value <= minimum)) goto up;\n        object->value = minimum;\n        object->state = 0;\n' if dec_clamp else '        if (object->value <= minimum) {\n            object->value = minimum;\n            object->state = 0;\n        }\n')
        s+='    }\nup:\n'
        s+=('    if (!(object->state & 1)) return;\n    {\n' if inc_guard else '    if (object->state & 1) {\n')
        s+='        float value = object->value;\n        float increment = lbl_806500C4;\n        float maximum = lbl_806500C8;\n        object->value = value + increment;\n'
        s+=('        if (maximum != object->value) return;\n        object->value = maximum;\n' if inc_clamp else '        if (maximum == object->value) {\n            object->value = maximum;\n        }\n')
        s+='    }\n}\n'
        measure('guards_'+''.join(str(int(x)) for x in [dec_guard,dec_clamp,inc_guard,inc_clamp]),s)
finally:
    SOURCE.write_text(BASELINE)
    cmd=['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80120B58.o']
    p=subprocess.run(cmd,capture_output=True,text=True)
    LOG['restore']={'argv':cmd,'exit_code':p.returncode,'stdout':p.stdout,'stderr':p.stderr}
    Path('reports/GEDE01/control-'+ID+'.json').write_text(json.dumps(LOG,indent=2)+'\n')
