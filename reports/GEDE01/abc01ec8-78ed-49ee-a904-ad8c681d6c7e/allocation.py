from pathlib import Path
exec((Path(__file__).parent/'experiment.py').read_text().split('\nwide=')[0].replace("'experiment-commands.json'","'allocation-commands.json'"))
import re,itertools
start=(R/'lifetimes-start.c.txt').read_text()
best=(99.11565,start,'short-order-mieb')
for shared_index in [False,True]:
 for separate_mask in [False,True]:
  for top_pointers in [False,True]:
   for top_context in [False,True]:
    s=start
    a,rest=s.split('    if (update == 0) {')
    if shared_index:
     a=a.replace('    Value value;','    int j;\n    Value value;')
     rest=re.sub(r'\bi\b','j',rest)
    if separate_mask:
     a=a.replace('    Value value;','    u16 other_bit;\n    Value value;')
     rest=re.sub(r'\bbit\b','other_bit',rest)
    s=a+'    if (update == 0) {'+rest
    if top_pointers:
     s=s.replace('    Value value;', '    float *x, *y, *z;\n    Value value;').replace('        float* x =', '        x =').replace('        float* y =','        y =').replace('        float* z =','        z =')
    if top_context:
     s=s.replace('    Value value;', '    void* context;\n    Value value;').replace('        void* context = fn_80201BC8(right_set);\n','').replace('        entry = set;\n        bit = 1;\n        for', '        entry = set;\n        bit = 1;\n        for')
     pos=s.index('    {\n',s.index('    if (update == 0)'))
     s=s[:pos]+s[pos:].replace('        entry = set;', '        context = fn_80201BC8(right_set);\n        entry = set;',1)
    n='allocation-'+''.join(str(int(x)) for x in [shared_index,separate_mask,top_pointers,top_context])
    score=measure(n,s)
    if score>best[0]: best=(score,s,n)
P.write_text(best[1])
(R/'allocation-best.txt').write_text(str((best[0],best[2]))+'\n')
