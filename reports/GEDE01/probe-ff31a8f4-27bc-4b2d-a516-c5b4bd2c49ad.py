"""Assignment-only reproducible canonical-compiler register-web experiments.
Run from eternal-darkness-decomp. Only target source and report outputs are edited.
Diagnostic bias externalization uses the existing tool, verified against retail.
"""
import subprocess, json, re, hashlib, difflib
from pathlib import Path
ID='ff31a8f4-27bc-4b2d-a516-c5b4bd2c49ad'
SRC=Path('src/game/game_fn_8000F774.c')
OBJ='build/GEDE01/src/game/game_fn_8000F774.o'
REPORT=Path('reports/GEDE01/trials-'+ID+'.json')
BASE=subprocess.check_output(['git','show','f7382393ba916acff6c8629b1a2323c53f44bf8d:eternal-darkness-decomp/src/game/game_fn_8000F774.c'],text=True)

def run(args,record):
 p=subprocess.run(args,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
 record.append({'argv':args,'returncode':p.returncode,'raw_output':p.stdout})
 if p.returncode: raise RuntimeError(p.stdout)
 return p.stdout

def trial(name,source,hypothesis):
 original=SRC.read_text()
 rec={'name':name,'hypothesis':hypothesis,'source_sha256':hashlib.sha256(source.encode()).hexdigest(),'patch_from_base':''.join(difflib.unified_diff(BASE.splitlines(True),source.splitlines(True),fromfile=str(SRC),tofile=str(SRC))),'commands':[]}
 records=json.loads(REPORT.read_text()) if REPORT.exists() else {'version':1,'assignment_id':ID,'trials':[]}
 try:
  SRC.write_text(source)
  run(['.tools/bin/ninja','-j2',OBJ],rec['commands'])
  sym=run(['build/binutils/powerpc-eabi-objdump','-t',OBJ],rec['commands'])
  bias=re.findall(r'\.sdata2\s+00000008\s+(@\d+)',sym)
  assert len(bias)==1,bias
  rec['bias_symbol']=bias[0]
  run(['python3','tools/externalize_elf_symbol.py',OBJ,bias[0],'lbl_8064DCE8','orig/GEDE01/sys/main.dol'],rec['commands'])
  run(['build/binutils/powerpc-eabi-objcopy','--redefine-sym='+bias[0]+'=lbl_8064DCE8','--remove-section=.sdata2',OBJ],rec['commands'])
  raw=run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_8000F774','fn_8000F774','-o','-','--format','json','-c','function_reloc_diffs=name_address'],rec['commands'])
  p=json.loads(raw[raw.index('{'):])
  a=next(s for s in p['left']['symbols'] if s['name']=='fn_8000F774')
  b=next(s for s in p['right']['symbols'] if s['name']=='fn_8000F774')
  rec['measurement']={'size':b['size'],'match_percent':b['match_percent'],'diff_rows':sum(bool(x.get('diff_kind')) for x in b['instructions']),'instruction_count':sum('instruction' in x for x in b['instructions']), 'alignment_rows':len(b['instructions'])}
  print(name,rec['bias_symbol'],rec['measurement'],flush=True)
 except Exception as e:
  rec['error']=str(e);print(name,'ERROR',str(e)[:100],flush=True)
 finally:
  records['trials'].append(rec);REPORT.write_text(json.dumps(records,indent=2)+'\n')
  SRC.write_text(original)
 return rec

def region(s,start,end,old,new):
 a=s.index(start);b=s.index(end,a)
 return s[:a]+s[a:b].replace(old,new)+s[b:]

if __name__=='__main__':
 trial('baseline',BASE,'Reproduce accepted attempt 6 source under canonical settings.')
 # Split controller across disjoint semantic roles: callback controller vs effects.
 s=BASE.replace('    s32 controller;','    s32 controller;\n    void* effect;')
 s=region(s,'    } else if (req.f30 == 4)', '    } else if (req.f30 == 3)', 'controller','effect').replace('effect = (s32)fn_80204A8C();','effect = fn_80204A8C();').replace('(void*)effect','effect')
 trial('separate_effect_web',s,'Separate pointer-valued effect lifetime in cases 4/7 from controller in case 2.')
 s2=s.replace('    void* effect;','    void* effect4;\n    void* effect7;')
 s2=region(s2,'    } else if (req.f30 == 4)','    } else if (req.f30 == 7)','effect','effect4')
 s2=region(s2,'    } else if (req.f30 == 7)','    } else if (req.f30 == 3)','effect','effect7')
 trial('separate_each_effect_web',s2,'Separate all three controller/effect definitions, retaining branch semantics.')
 s3=BASE.replace('    s32 controller;','    void* controller;').replace('controller = (s32)','controller = ').replace('(void*)controller','controller')
 trial('pointer_controller',s3,'Use the actual pointer return type for controller without integer roundtrips.')
 s4=s.replace('    s32 controller;','    void* controller;').replace('controller = (s32)','controller = ').replace('(void*)controller','controller')
 trial('pointer_controller_separate_effect',s4,'Combine type-correct controller pointer with separated effect web.')
 s5=BASE.replace('    s32 controller;','    s32 controller;\n    void* object;').replace('        void* object;\n','')
 trial('hoist_object',s5,'Make the final object web a function-scope declaration, after controller.')
 s6=BASE.replace('    void* found;','    void* attachment;\n    void* found;')
 s6=region(s6,'        found = fn_80201C2C','        array = fn_80201C24','found','attachment')
 trial('split_found_roles',s6,'Separate the attachment search result from the later item-owner search result.')
 s7=BASE.replace('    ItemArray* array;','    ItemArray* array;\n    ItemArray* data_array;').replace('array = *(ItemArray**)array;','data_array = *(ItemArray**)array;').replace('array->items[index], array->data','data_array->items[index], data_array->data')
 trial('split_array_indirection',s7,'Separate outer item-array pointer and its dereferenced inner data pointer.')
