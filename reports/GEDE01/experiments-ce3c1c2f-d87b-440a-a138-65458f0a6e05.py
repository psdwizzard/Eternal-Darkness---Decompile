"""Assignment-local codegen experiments; canonical flags; restore best source."""
import json, subprocess, pathlib, hashlib, sys, itertools
root=pathlib.Path(__file__).resolve().parents[2]
source=root/'src/game/game_fn_801807B0.c'
aid='ce3c1c2f-d87b-440a-a138-65458f0a6e05'
reports=root/'reports/GEDE01'
baseline=subprocess.check_output(['git','show','HEAD:eternal-darkness-decomp/src/game/game_fn_801807B0.c'],cwd=root,text=True)
command=subprocess.check_output(['.tools/bin/ninja','-t','commands','build/GEDE01/src/game/game_fn_801807B0.o'],cwd=root,text=True).splitlines()[-1]
variants=[('baseline', baseline)]
# Change declaration scope without moving any observable call or computation.
for subset in [('second','third','fourth'),('first','second','third','fourth')]:
 for nested in (False,True):
  s=baseline
  for name in subset: s=s.replace('    u32 '+name+'_stride;\n','')
  if nested:
   for name in subset:
    s=s.replace('    '+name+'_stride =','    {\n    u32 '+name+'_stride;\n    '+name+'_stride =')
   s=s.rstrip()+'\n'+'}\n'*len(subset)
  else:
   marker='    fn_8017FFA8();'
   s=s.replace(marker,'    {\n'+''.join('    u32 '+n+'_stride;\n' for n in subset)+marker)
   s=s.rstrip()+'\n}\n'
  variants.append(('scope_'+('_'.join(subset))+'_'+str(nested),s))
for name in ['second_stride','third_stride','fourth_stride','first_stride']:
 s=baseline.replace('    u32 '+name+';\n','')
 s=s.replace('    fn_8017FFA8();','    {\n    u32 '+name+';\n    fn_8017FFA8();').rstrip()+'\n}\n'
 variants.append(('scope_only_'+name,s))
for qualifier in ['register','const']:
 s=baseline
 for n,f in [('first','8017FFA0'),('second','8017FFB8'),('third','8017FF98'),('fourth','8017FFB0')]:
  s=s.replace('    u32 '+n+'_stride;\n','')
  s=s.replace('    '+n+'_stride = fn_'+f+'();','    '+qualifier+' u32 '+n+'_stride = fn_'+f+'();')
 variants.append((qualifier+'_initialized_strides',s))
# Separate scalar fields in a local aggregate test scalar-replacement allocation.
s=baseline
for n in ['first','second','third','fourth']:
 s=s.replace('    u32 '+n+'_stride;\n','')
 s=s.replace(n+'_stride','strides.'+n)
s=s.replace('    u32 first_size;','    struct { u32 first, second, third, fourth; } strides;\n    u32 first_size;')
variants.append(('aggregate_strides',s))
# Signedness and true ABI-width candidates (no manual register binding).
for mask in range(1,8):
 s=baseline
 for bit,name in enumerate(['count','width','scale']):
  if mask&(1<<bit): s=s.replace('u32 '+name+(')' if name=='scale' else ','),('u8 ' if name=='scale' else 'u16 ')+name+(')' if name=='scale' else ','))
 variants.append(('narrow_parameters_'+str(mask),s))
for what in ['strides','sizes','both','getters','all']:
 s=baseline
 for name in ['first','second','third','fourth']:
  if what in ('strides','both','all'): s=s.replace('u32 '+name+'_stride;', 'int '+name+'_stride;')
  if what in ('sizes','both','all'): s=s.replace('u32 '+name+'_size;', 'int '+name+'_size;')
 if what in ('getters','all'): s=s.replace('extern u32 fn_', 'extern int fn_')
 variants.append(('signed_'+what,s))
for what in ['strides','sizes','both','all']:
 s=baseline
 for name in ['first','second','third','fourth']:
  if what in ('strides','both','all'): s=s.replace('    u32 '+name+'_stride;', '    register u32 '+name+'_stride;')
  if what in ('sizes','both','all'): s=s.replace('    u32 '+name+'_size;', '    register u32 '+name+'_size;')
 if what=='all': s=s.replace('    void* ', '    register void* ')
 variants.append(('register_'+what,s))
