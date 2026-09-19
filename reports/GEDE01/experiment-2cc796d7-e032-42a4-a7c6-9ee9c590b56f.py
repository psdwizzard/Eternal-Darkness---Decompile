import json, pathlib, subprocess, sys
A='2cc796d7-e032-42a4-a7c6-9ee9c590b56f'
r=pathlib.Path('reports/GEDE01')
p=r/f'objdiff-{A}.json'
d=json.loads(p.read_text())
s=d['baseline_source']; label=sys.argv[1]
helper='''static inline float add_component(float base, float component)
{
    return base + component;
}

'''
if label == 'inline-return':
    s=s.replace('/*\n * NonMatching',helper+'/*\n * NonMatching').replace('lbl_8064D6C8 + value->y','add_component(lbl_8064D6C8, value->y)').replace('lbl_8064D6CC + value->z','add_component(lbl_8064D6CC, value->z)')
elif label == 'inline-wrap':
    helper='''static inline void add_wrap(float* base, float component)
{
    float angle = *base + component;
    float limit = lbl_8065135C;
    *base = angle;
    if (angle > limit) {
        *base = angle - limit;
    }
}

'''
    s=s.replace('/*\n * NonMatching',helper+'/*\n * NonMatching')
    start=s.index('            angle = lbl_8064D6C8')
    s=s[:start]+'''            add_wrap(&lbl_8064D6C8, value->y);
            add_wrap(&lbl_8064D6CC, value->z);
'''+s[s.index('        }\n    }\n}',start):]
elif label == 'double-limit':
    s=s.replace('    float limit;','    double limit;')
elif label != 'baseline':
    raise ValueError(label)
pathlib.Path('src/game/game_fn_801F02C4.c').write_text(s)
e={'label':label,'source':s,'commands':[]}
def run(cmd):
    x=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    e['commands'].append({'argv':cmd,'exit_code':x.returncode,'raw_stdout':x.stdout})
    print(x.stdout)
    if x.returncode: raise RuntimeError(cmd)
run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_801F02C4.o'])
for mode in ['canonical','strict']:
    out=r/f'objdiff-{A}-{label}-{mode}.raw.json'
    cmd=['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_801F02C4','-o',str(out),'--format','json-pretty']
    if mode=='strict': cmd+=['-c','function_reloc_diffs=name_address']
    cmd+=['fn_801F02C4']
    run(cmd)
    raw=json.loads(out.read_text())
    l=next(x for x in raw['left']['symbols'] if x['name']=='fn_801F02C4'); rr=next(x for x in raw['right']['symbols'] if x['name']=='fn_801F02C4')
    e[mode]={'configuration':'function_reloc_diffs=name_address' if mode=='strict' else 'default canonical','raw_report':'eternal-darkness-decomp/'+str(out),'match_percent':l['match_percent'],'retail_text_bytes':l['size'],'generated_text_bytes':rr['size']}
    print(label,mode,e[mode])
d['experiments'].append(e); p.write_text(json.dumps(d,indent=2)+'\n')
