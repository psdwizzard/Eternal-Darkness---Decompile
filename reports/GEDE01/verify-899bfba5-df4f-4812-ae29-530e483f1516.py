"""Reproduce assignment evidence from the canonical build; run in project root."""
import difflib, hashlib, json, pathlib, struct, subprocess
ID='899bfba5-df4f-4812-ae29-530e483f1516'
TARGET='fn_800C8568'
BASE='f4e1fa8bd8bde93ac9ed247e07cd20ad7a5bcd31'
report=pathlib.Path('reports/GEDE01')
commands=[]
def run(args):
 p=subprocess.run(args,capture_output=True,text=True)
 commands.append({'cwd':'eternal-darkness-decomp','argv':args,'exit_code':p.returncode,'stdout':p.stdout,'stderr':p.stderr})
 if p.returncode: raise RuntimeError(commands[-1])
 return p.stdout
run(['python3','configure.py'])
run(['.tools/bin/ninja','-j2'])
raw={}
for name,extra in [('canonical',[]),('relocation_strict',['-c','function_reloc_diffs=name_address'])]:
 args=['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_800C8568','-o','-','--format','json']+extra+[TARGET]
 # Store the parsed, unabridged tool response, avoiding duplicated stdout.
 raw[name]=json.loads(run(args));commands[-1]['stdout']='Stored without field removal in '+name
run(['sha1sum','build/GEDE01/main.dol'])
run(['python3','tools/legal_audit.py'])
run(['git','diff','--check'])
def sym(d,k): return next(s for s in d[k]['symbols'] if s['name']==TARGET)
def elf(path):
 data=pathlib.Path(path).read_bytes();assert data[:6]==b'\x7fELF\x01\x02'
 shoff=struct.unpack_from('>I',data,32)[0];entsize,n,strings=struct.unpack_from('>HHH',data,46)
 sections=[struct.unpack_from('>10I',data,shoff+i*entsize) for i in range(n)]
 def body(s):return data[s[4]:s[4]+s[5]]
 def string(b,off):return b[off:b.index(b'\x00',off)].decode()
 names=body(sections[strings]);named={string(names,s[0]):(i,s) for i,s in enumerate(sections)}
 text_index,text_section=named['.text'];relocations=[]
 for section in sections:
  if section[1]!=4 or section[7]!=text_index:continue
  syms=sections[section[6]];strs=body(sections[syms[6]])
  for off in range(0,section[5],section[9]):
   address,info,addend=struct.unpack_from('>IIi',data,section[4]+off)
   st_name,value,size,typ,other,ndx=struct.unpack_from('>IIIBBH',data,syms[4]+(info>>8)*syms[9])
   relocations.append({'offset':address,'type':info&255,'target_name':string(strs,st_name),'target_address':value,'addend':addend})
 return body(text_section),relocations
