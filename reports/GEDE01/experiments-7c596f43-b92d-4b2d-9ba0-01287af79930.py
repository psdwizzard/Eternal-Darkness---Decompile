"""Attempt 8: explicit parser CFG and loop-exit lowering, canonical compiler."""
import subprocess, json, difflib, struct, re
from pathlib import Path
ID="7c596f43-b92d-4b2d-9ba0-01287af79930"
p=Path('src/game/game_fn_801E6814.c')
base=subprocess.check_output(['git','show','f696af3:eternal-darkness-decomp/'+str(p)],text=True)
configuration=Path('configure.py'); original_configuration=configuration.read_text()
def registration():
 data=Path('build/GEDE01/src/game/game_fn_801E6814.o').read_bytes()
 shoff=struct.unpack_from('>I',data,32)[0]; shsize,shcount=struct.unpack_from('>HH',data,46)
 sections=[struct.unpack_from('>10I',data,shoff+i*shsize) for i in range(shcount)]
 names={}
 for h in sections:
  if h[1]!=2: continue
  strings=sections[h[6]]
  for off in range(h[4],h[4]+h[5],h[9]):
   name,value,size,info,other,section=struct.unpack_from('>IIIBBH',data,off)
   start=strings[4]+name; name=data[start:data.index(0,start)].decode()
   if name.startswith('@') and section<len(sections):
    o=sections[section][4]+value; bits=data[o:o+8].hex()
    if bits in ['4330000000000000','4330000080000000']: names[bits]=name
 assert len(names)==2,names
 block='    "801E6814": (\n        ".sdata2",\n        [("'+names['4330000000000000']+'", "lbl_80651268"), ("'+names['4330000080000000']+'", "lbl_80651288")],\n    ),'
 updated=re.sub(r'    "801E6814": \(.*?\n    \),',lambda m:block,original_configuration,flags=re.S)
 configuration.write_text(updated)
 c=subprocess.run(['python3','configure.py'],capture_output=True,text=True)
 assert c.returncode==0,c.stderr
 return names

condition="*text >= '0' && *text <= '9' && digits < 3"
body="""                    value *= 10;
                    value += *text;
                    digits++;
                    text++;
                    value -= '0';"""
loop="                while ("+condition+") {\n"+body+"\n                }"
variants={'recovered_baseline':base}
replacements={
 'explicit_breaks':"                while (1) {\n                    if (*text < '0') break;\n                    if (*text > '9') break;\n                    if (digits >= 3) break;\n"+body+"\n                }",
 'combined_break':"                while (1) {\n                    if (*text < '0' || *text > '9' || digits >= 3) break;\n"+body+"\n                }",
 'goto_tests':"                goto parser_test;\nparser_body:\n"+body+"\nparser_test:\n                if (*text < '0') goto parser_end;\n                if (*text > '9') goto parser_end;\n                if (digits < 3) goto parser_body;\nparser_end:;",
 'goto_positive':"                goto parser_test;\nparser_body:\n"+body+"\nparser_test:\n                if (*text >= '0') {\n                    if (*text <= '9') {\n                        if (digits < 3) goto parser_body;\n                    }\n                }",
 'guarded_do':"                if ("+condition+") {\n                    do {\n"+body+"\n                    } while ("+condition+");\n                }",
 'range_while_count_break':"                while (*text >= '0' && *text <= '9') {\n                    if (digits >= 3) break;\n"+body+"\n                }",
 'first_test_while_remaining_breaks':"                while (*text >= '0') {\n                    if (*text > '9') break;\n                    if (digits >= 3) break;\n"+body+"\n                }",
 'do_with_forward_exit':"                do {\n                    if (*text < '0') break;\n                    if (*text > '9') break;\n                    if (digits >= 3) break;\n"+body+"\n                } while (1);",
}
for name,replacement in replacements.items():
 variants[name]=base.replace(loop,replacement)
 variants[name+'_commuted']=base.replace(loop,replacement.replace('value += *text;', 'value = *text + value;'))
out={'version':1,'assignment_id':ID,'hypothesis':'Parser loop CFG construction: explicit forward exits, backward goto and guarded do loops may change MWCC allocator traversal independently of arithmetic/declaration variants already exhausted. Commuted variants test interaction with the retail add operand order.','recovered_commit':'f696af3fb7eee1af2161da125872b2813bf61757','trials':[]}
best=base; bestscore=0; bestconfig=original_configuration
try:
 for name,s in variants.items():
  p.write_text(s)
  cmd=['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_801E6814.externalized']
  b=subprocess.run(cmd,capture_output=True,text=True)
  t={'name':name,'source_diff':''.join(difflib.unified_diff(base.splitlines(True),s.splitlines(True),fromfile='recovered_baseline',tofile=name)),'build_command':cmd,'build_exit':b.returncode,'build_stdout':b.stdout,'build_stderr':b.stderr}
  if b.returncode!=0:
   try:
    t['constant_registration']=registration()
    b=subprocess.run(cmd,capture_output=True,text=True)
    t.update(retry_build_exit=b.returncode,retry_build_stdout=b.stdout,retry_build_stderr=b.stderr)
   except Exception as e: t['registration_error']=str(e)
  if b.returncode==0:
   cmd=['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_801E6814','fn_801E6814','-o','-','--format','json','-c','function_reloc_diffs=name_address']
   d=subprocess.run(cmd,capture_output=True,text=True)
   t.update(diff_command=cmd,diff_exit=d.returncode,diff_stderr=d.stderr)
   if d.returncode==0:
    x=json.loads(d.stdout); a=next(v for v in x['left']['symbols'] if v['name']=='fn_801E6814'); z=next(v for v in x['right']['symbols'] if v['name']=='fn_801E6814')
    t.update(score=a['match_percent'],retail_size=a['size'],generated_size=z['size'],instructions={k:[v.get('instruction',{}).get('formatted') for v in o['instructions']] for k,o in [('left',a),('right',z)]})
    if t['score']>bestscore: bestscore=t['score']; best=s; bestconfig=configuration.read_text(); out['selected_trial']=name
  out['trials'].append(t)
  Path('reports/GEDE01/experiments-'+ID+'.json').write_text(json.dumps(out,indent=2)+'\n')
  print(name,t.get('score'),b.returncode,flush=True)
  if bestscore==100:break
finally:
 p.write_text(best)
 configuration.write_text(bestconfig)
 subprocess.run(['python3','configure.py'],check=True)
