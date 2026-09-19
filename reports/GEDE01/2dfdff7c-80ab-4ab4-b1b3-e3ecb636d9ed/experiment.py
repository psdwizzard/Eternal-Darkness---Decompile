import pathlib,subprocess,json,itertools,difflib
R=pathlib.Path('reports/GEDE01/2dfdff7c-80ab-4ab4-b1b3-e3ecb636d9ed')
S=pathlib.Path('src/game/game_fn_80205914.c')
base=S.read_text()
(R/'baseline-source.json').write_text(json.dumps({'source':base},indent=2)+'\n')
results=[]
old='''            local.output[0] = local.c;
            local.output[1] = local.b;
            local.output[2] = local.a;'''
variants={}
for order in itertools.permutations(range(3)):
 if order==(0,1,2):continue
 lines=old.splitlines();variants['store-order-'+''.join(map(str,order))]=base.replace(old,'\n'.join(lines[i] for i in order))
variants['output-struct']=base.replace('u32 output[3];','struct { u32 c, b, a; } output;').replace('output[0]','output.c').replace('output[1]','output.b').replace('output[2]','output.a')
variants['temporary-aggregate']=base.replace(old,'''            {
                struct { u32 c, b, a; } result;
                result.c = local.c;
                result.b = local.b;
                result.a = local.a;
                local.output[0] = result.c;
                local.output[1] = result.b;
                local.output[2] = result.a;
            }''')
variants['scalar-temporaries']=base.replace(old,'''            {
                u32 a = local.a;
                u32 b = local.b;
                u32 c = local.c;
                local.output[0] = c;
                local.output[1] = b;
                local.output[2] = a;
            }''')
try:
 for name,src in variants.items():
  S.write_text(src)
  build=subprocess.run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80205914.o'],stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
  (R/(name+'.log')).write_text(build.stdout)
  if build.returncode:raise RuntimeError(build.stdout)
  subprocess.run(['build/tools/objdiff-cli','diff','-1','build/GEDE01/obj/game/game_fn_80205914.o','-2','build/GEDE01/src/game/game_fn_80205914.o','-o',str(R/(name+'.json')),'--format','json','-c','function_reloc_diffs=name_address','fn_80205914'],check=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
  d=json.loads((R/(name+'.json')).read_text());s=next(s for s in d['left']['symbols'] if s.get('name')=='fn_80205914')
  row={'trial':name,'score':s['match_percent'],'patch':''.join(difflib.unified_diff(base.splitlines(True),src.splitlines(True),fromfile='baseline',tofile=name))};results.append(row)
  print(name,s['match_percent'],flush=True)
finally:
 S.write_text(base)
 (R/'experiments.json').write_text(json.dumps(results,indent=2)+'\n')
