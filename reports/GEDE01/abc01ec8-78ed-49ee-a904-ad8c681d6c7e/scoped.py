from pathlib import Path
exec((Path(__file__).parent/'experiment.py').read_text().split('\nwide=')[0].replace("'experiment-commands.json'","'scoped-commands.json'"))
import re,itertools
start=(R/'scoped-start.c.txt').read_text();(R/'scoped-start.c.txt').write_text(start)
best=(99.45578,start,'allocation-1010')
a,rest=start.split('    if (update == 0) {'); b,c=rest.split('    {\n        void* context')
for mask2,mask3,local_index,pointer_local in itertools.product([False,True],repeat=4):
 aa=a;bb=b;cc='        void* context'+c
 if mask2:
  bb='\n        u16 bit2;'+re.sub(r'\bbit\b','bit2',bb)
 if mask3:
  cc='        u16 bit3;\n'+re.sub(r'\bbit\b','bit3',cc)
 if local_index:
  bb='\n        int j;'+bb
  cc='        int j;\n'+cc
 if pointer_local:
  aa=aa.replace('    float *x, *y, *z;\n','')
  cc='        float *x, *y, *z;\n'+cc
 s=aa+'    if (update == 0) {'+bb+'    {\n'+cc
 name='scope-'+''.join(str(int(x)) for x in [mask2,mask3,local_index,pointer_local])
 score=measure(name,s)
 if score>best[0]:best=(score,s,name)
P.write_text(best[1]);(R/'scoped-best.txt').write_text(str((best[0],best[2]))+'\n')
