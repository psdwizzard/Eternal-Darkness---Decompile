from pathlib import Path
exec((Path(__file__).parent/'experiment.py').read_text().split('\nwide=')[0].replace("'experiment-commands.json'","'lifetimes-commands.json'"))
import re,itertools
start=(R/'lifetimes-start.c.txt').read_text()
(R/'lifetimes-start.c.txt').write_text(start)
a,rest=start.split('    if (update == 0) {')
b,c=rest.split('    {\n        void* context')
for typ in ['int','u16']:
    for split_bit in [False,True]:
        b2=re.sub(r'\bi\b','j',b)
        c2=re.sub(r'\bi\b','k',c)
        b2='\n        '+typ+' j;'+b2
        c2=c2.replace(' = fn_80201BC8(right_set);',' = fn_80201BC8(right_set);\n        '+typ+' k;')
        if split_bit:
            b2='\n        u16 mask2;'+re.sub(r'\bbit\b','mask2',b2)
            c2=c2.replace('        '+typ+' k;', '        '+typ+' k;\n        u16 mask3;')
            c2=re.sub(r'\bbit\b','mask3',c2)
        s=a+'    if (update == 0) {'+b2+'    {\n        void* context'+c2
        measure('scoped-'+typ+'-'+str(split_bit),s)
P.write_text(start)
