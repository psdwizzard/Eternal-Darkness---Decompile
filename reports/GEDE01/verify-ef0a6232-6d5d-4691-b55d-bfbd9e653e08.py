"""Summarize raw objdiff and ELF relocation measurements without disassembly."""
import collections, hashlib, json, pathlib, struct, subprocess
A='ef0a6232-6d5d-4691-b55d-bfbd9e653e08'
P=pathlib.Path('build/GEDE01/attempt-ef0a6232')

def elf(path):
 b=pathlib.Path(path).read_bytes()
 assert b[:6]==b'\x7fELF\x01\x02'
 h=struct.unpack_from('>16sHHIIIIIHHHHHH',b)
 sh=[struct.unpack_from('>IIIIIIIIII',b,h[6]+i*h[11]) for i in range(h[12])]
 def content(s): return b[s[4]:s[4]+s[5]]
 def string(t,o): return t[o:t.index(b'\0',o)].decode()
 names=content(sh[h[13]])
 sections={string(names,s[0]):(i,s) for i,s in enumerate(sh)}
 def symbols(i):
  s=sh[i];t=content(sh[s[6]]);data=content(s)
  return [string(t,struct.unpack_from('>I',data,o)[0]) for o in range(0,s[5],s[9])]
 sym=symbols(sections['.symtab'][0])
 texti,texts=sections['.text']
 rel=[]
 for s in sh:
  if s[1]!=4 or s[7]!=texti:continue
  sy=symbols(s[6]);data=content(s)
  for off in range(0,len(data),s[9]):
   addr,info,addend=struct.unpack_from('>IIi',data,off)
   rel.append({'offset':addr,'type':info&255,'target':sy[info>>8],'addend':addend})
 return {'text':content(texts),'relocations':rel,'symbols':sym,'sha256':hashlib.sha256(b).hexdigest()}

paths=['build/GEDE01/obj/game/game_fn_8008DD78.o','build/GEDE01/src/game/game_fn_8008DD78.o']
e=[elf(p) for p in paths]
report={'assignment_id':A,'target':'fn_8008DD78','tool':'objdiff-cli v3.6.1','objdiff':{}}
for mode in ['canonical','strict']:
 raw=P/(mode+'.json')
 cmd=['build/tools/objdiff-cli','diff','-1',paths[0],'-2',paths[1],'fn_8008DD78','-o',str(raw),'--format','json']
 if mode=='strict':cmd+=['-c','function_reloc_diffs=name_address']
 p=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,check=True)
 d=json.loads(raw.read_text())
 # Verbatim summary fields from the raw JSON; disassembly stays ignored/local.
 summary={side:{'sections':d[side]['sections'],'symbols':[{k:v for k,v in s.items() if k!='instructions'} for s in d[side]['symbols']]} for side in ['left','right']}
 report['objdiff'][mode]={'command':cmd,'exit_code':p.returncode,'raw_stdout_stderr':p.stdout,'raw_summary_fields':summary}
 if mode=='strict':strict=d
