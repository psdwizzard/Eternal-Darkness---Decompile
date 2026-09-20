#!/usr/bin/env python3
"""Run assignment-specific source hypotheses under the unchanged Ninja rule.
Run from eternal-darkness-decomp. Restores the starting source after all trials.
Trial objects are measured before the registered constant externalization.
Run python3 configure.py and .tools/bin/ninja -j2 afterwards to reapply it.
"""
import difflib, hashlib, json, pathlib, struct, subprocess
ID='0cdc49a6-c214-4668-8f17-0fc62fcf7826'
BASE='eb143e7299aea718bacfdf41f24ab8831310d045'
SOURCE='src/game/game_fn_80189C14.c'
OBJECT='build/GEDE01/src/game/game_fn_80189C14.o'
REPORT=pathlib.Path('reports/GEDE01/experiments-'+ID+'.json')
source=pathlib.Path(SOURCE)
baseline=subprocess.check_output(['git','show',BASE+':eternal-darkness-decomp/'+SOURCE],text=True)
original=source.read_text()
result={'version':1,'assignment_id':ID,'base_commit':BASE,'source':SOURCE,'object':OBJECT,'cwd':'eternal-darkness-decomp','experiments':[]}
def run(cmd):
 p=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
 return {'argv':cmd,'exit_code':p.returncode,'output':p.stdout}
def text_hash():
 data=pathlib.Path(OBJECT).read_bytes()
 off=struct.unpack_from('>I',data,32)[0]; es,num,strings=struct.unpack_from('>HHH',data,46)
 headers=[struct.unpack_from('>10I',data,off+i*es) for i in range(num)]
 sh=headers[strings]; names=data[sh[4]:sh[4]+sh[5]]
 for h in headers:
  if names[h[0]:].split(b'\0',1)[0]==b'.text':
   return hashlib.sha256(data[h[4]:h[4]+h[5]]).hexdigest()
 raise ValueError('missing .text')
def trial(name,code,hypothesis):
 source.write_text(code)
 row={'name':name,'hypothesis':hypothesis,'patch':''.join(difflib.unified_diff(baseline.splitlines(True),code.splitlines(True),fromfile='a/'+SOURCE,tofile='b/'+SOURCE)), 'source_sha256':hashlib.sha256(source.read_bytes()).hexdigest()}
 row['build']=run(['.tools/bin/ninja','-j2','-v',OBJECT])
 if row['build']['exit_code']==0:
  row['object_sha256']=hashlib.sha256(pathlib.Path(OBJECT).read_bytes()).hexdigest()
  row['text_sha256']=text_hash()
  diff=run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80189C14','fn_80189C14','-o','-','--format','json'])
  row['objdiff']=diff
  if diff['exit_code']==0:
   d=json.loads(diff['output']);a=next(s for s in d['left']['symbols'] if s['name']=='fn_80189C14');b=next(s for s in d['right']['symbols'] if s['name']=='fn_80189C14')
   row['measurement']={'match_percent':a['match_percent'],'retail_size':a['size'],'generated_size':b['size'],'retail_instructions':sum('instruction' in i for i in a['instructions']),'generated_instructions':sum('instruction' in i for i in b['instructions'])}
 result['experiments'].append(row); REPORT.write_text(json.dumps(result,indent=2)+'\n')
 print(name,row.get('measurement'),row.get('object_sha256'),flush=True)
