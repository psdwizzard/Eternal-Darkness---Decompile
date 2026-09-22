import json,subprocess,re,hashlib
from pathlib import Path
A='174d74e1-3fdf-41fd-99ed-047612b2963f'
P=Path('reports/GEDE01')/A
rootprefix='eternal-darkness-decomp/'
runs=[]
def run(label,cmd):
 r=subprocess.run(cmd,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
 rec={'label':label,'command':cmd,'cwd':'eternal-darkness-decomp','returncode':r.returncode,'output':r.stdout}
 runs.append(rec)
 (P/(label+'.log')).write_text(r.stdout)
 if r.returncode:raise RuntimeError(rec)
 return r.stdout
obj=['build/GEDE01/obj/game/game_fn_8017CCD8.o','build/GEDE01/src/game/game_fn_8017CCD8.o']
common=['build/tools/objdiff-cli','diff','-1',obj[0],'-2',obj[1],'fn_8017CCD8','--format','json']
scores={}
for mode,extra in [('canonical',[]),('relocation-strict',['-c','function_reloc_diffs=name_address'])]:
 run(mode,common+extra+['-o',str(P/(mode+'.json'))])
 d=json.loads((P/(mode+'.json')).read_text())
 l=next(s for s in d['left']['symbols'] if s['name']=='fn_8017CCD8')
 r=next(s for s in d['right']['symbols'] if s['name']=='fn_8017CCD8')
 scores[mode]={'match_percent':l['match_percent'],'retail_size':l['size'],'generated_size':r['size'],'raw_output':rootprefix+str(P/(mode+'.json'))}
rels=[]
for label,path in zip(['retail-relocations','generated-relocations'],obj):
 output=run(label,['readelf','-rW',path])
 rels.append([line.split()[:1]+line.split()[2:] for line in output.splitlines() if re.match(r'^[0-9a-fA-F]{8}\s',line)])
assert len(rels[0])==8 and rels[0]==rels[1]
commands=run('compiler-commands',['.tools/bin/ninja','-t','commands',obj[1]])
compiler=next(l for l in commands.splitlines() if ' -c src/game/game_fn_8017CCD8.c ' in l)
run('toolchain-digests',['sha256sum','compilers/GC/1.3/mwcceppc.exe','build/tools/objdiff-cli'])
run('objdiff-version',['build/tools/objdiff-cli','--version'])
source=Path('src/game/game_fn_8017CCD8.c').read_text()
assert not re.search(r'\b(?:asm|__asm|INCBIN)\b',source)
assert 'Object(NonMatching, "game/game_fn_8017CCD8.c")' in Path('configure.py').read_text()
meta={'version':1,'assignment_id':A,'target':'fn_8017CCD8','status':'attempted','measurements':scores,'runs':runs,
'compiler':{'revision':'GC/1.3','command':compiler,'policy':'Unchanged canonical configure.py settings'},
'relocations':{'equal':True,'count':8,'comparison_fields':['offset','type','symbol_value','target','addend'],'retail':rels[0],'generated':rels[1]},
'experiments':{'hypothesis':'Changing typed pointer stride into equivalent byte/integer arithmetic may change MWCC dependency scheduling; supplementary operand-commutation and signed-promotion controls.', 'reproduction_command':'python3 reports/GEDE01/'+A+'/experiment.py','source_and_raw_build_runs':rootprefix+str(P/'experiments.json'),'results':[{'name':r['name'],'score':r.get('score'),'raw_objdiff':rootprefix+r['raw_objdiff']} for r in json.loads((P/'experiments.json').read_text())]},
'preserved_attempts_reviewed':['0c9682c26dd78324c02e3a535e1b121ff81fe9e2','0746dabb22e6608471681d018355e90b7e617da3'],
'legal_audit':{'independent_c_translation_unit':True,'source':rootprefix+'src/game/game_fn_8017CCD8.c','source_sha256':hashlib.sha256(source.encode()).hexdigest(),'inline_or_whole_function_assembly':False,'source_and_registration_unchanged_from_base':True,'retained_registration':'NonMatching','new_compiler_policy':False,'shared_inputs_modified':False,'neighboring_functions_edited':False,'note':'Existing reconstruction retained; rejected source variants are embedded only as report data. No assembly, object patching, runtime edits, or global progress edits.'}}
Path('reports/GEDE01/objdiff-'+A+'.json').write_text(json.dumps(meta,indent=2)+'\n')
print(json.dumps(scores,indent=2))
