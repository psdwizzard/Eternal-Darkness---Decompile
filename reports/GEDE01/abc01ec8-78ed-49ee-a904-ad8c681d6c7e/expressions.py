from pathlib import Path
exec((Path(__file__).parent/'experiment.py').read_text().split('\nwide=')[0].replace("'experiment-commands.json'","'expressions-commands.json'"))
start=(R/'expressions-start.c.txt').read_text();(R/'expressions-start.c.txt').write_text(start)
best=(99.45578,start,'allocation-1010')
variants={}
for direct in range(1,8):
 s=start.replace('    float *x, *y, *z;','    float *x;\n    float *y;\n    float *z;')
 for i,v in enumerate('xyz'):
  if direct&(1<<i):
   s=s.replace('    float *'+v+';\n','').replace('        '+v+' = &value.'+v+';\n','').replace('fn_8014B604('+v+',','fn_8014B604(&value.'+v+',')
 variants['direct-'+str(direct)]=s
variants['condition-normalized']=start.replace('            bit = (u16)bit;\n','').replace('set->active & bit','set->active & (bit = (u16)bit)')
variants['normalized-u32-best']=start.replace('u16 bit;', 'u32 bit;')
variants['normalized-int-best']=start.replace('u16 bit;', 'int bit;')
variants['increment-unmasked']=start.replace('bit = (u16)(bit << 1);','bit <<= 1;')
variants['increment-for']=start.replace('for (i = 0; i < count; i++) {','for (i = 0; i < count; i++, bit = (u16)(bit << 1)) {').replace('for (j = 0; j < count; j++) {','for (j = 0; j < count; j++, bit = (u16)(bit << 1)) {').replace('        bit = (u16)(bit << 1);\n','').replace('            bit = (u16)(bit << 1);\n','')
variants['cleanup-else']=start.replace('        return;\n    }\n\n    {', '    } else {')
variants['cleanup-else-short-index']=variants['cleanup-else'].replace('    int j;\n','').replace('for (j = 0; j < count; j++)','for (i = 0; i < count; i++)')
variants['reuse-update-index']=start.replace('    int j;\n','').replace('for (j = 0; j < count; j++)','for (update = 0; update < count; update++)')
variants['reuse-mode-index']=start.replace('    int j;\n','').replace('for (j = 0; j < count; j++)','for (mode = 0; mode < count; mode++)')
for name,s in variants.items():
 score=measure(name,s)
 if score>best[0]:best=(score,s,name)
P.write_text(best[1]);(R/'expressions-best.txt').write_text(str((best[0],best[2]))+'\n')