for qual in ['', 'const ', 'register ']:
 s=baseline
 for n in ['first','second','third','fourth']:
  s=s.replace('    u32 '+n+'_stride;\n','')
  s=s.replace('    '+n+'_stride =', '    {\n    '+qual+'u32 '+n+'_stride =')
 s=s.rstrip()+'\n}\n'*4
 variants.append(('nested_initialized_'+qual.strip(),s))
for mask in range(1,16):
 s=baseline
 for i,n in enumerate(['first','second','third','fourth']):
  if mask&(1<<i): s=s.replace('(u16)count * '+n+'_size',n+'_size * (u16)count')
 variants.append(('allocation_operand_order_'+str(mask),s))
# Hoist pure size expressions across allocation calls, preserving call order.
names=['first','second','third','fourth']
size_lines={n:'        '+n+'_size = '+n+'_stride * '+('(u16)width' if n=='first' else 'doubled_width')+';\n' for n in names}
for positions in itertools.product(range(1),range(2),range(3),range(4)):
 if positions==(0,1,2,3): continue
 s=baseline
 for line in size_lines.values(): s=s.replace(line,'')
 for i,n in enumerate(names):
  marker='        '+n+' = fn_801FEA8C'
  s=s.replace(marker,''.join(size_lines[names[j]] for j in range(4) if positions[j]==i)+marker)
 variants.append(('size_hoist_'+''.join(map(str,positions)),s))
for order in itertools.permutations(names):
 s=baseline
 for line in size_lines.values():s=s.replace(line,'')
 s=s.replace('        first = fn_801FEA8C',''.join(size_lines[n] for n in order)+'        first = fn_801FEA8C')
 variants.append(('all_sizes_order_'+'_'.join(order),s))
# Coalescing can distinguish recomputation of size expressions from named sizes.
for mask in range(1,16):
 s=baseline
 for i,n in enumerate(names):
  if mask&(1<<i):
   expr=n+'_stride * '+('(u16)width' if n=='first' else 'doubled_width')
   s=s.replace(n+', '+n+'_size, count',n+', '+expr+', count')
 variants.append(('recompute_sizes_'+str(mask),s))
# Reverse the operand traversal for the stride expressions.
for mask in range(1,16):
 s=baseline
 for i,n in enumerate(names):
  if mask&(1<<i):
   term='(u16)width' if n=='first' else 'doubled_width'
   s=s.replace(n+'_stride * '+term,term+' * '+n+'_stride')
 variants.append(('stride_operand_order_'+str(mask),s))
# Test virtual-register creation order independently of expression evaluation.
for order in itertools.permutations(['first','second','third','fourth']):
 for kinds in [('stride',), ('size',), ('stride','size')]:
  t=baseline
  for kind in kinds:
   for n in names: t=t.replace('    u32 '+n+'_'+kind+';\n','')
  decl=''.join('    u32 '+n+'_'+kind+';\n' for kind in kinds for n in order)
  t=t.replace('    fn_8017FFA8();',decl+'    fn_8017FFA8();')
  variants.append(('declaration_order_'+'_'.join(kinds)+'_'+'_'.join(order),t))
for pos in ['first_stride','first_size','first','calls']:
 for ty in ['u16','u32']:
  t=baseline.replace('        u16 doubled_width =','        doubled_width =')
  marker={'first_stride':'    u32 first_stride;','first_size':'    u32 first_size;','first':'    void* first;','calls':'    fn_8017FFA8();'}[pos]
  t=t.replace(marker,'    '+ty+' doubled_width;\n'+marker)
  if ty=='u32':t=t.replace('doubled_width >> 1','(u16)doubled_width >> 1')
  variants.append(('width_declaration_'+pos+'_'+ty,t))
# Count cast as a scoped allocation-only value, rather than the previous early local.
for ty in ['u16','u32','int']:
 for pos in ['before_width','after_width','before_first']:
  t=baseline.replace('(u16)count *','allocation_count *')
  line='        '+ty+' allocation_count = (u16)count;\n'
  if pos=='before_width': t=t.replace('        u16 doubled_width =',line+'        u16 doubled_width =')
  elif pos=='after_width':t=t.replace('        first_size =',line+'        first_size =')
  else:
   t=t.replace('        first = fn_', '        {\n'+line+'        first = fn_')
   t=t.replace('        group->first =','        }\n        group->first =')
  variants.append(('allocation_scope_count_'+ty+'_'+pos,t))