try:
 trial('baseline',baseline,'Retained accepted reconstruction; force source rebuild to capture compiler invocation and hash.')
 code=baseline.replace('self = arg;','self = arg + 0x5C;').replace('self[1]','arg[1]')
 for off in ['0x50','0x54','0x58','0x4C']: code=code.replace('self + '+off,'arg + '+off)
 code=code.replace('self + 0x94','self + 0x38').replace('self + 0xB8','self + 0x5C').replace('fn_8018D0D0(self, self + 0x5C, *(s16*)(self + 0xE))','fn_8018D0D0(self - 0x5C, self, *(s16*)(self - 0x4E))')
 trial('interior_pointer',code,'Store the late-use self pointer biased to the +0x5C subobject, while early loads use arg. Tests whether a non-copy virtual register avoids incoming-parameter r31 coloring; all effective addresses remain unchanged.')
 code=baseline.replace('u8* self;','struct { u8* pointer; } owner;').replace('self','owner.pointer')
 trial('scalar_aggregate',code,'Represent the retained owner pointer as a local single-field aggregate to test scalar replacement versus incoming-parameter copy coalescing. This changes the storage object, unlike the earlier pointed-to-type hypothesis.')
 code=baseline.replace('fn_80189C14(u8* arg)','fn_80189C14(unsigned long arg)').replace('self = arg;','self = (u8*)arg;')
 trial('integer_parameter',code,'Use an ABI-equivalent 32-bit unsigned incoming address and explicit pointer conversion to test whether pointer-parameter coloring survives the type conversion, without changing any effective address.')
 code=baseline.replace('u8* self;','union { u8* pointer; unsigned long bits; } owner;').replace('self','owner.pointer').replace('owner.pointer = arg;','owner.bits = (unsigned long)arg;')
 trial('union_representation',code,'Copy the address through a local union integer representation, then use its pointer representation. Tests whether scalar replacement across different member types breaks parameter coalescing on the 32-bit target.')
 integer=baseline.replace('fn_80189C14(u8* arg)','fn_80189C14(unsigned long arg)').replace('self = arg;','self = (u8*)arg;')
 code=integer.replace('u8* data = lbl_80607120;','u8* data;').replace('u16 size0 = *(u16*)(data + 2);','u16 size0;').replace('self = (u8*)arg;','self = (u8*)arg;\n    data = lbl_80607120;\n    size0 = *(u16*)(data + 2);')
 trial('integer_delayed_data',code,'Initialize data and size0 after converting the incoming integer address, allowing incoming r3 to die before the global address is formed.')
 code=code.replace('position_offset = 0;\n    for (entry_index = 0;', 'entry_index = 0;\n    position_offset = 0;\n    for (;')
 trial('integer_delayed_data_loop_order',code,'Additionally initialize entry_index before position_offset to reproduce retail li r28 then li r15 scheduling.')
 best=code
 code=best.replace('data = lbl_80607120;', 'arg = (unsigned long)lbl_80607120;\n    data = (u8*)arg;')
 trial('integer_reuse_argument',code,'Reuse the dead integer argument for the global address so address materialization can reuse incoming r3.')
 code=best.replace('unsigned long arg','int arg')
 trial('signed_integer_parameter',code,'Check whether signed integer address representation changes transient address allocation, retaining identical target ABI bits.')
 code=best.replace('data = lbl_80607120;\n    size0 = *(u16*)(data + 2);\n    count = self[1];','count = self[1];\n    data = lbl_80607120;\n    size0 = *(u16*)(data + 2);')
 trial('count_before_data',code,'Place the first self dereference before global address materialization to end incoming integer-address liveness before data scratch assignment.')
 code=best.replace('u8* data;','unsigned long data;').replace('data = lbl_80607120;','data = (unsigned long)lbl_80607120;')
 trial('integer_data_address',code,'Represent the global table address as an integer too, testing whether transient address class controls r3 versus r4 selection.')
 code=best.replace('    u8* data;\n','').replace('    data = lbl_80607120;\n','').replace('(data + ', '(lbl_80607120 + ')
 trial('direct_global_loads',code,'Remove the local data pointer and address each table field directly, giving common-address elimination control of the transient high-half register.')
 code=best.replace('u8* data;','u16* data;').replace('data = lbl_80607120;','data = (u16*)lbl_80607120;')
 for old,new in [('*(u16*)(data + 2)','data[1]'),('*(u16*)(data + 0xA)','data[5]'),('*(u16*)(data + 0xE)','data[7]'),('*(u16*)(data + 0xC)','data[6]')]: code=code.replace(old,new)
 trial('short_data_pointer',code,'Use a u16 table pointer with indexed loads, testing transient address allocation for scaled C lvalues.')
 code=best.replace('fn_80189C14(unsigned long arg)','fn_80189C14(u8* arg)').replace('u8* self;','unsigned long owner_address;').replace('self = (u8*)arg;','owner_address = (unsigned long)arg;').replace('self','((u8*)owner_address)')
 trial('pointer_parameter_integer_owner',code,'Reverse the successful representation boundary: pointer ABI parameter with integer long-lived owner address, casting at uses. Tests whether the parameter can die before high-half formation while owner avoids pointer-parameter preference.')
 code=best.replace('u8* data;','u8* data;').replace('self = (u8*)arg;', 'self = (u8*)arg;\n    arg = 0;')
 trial('explicit_parameter_kill',code,'Explicitly overwrite the integer parameter immediately after saving its pointer value, testing early input-register liveness termination.')
 code=best.replace('u8* data;','register u8* data;')
 trial('integer_register_data',code,'On the successful integer-parameter branch, prioritize the global data pointer for transient register allocation.')
 code=best.replace('u8* self;','register u8* self;')
 trial('integer_register_owner',code,'On the successful integer-parameter branch, prioritize the converted owner before the global data address; earlier register tests used the pointer-parameter branch.')
 code=best.replace('fn_80189C14(unsigned long arg)','fn_80189C14(register unsigned long arg)')
 trial('integer_register_argument',code,'Test register-qualified integer incoming argument, after its representation was shown to affect coloring.')
 code=best.replace('extern u8 lbl_80607120[], lbl_8063C098[];', 'extern struct { u16 unused; u16 size0; u16 pad[3]; u16 flush0; u16 flush2; u16 flush1; } lbl_80607120;\nextern u8 lbl_8063C098[];').replace('    u8* data;\n','').replace('    data = lbl_80607120;\n','')
 for old,new in [('*(u16*)(data + 2)','lbl_80607120.size0'),('*(u16*)(data + 0xA)','lbl_80607120.flush0'),('*(u16*)(data + 0xE)','lbl_80607120.flush1'),('*(u16*)(data + 0xC)','lbl_80607120.flush2')]: code=code.replace(old,new)
 trial('global_structure',code,'Model the global table as an actual struct object with field lvalues, testing symbol-offset address lowering rather than array-base arithmetic.')
finally:
 source.write_text(original)
 result['restore']=run(['.tools/bin/ninja','-j2','-v',OBJECT])
 result['restored_object_sha256']=hashlib.sha256(pathlib.Path(OBJECT).read_bytes()).hexdigest()
 REPORT.write_text(json.dumps(result,indent=2)+'\n')
