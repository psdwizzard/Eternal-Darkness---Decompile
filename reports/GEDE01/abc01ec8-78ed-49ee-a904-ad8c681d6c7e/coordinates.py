from pathlib import Path
exec((Path(__file__).parent/'experiment.py').read_text().split('\nwide=')[0].replace("'experiment-commands.json'","'coordinates-commands.json'"))
import itertools
start=(R/'coordinates-start.c.txt').read_text();(R/'coordinates-start.c.txt').write_text(start)
best=(99.45578,start,'allocation-1010')
variants={}
for yn,y in [('stack','&value.y'),('x','x + 1')]:
 for zn,z in [('stack','&value.z'),('x','x + 2'),('y','y + 1')]:
  variants['coordinates-'+yn+'-'+zn]=start.replace('y = &value.y;', 'y = '+y+';').replace('z = &value.z;', 'z = '+z+';')
for order in itertools.permutations('xyz'):
 variants['init-'+''.join(order)]=start.replace('        x = &value.x;\n        y = &value.y;\n        z = &value.z;', ''.join('        '+v+' = &value.'+v+';\n' for v in order).rstrip())
for name,s in variants.items():
 score=measure(name,s)
 if score>best[0]:best=(score,s,name)
P.write_text(best[1]);(R/'coordinates-best.txt').write_text(str((best[0],best[2]))+'\n')
