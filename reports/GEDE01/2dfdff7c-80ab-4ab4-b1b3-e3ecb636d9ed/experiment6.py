import pathlib,subprocess,json,itertools,difflib
R=pathlib.Path('reports/GEDE01/2dfdff7c-80ab-4ab4-b1b3-e3ecb636d9ed');S=pathlib.Path('src/game/game_fn_80205914.c');base=json.loads((R/'baseline-source.json').read_text())['source']
branch=base.replace('''        return 0;
    }
    return 0;
}''','''    } else {
        return 0;
    }
    return 0;
}''')
old='''            local.output[0] = local.c;
            local.output[1] = local.b;
            local.output[2] = local.a;'''
variants={}
for mask in range(1,8):
 for mode in ['direct','temps']:
  src=branch.replace('u32 output[3];', 'struct { '+''.join(('volatile ' if mask&(1<<i) else '')+'u32 '+x+'; ' for i,x in enumerate('cba'))+'} output;')
  if mode=='temps':src=src.replace(old, """            {
                u32 c = local.c;
                u32 b = local.b;
                u32 a = local.a;
                local.output[1] = b;
                local.output[0] = c;
                local.output[2] = a;
            }""")
  for i,x in enumerate('cba'):
   src=src.replace('&local.output['+str(i)+']','(u32 *)&local.output.'+x).replace('local.output['+str(i)+']','local.output.'+x)
  variants['volatile-output-'+str(mask)+'-'+mode]=src
for kind in ['int','float','register']:
 src=branch.replace(old,"""            {
                u32 c = local.c;
                u32 b = local.b;
                u32 a = local.a;
                local.output[1] = b;
                local.output[0] = c;
                local.output[2] = a;
            }""")
 if kind=='register':
  for x in 'cba':src=src.replace('u32 '+x+' = local.', 'register u32 '+x+' = local.')
 elif kind=='int':src=src.replace('typedef unsigned int u32;', 'typedef int u32;')
 else:
  src=src.replace('u32 output[3];','float output[3];')
  for i,x in enumerate('cba'):
   src=src.replace('local.output['+str(i)+'] = '+x+';', '*(u32 *)&local.output['+str(i)+'] = '+x+';').replace('&local.output['+str(i)+']', '(u32 *)&local.output['+str(i)+']')
 variants['value-type-'+kind]=src
results=[]
try:
 for name,src in variants.items():
  S.write_text(src)
  b=subprocess.run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80205914.o'],stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True);(R/(name+'.log')).write_text(b.stdout)
  if b.returncode:raise RuntimeError(b.stdout)
  subprocess.run(['build/tools/objdiff-cli','diff','-1','build/GEDE01/obj/game/game_fn_80205914.o','-2','build/GEDE01/src/game/game_fn_80205914.o','-o',str(R/(name+'.json')),'--format','json','-c','function_reloc_diffs=name_address','fn_80205914'],check=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
  d=json.loads((R/(name+'.json')).read_text());s=next(s for s in d['left']['symbols'] if s.get('name')=='fn_80205914')
  results.append({'trial':name,'score':s['match_percent'],'patch':''.join(difflib.unified_diff(base.splitlines(True),src.splitlines(True),fromfile='baseline',tofile=name))})
  print(name,s['match_percent'],flush=True)
  if s['match_percent']==100:break
finally:
 S.write_text(base)
 (R/'experiments6.json').write_text(json.dumps(results,indent=2)+'\n')
