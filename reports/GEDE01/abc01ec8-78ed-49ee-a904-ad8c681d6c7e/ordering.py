from pathlib import Path
exec((Path(__file__).parent/'experiment.py').read_text().split('\nwide=')[0].replace("'experiment-commands.json'","'ordering-commands.json'"))
import itertools
start=(R/'ordering-start.c.txt').read_text()
(R/'ordering-start.c.txt').write_text(start)
best=(99.45578,start,'allocation-1010')
for order in itertools.permutations('bjxyz'):
 s=start.replace('    u16 bit;\n','').replace('    int j;\n','').replace('    float *x, *y, *z;\n','')
 decl={'b':'u16 bit;','j':'int j;','x':'float* x;','y':'float* y;','z':'float* z;'}
 s=s.replace('    Set* right_set;', ''.join('    '+decl[v]+'\n' for v in order)+'    Set* right_set;')
 name='ordering-'+''.join(order)
 score=measure(name,s)
 if score>best[0]: best=(score,s,name)
 if score==100: break
P.write_text(best[1])
(R/'ordering-best.txt').write_text(str((best[0],best[2]))+'\n')
