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
            local.output[2] = local.a;
            fn_8012C774(target, &local.output[2], &local.output[1], &local.output[0], 4);'''
variants={}
for order in itertools.permutations('oabc'):
 decls={'o':'void *call_object = target;','a':'u32 *pa = &local.output[2];','b':'u32 *pb = &local.output[1];','c':'u32 *pc = &local.output[0];'}
 decl='\n'.join('                '+decls[k] for k in order)
 for mode in ['direct','temps']:
  assign=old[:old.index('            fn_8012C774')]
  if mode=='temps':assign='''                u32 c = local.c;
                u32 b = local.b;
                u32 a = local.a;
                local.output[1] = b;
                local.output[0] = c;
                local.output[2] = a;
'''
  variants['pointers-'+''.join(order)+'-'+mode]=branch.replace(old,'            {\n'+decl+'\n'+assign+'                fn_8012C774(call_object, pa, pb, pc, 4);\n            }')
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
 (R/'experiments3.json').write_text(json.dumps(results,indent=2)+'\n')