# Keep the getter's value through a size variable, splitting its later SSA lifetime.
getters=dict(zip(names,['8017FFA0','8017FFB8','8017FF98','8017FFB0']))
for mask in range(1,16):
 t=baseline
 for i,n in enumerate(names):
  if mask&(1<<i):
   t=t.replace(n+'_stride = fn_'+getters[n]+'();',n+'_size = fn_'+getters[n]+'();\n    '+n+'_stride = '+n+'_size;')
   t=t.replace(n+'_size = '+n+'_stride *',n+'_size = '+n+'_size *')
 variants.append(('size_value_split_'+str(mask),t))
# SSA reuse of each stride while preserving the original unit for the metadata.
for mask in range(1,8):
 t=baseline
 for i,n in enumerate(names[1:]):
  if mask&(1<<i):
   t=t.replace('    u32 '+n+'_size;', '    u32 '+n+'_size;\n    u32 '+n+'_unit;')
   t=t.replace('        '+n+'_size = '+n+'_stride * doubled_width;', '        '+n+'_unit = '+n+'_stride;\n        '+n+'_stride *= doubled_width;\n        '+n+'_size = '+n+'_stride;')
   t=t.replace(n+'_stride * half_width',n+'_unit * half_width')
 variants.append(('stride_value_split_'+str(mask),t))
# Explicit dimension-value locals change late interference, without volatile or asm.
for ty in ['u16','u32','int']:
 for scope in ['root','final']:
  for order in itertools.permutations(names[1:]):
   t=baseline
   decl=''.join('            '+ty+' '+n+'_dimension;\n' for n in order)
   if scope=='root':t=t.replace('    u32 first_stride;',decl+'    u32 first_stride;')
   else:t=t.replace('            u16 half_width =',decl+'            u16 half_width =')
   t=t.replace('            group->dimensions[3]', ''.join('            '+n+'_dimension = '+n+'_stride * half_width;\n' for n in order)+'            group->dimensions[3]')
   for i,n in enumerate(names[1:]):t=t.replace('group->dimensions['+str(i+5)+'] = '+n+'_stride * half_width;', 'group->dimensions['+str(i+5)+'] = '+n+'_dimension;')
   variants.append(('dimension_locals_'+ty+'_'+scope+'_'+'_'.join(order),t))
result_path=reports/('experiments-'+aid+'.json')
results=json.loads(result_path.read_text())['results'] if result_path.exists() and '--fresh' not in sys.argv else []
completed={r['name'] for r in results}
best=source.read_text()
bestscore=max([r.get('score',0) for r in results] or [0])
try:
 for name,s in variants:
  if name in completed: continue
  source.write_text(s)
  p=subprocess.run(command,cwd=root,shell=True,text=True,capture_output=True)
  row={'name':name,'source_sha256':hashlib.sha256(s.encode()).hexdigest(),'build_exit':p.returncode,'build_output':p.stdout+p.stderr}
  if not p.returncode:
   d=subprocess.run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_801807B0','fn_801807B0','-o','-','--format','json'],cwd=root,text=True,capture_output=True)
   raw=json.loads(d.stdout)
   l=next(x for x in raw['left']['symbols'] if x['name']=='fn_801807B0')
   r=next(x for x in raw['right']['symbols'] if x['name']=='fn_801807B0')
   row.update(score=l['match_percent'],size=r['size'],instructions=[x.get('instruction',{}).get('formatted','<gap>') for x in r['instructions']],diff_output=d.stderr)
   if row['score']>bestscore: bestscore=row['score']; best=s
  results.append(row)
  print(name,row.get('score'),row.get('size'),flush=True)
  (reports/('experiments-'+aid+'.json')).write_text(json.dumps({'compiler_command':command,'results':results},indent=2)+'\n')
  if bestscore==100: break
finally:
 source.write_text(best)
 subprocess.run(command,cwd=root,shell=True,check=True)
