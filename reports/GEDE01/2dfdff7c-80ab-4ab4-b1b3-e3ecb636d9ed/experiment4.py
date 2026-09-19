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
variants={}
for decl in itertools.permutations('cba'):
 for assign in itertools.permutations('cba'):
  for loc in ['before','after']:
   src=branch.replace('                u32 output[3];\n','')
   declaration=''.join('            u32 out_'+x+';\n' for x in decl)
   if loc=='before':src=src.replace('            struct {',declaration+'            struct {')
   else:src=src.replace('            } local;','            } local;\n'+declaration)
   old='''            local.output[0] = local.c;
            local.output[1] = local.b;
            local.output[2] = local.a;'''
   src=src.replace(old,''.join('            out_'+x+' = local.'+x+';\n' for x in assign).rstrip())
   for i,x in enumerate('cba'):src=src.replace('local.output['+str(i)+']','out_'+x)
   variants['split-'+''.join(decl)+'-'+''.join(assign)+'-'+loc]=src
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
 (R/'experiments4.json').write_text(json.dumps(results,indent=2)+'\n')