left,right=[strict[side]['symbols'][0]['instructions'] for side in ['left','right']]
# objdiff symbol IDs are its own filtered IDs, not ELF symbol indices.
# Resolve their names through real relocations at the instruction offsets.
reloc_names=[]
for side,insns in enumerate([left,right]):
 by_insn={r['offset']//4*4:r for r in e[side]['relocations']}
 names={}
 for entry in insns:
  ins=entry.get('instruction',{});r=ins.get('relocation');off=int(ins.get('address','0'))
  if r and off in by_insn:
   name=by_insn[off]['target'];idx=r['target_symbol']
   assert idx not in names or names[idx]==name
   names[idx]=name
 reloc_names.append(names)
rows=[];reloc_rows=[]
for a,b in zip(left,right):
 ai=a.get('instruction',{});bi=b.get('instruction',{})
 if a.get('diff_kind') or b.get('diff_kind'):
  regs=lambda ins:[p['arg']['opaque'] for p in ins.get('parts',[]) if 'opaque' in p.get('arg',{})]
  rows.append({'offset':ai.get('address','0'),'kind':a.get('diff_kind',b.get('diff_kind')),'retail_register_operands':regs(ai),'candidate_register_operands':regs(bi)})
 if 'relocation' in ai or 'relocation' in bi:
  def relocation(ins,side):
   r=ins.get('relocation')
   if r is None:return None
   return {'type':r.get('type',0),'target':reloc_names[side][r['target_symbol']],'addend':r.get('addend','0')}
  l,r=relocation(ai,0),relocation(bi,1)
  reloc_rows.append({'offset':ai.get('address','0'),'retail':l,'candidate':r,'equal':l==r and ai.get('address','0')==bi.get('address','0')})
report['measurement']={'retail_bytes':len(e[0]['text']),'candidate_bytes':len(e[1]['text']),'retail_instructions':len(left),'candidate_instructions':len(right),'text_bytes_equal':e[0]['text']==e[1]['text'],'differing_instructions':len(rows),'difference_kinds':dict(collections.Counter(x['kind'] for x in rows)),'register_differences':rows,'elf_relocations_equal':e[0]['relocations']==e[1]['relocations'],'elf_relocations':e[0]['relocations'],'objdiff_relocation_sites':reloc_rows,'source_sha256':hashlib.sha256(pathlib.Path('src/game/game_fn_8008DD78.c').read_bytes()).hexdigest()}
report['resolution']={
 'prior_score':98.61789,
 'hypotheses_tested':['callback-loop spelling and induction lowering','register storage hints and explicit callback pointer','declaration-order tie breaking without changing local scope','separate incoming resource and model-result locals, then refine declaration order'],
 'successful_change':'Separate model from the incoming resource parameter, then order locals as data, value, created, owner, target_id, callback, target, model, actor. No call order, branch, type width, compiler setting, or ABI change.',
 'preserved_commits_reviewed':['027249e3092832dfca848f890910dba4b3fb8644','1facb5e4083def39c8e1e290245095a8b4503769','9a058a0efd8125cd1f6079638db42f24cda80b38','5c33f28fb03e08e1947c130190572fb00f8dde5f','e084c7fe986b3d78528f806eba3767aea1e152c6'],
 'scripts':['eternal-darkness-decomp/reports/GEDE01/experiment-'+A+'.py','eternal-darkness-decomp/reports/GEDE01/verify-'+A+'.py'],
 'notes':'The final source comment was updated after reaching 100%; the final source hash differs from the winning experiment only for this explanatory comment. Thirty-seven encoded ELF relocations and the synthetic objdiff R_PPC_NONE site give 38 objdiff relocation-bearing instructions.'
}
report['experiments']={}
for name in ['loop-results.json','followup-results.json','refine-results.json']:
 p=P/name
 if p.exists():report['experiments'][name]=json.loads(p.read_text())
report['commands']={}
for name,cmd in [('dol_sha1',['sha1sum','orig/GEDE01/sys/main.dol','build/GEDE01/main.dol']),('compiler_sha256',['sha256sum','compilers/GC/1.3/mwcceppc.exe']),('legal_audit',['python3','tools/legal_audit.py'])]:
 p=subprocess.run(cmd,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
 report['commands'][name]={'command':cmd,'exit_code':p.returncode,'raw_stdout_stderr':p.stdout}
for name in ['configure','ninja']:
 p=P/(name+'.txt')
 if p.exists():report['commands'][name]={'command':'python3 configure.py' if name=='configure' else '.tools/bin/ninja -j2','raw_stdout_stderr':p.read_text(),'exit_code':int((P/(name+'.exit')).read_text())}
report['legal_note']='Only reconstructed C, experiment/verification scripts, numerical measurements, symbol/relocation metadata and hashes are retained. Full disassembly and all object/DOL/compiler files stay untracked.'
out=pathlib.Path('reports/GEDE01')/('objdiff-'+A+'.json')
out.write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({k:v for k,v in report['measurement'].items() if k not in ['register_differences','elf_relocations','objdiff_relocation_sites']},indent=2))
print('relocation sites:',len(reloc_rows),'all equal:',all(r['equal'] for r in reloc_rows))
print('canonical:',report['objdiff']['canonical']['raw_summary_fields']['left']['symbols'][0]['match_percent'])
print('strict:',report['objdiff']['strict']['raw_summary_fields']['left']['symbols'][0]['match_percent'])
