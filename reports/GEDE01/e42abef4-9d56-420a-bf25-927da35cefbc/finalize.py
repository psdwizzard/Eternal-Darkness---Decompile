from experiment import *
import collections, shutil, hashlib
assignment='e42abef4-9d56-420a-bf25-927da35cefbc'
parent=report.parent
raw=report/'retained-strict.json'
assert raw.exists()
d=json.loads(raw.read_text())
a=next(s for s in d['left']['symbols'] if s['name']=='fn_801EFA68')
b=next(s for s in d['right']['symbols'] if s['name']=='fn_801EFA68')
assert a['match_percent']==98.51542
assert 'ea24b6af954876ce072562ff39cdb4c81d32be1f  build/GEDE01/main.dol' in (report/'sha1.log').read_text()
shutil.copyfile(raw,parent/('objdiff-'+assignment+'.json'))
shutil.copyfile(report/'retained-canonical.json',parent/('objdiff-'+assignment+'-canonical.json'))
def relative(p): return str(p.relative_to(root.parent))
experiments=[]
for p in sorted(report.glob('*-canonical.json')):
 name=p.name[:-len('-canonical.json')]
 data=json.loads(p.read_text()); s=next(s for s in data['left']['symbols'] if s['name']=='fn_801EFA68')
 invalid=name.startswith('size-')
 experiments.append({'name':name,'canonical_score':s['match_percent'],'strict_score':next(s for s in json.loads((report/(name+'-strict.json')).read_text())['left']['symbols'] if s['name']=='fn_801EFA68')['match_percent'],'valid_reconstruction':not invalid,'note':'Rejected: broad declaration replacement accidentally inserted fields into DisplayConfig; corrected in layout-correct-size variants.' if invalid else '', 'canonical':relative(p),'strict':relative(report/(name+'-strict.json')),'patch_from_accepted_base':relative(report/(name+'.patch')),'commands':relative(report/(name+'-commands.json'))})
differences=[]
for x,y in zip(a['instructions'],b['instructions']):
 if x.get('diff_kind') or y.get('diff_kind'):
  differences.append({'kind':x.get('diff_kind') or y.get('diff_kind'),'retail':x.get('instruction'),'generated':y.get('instruction')})
def relocs(side):
 import re
 obj='build/GEDE01/'+('obj' if side=='left' else 'src')+'/game/game_fn_801EFA68.o'
 cmd=['build/binutils/powerpc-eabi-readelf','-Wr',obj]
 p=subprocess.run(cmd,cwd=root,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
 assert p.returncode==0
 (report/('relocations-'+side+'.json')).write_text(json.dumps({'command':cmd,'cwd':'eternal-darkness-decomp','exit_code':p.returncode,'output':p.stdout},indent=2)+'\n')
 result=[]
 for line in p.stdout.splitlines():
  m=re.match(r'\s*([0-9a-f]+)\s+[0-9a-f]+\s+(R_PPC_\w+)\s+[0-9a-f]+\s+(\S+)\s+([+-])\s+([0-9a-f]+)\s*$',line)
  if m:
   off,typ,name,sign,add=m.groups()
   result.append({'offset':int(off,16),'type':typ,'target':name,'addend':int(add,16)*(-1 if sign=='-' else 1)})
 return result
left=relocs('left');right=relocs('right')
assert len(left)==len(right)
reloc_diff=[{'ordinal':i,'retail':l,'generated':r} for i,(l,r) in enumerate(zip(left,right)) if any(l[k]!=r[k] for k in ['type','target','addend'])]
(report/'relocations.json').write_text(json.dumps({'comparison':'Ordered relocation records from raw readelf -Wr outputs; offsets may shift with inserted instructions; target names, types, and addends compared exactly.','retail':left,'generated':right,'mismatches':reloc_diff},indent=2)+'\n')
summary={'assignment_id':assignment,'target':'fn_801EFA68','best_score':a['match_percent'],'retail_size':a['size'],'generated_size':b['size'],'status':'attempted','accepted_base':'a83620c53978edc11586cc4634ba9c4bfb3775f4','history':'history.json','historical_reconciliation':'128eaa5 changes reports only; its source matches the accepted base. Historical 92.92951% is an inherited assertion, not a reproduced measurement. The historical patch was not committed and is not claimed as recovered. This assignment preserves raw measurements and exact patches for every new experiment.','new_hypothesis':'The extraneous fn_8015DAB0 arguments keep r4 live. Its existing C reconstruction accepts one ResourceTable pointer; remove unused call arguments and unused mode parameter. Retail also truncates aligned width to u16 and computes framebuffer size before pointer stores. These changes match the startup and framebuffer allocation sequences.','additional_tests':'Source-level union assignment orders under unchanged GC/1.3 settings; retain order 0132. No explicit operand-narrowing rerun from attempt 4.','compiler':'GC/1.3; canonical configure.py flags, recorded in compiler-command.log','canonical_equals_strict':(report/'retained-canonical.json').read_bytes()==raw.read_bytes(),'source_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'row_counts':dict(collections.Counter(x['kind'] for x in differences)),'differences':differences,'experiments':experiments,'dol_verification':'NonMatching remains linked from the retail object, so the whole-DOL SHA-1 validates the build but does not establish a C match.','constraints':'Only assigned source and assignment reports changed. No registration or split changes needed. No compiler-policy, gate, runtime, neighboring function, or global-progress edits. No assembly or extra C translation unit retained.'}
(report/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
divergence='Canonical and relocation-strict objdiff both measure 98.51542% (908 retail bytes, 916 generated bytes). The startup and framebuffer allocation sequences now match. Remaining rows: 3 argument mismatches, 2 replacements, 2 generated inserts. Width-conversion stores at retail offsets 0x1E0/0x1EC are reversed; GC/1.3 emits double fsub plus frsp instead of retail fsubs for both viewport dimensions; ratio conversion at retail offset 0x268 targets TU-local @22 instead of lbl_80651350 (both addends zero). Kept one NonMatching C translation unit.'
evidence=[relative(parent/('objdiff-'+assignment+'.json')),relative(parent/('objdiff-'+assignment+'-canonical.json')),relative(report/'summary.json'),relative(report/'relocations.json'),relative(report/'verification-commands.json'),relative(report/'configure.log'),relative(report/'build.log'),relative(report/'sha1.log'),relative(report/'legal-audit.json')]
(parent/('durable-'+assignment+'.json')).write_text(json.dumps({'version':1,'assignment_id':assignment,'attempt':5,'base_commit':'a83620c53978edc11586cc4634ba9c4bfb3775f4','target':'fn_801EFA68','status':'attempted','evidence':evidence,'divergence':divergence},indent=2)+'\n')
print(json.dumps({'best_score':a['match_percent'],'row_counts':summary['row_counts'],'relocation_mismatches':reloc_diff},indent=2))