lt,lr=elf('build/GEDE01/obj/game/game_fn_800C8568.o');rt,rr=elf('build/GEDE01/src/game/game_fn_800C8568.o')
sha=hashlib.sha1(pathlib.Path('build/GEDE01/main.dol').read_bytes()).hexdigest()
assert sha=='ea24b6af954876ce072562ff39cdb4c81d32be1f'
left=sym(raw['canonical'],'left');right=sym(raw['canonical'],'right')
source=pathlib.Path('src/game/game_fn_800C8568.c').read_bytes()
preserved=subprocess.check_output(['git','show','57b9df56862460c14184c5ae3bfd35ec3a94668c:eternal-darkness-decomp/src/game/game_fn_800C8568.c'])
assert source==preserved
score=left['match_percent'];strict_score=sym(raw['relocation_strict'],'left')['match_percent']
assert score==strict_score==95.6
assert len(lt)==500 and len(rt)==492
same_relocations=sum(a==b for a,b in zip(lr,rr))
sequence_equal=[{k:v for k,v in a.items() if k!='offset'} for a in lr]==[{k:v for k,v in a.items() if k!='offset'} for a in rr]
divergence=("Canonical and relocation-strict objdiff both measure 95.60%; retail is 500 bytes and generated C is 492 bytes. "
"The preserved union reconstruction retains the full 32-bit radius for fn_800C928C and matches the 0x60 frame/stmw r20. "
"Generated C omits retail's inert cmpwi r27,1 at 0xFC, bne at 0x100 targeting 0x108, and nop at 0x104, "
"and adds sth r24,0x24(r1) at generated offset 0x100 after clrlwi. Later instructions shift by eight bytes; "
"the final call's addi r7 and argument moves are scheduled differently. "
"Pointer temporaries, scoped scratch lifetime, bitfield/word union members, old-style call declaration, aggregate copy, "
"inline normalization, and comma-expression call lowering did not improve the preserved best score. "
"Relocation types, targets, target values, and addends agree in sequence, but offsets do not; this is NonMatching.")
unit=next(u for u in json.load(open('objdiff.json'))['units'] if u['name']=='main/game/game_fn_800C8568')
experiments_path=f'eternal-darkness-decomp/reports/GEDE01/experiments-{ID}.json'
evidence={'version':1,'assignment_id':ID,'target':TARGET,'status':'attempted',
 'measurement':{'canonical_match_percent':score,'relocation_strict_match_percent':strict_score,'function_reloc_diffs':'name_address',
 'retail_size':len(lt),'generated_size':len(rt),'text_bytes_equal':lt==rt,'source_sha256':hashlib.sha256(source).hexdigest(),
 'compiler_sha256':hashlib.sha256(pathlib.Path('compilers/GC/1.3/mwcceppc.exe').read_bytes()).hexdigest(),
 'dol_sha1':sha,'retail_text_sha256':hashlib.sha256(lt).hexdigest(),'generated_text_sha256':hashlib.sha256(rt).hexdigest()},
 'canonical_compiler_configuration':unit.get('scratch'),
 'relocations':{'retail':lr,'generated':rr,'equal_count_in_sequence_with_offsets':same_relocations,
 'exact_equal':lr==rr,'sequence_equal_ignoring_offsets':sequence_equal,
 'retail_relocation_bearing_instruction_count':sum('relocation' in i.get('instruction',{}) for i in left['instructions']),
 'generated_relocation_bearing_instruction_count':sum('relocation' in i.get('instruction',{}) for i in right['instructions'])},
 'commands':commands,**raw,'experiments':experiments_path,'divergence':divergence,
 'historical_reconciliation':{'source_identical_to_preserved_commit':'57b9df56862460c14184c5ae3bfd35ec3a94668c',
 'accepted_base':BASE,'prior_attempts_studied':['57b9df56862460c14184c5ae3bfd35ec3a94668c','3d6707318395f2702853b449cb352979bbbed6b6','2da436eae6a780750e4cb6818e71100b26cfd52d','01ce4f0cdec46d2261aeb3f6d1be81c10ebcec32'],
 'branch_correction':'Raw retail objdiff shows bne at 0x100 targeting 0x108: displacement +8, skipping the nop at 0x104. It is neither a self-loop nor a trap. Earlier prose describing +4 was inaccurate.'},
 'scope_audit':{'source_retained_without_change':True,'registration':'Existing NonMatching registration retained. No configure.py or splits.txt edits.',
 'policy':'Canonical GC/1.3 flags unchanged; no inline or whole-function assembly, no compiler policy changes, no neighboring source edits.',
 'preexisting_changes_excluded':['CLAUDE.md'],'source_semantics':'Full int radius remains unchanged for final call. Only comparison narrows to u16. No infinite loops introduced.',
 'dol_caveat':'NonMatching target links retail code; the verified DOL hash does not establish that the C candidate matches.'}}
(report/f'objdiff-{ID}.json').write_text(json.dumps(evidence,indent=2)+'\n')
envelope={'version':1,'assignment_id':ID,'attempt':5,'base_commit':BASE,'target':TARGET,'status':'attempted',
'evidence':[f'eternal-darkness-decomp/reports/GEDE01/objdiff-{ID}.json',experiments_path],'divergence':divergence}
(report/f'durable-{ID}.json').write_text(json.dumps(envelope,indent=2)+'\n')
print(json.dumps({'score':score,'strict_score':strict_score,'retail_bytes':len(lt),'generated_bytes':len(rt),'retail_relocations':len(lr),'generated_relocations':len(rr),'exact_relocations':same_relocations,'sequence_equal':sequence_equal,'dol_sha1':sha},indent=2))
