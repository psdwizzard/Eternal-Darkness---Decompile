import pathlib,subprocess,json,hashlib
root=pathlib.Path(__file__).resolve().parents[3]
r=pathlib.Path(__file__).resolve().parent
src=root/'src/game/game_fn_80088A04.c'
entry_source=src.read_text()
original=subprocess.check_output(['git','show','2f48f2ee01abe95fadde42861598a098e747c86d:eternal-darkness-decomp/src/game/game_fn_80088A04.c'],cwd=root,text=True)
copy='''owner->position.x = output.x;
        owner->position.y = output.y;
        owner->position.z = output.z;'''
array=original.replace('    s16 angle;\n    u8 pad02[0x12];\n    s16 phase;\n    u8 pad16[0x12];\n    s16 scale;', '    s16 value;\n    u8 pad[0x12];').replace('extern Settings lbl_8031D3B8;', 'extern Settings lbl_8031D3B8[3];').replace('&lbl_8031D3B8;', 'lbl_8031D3B8;').replace('settings->angle','settings[0].value').replace('settings->phase','settings[1].value').replace('settings->scale','settings[2].value')
variants={
 'settings-record-array': array,
 'settings-halfword-array': original.replace('extern Settings lbl_8031D3B8;', 'extern s16 lbl_8031D3B8[21];').replace('Settings* settings = &lbl_8031D3B8;', 's16* settings = lbl_8031D3B8;').replace('settings->angle','settings[0]').replace('settings->phase','settings[10]').replace('settings->scale','settings[20]'),
 'remainder-expression': original.replace('random = fn_800FBFB0();','random = fn_800FBFB0() % 352;').replace('settings->phase = random % 352;','settings->phase = random;'),
 'remainder-before-scale': original.replace('settings->scale = 128;', 'settings->phase = random % 352;\n        settings->scale = 128;').replace('input.z = -1;\n        settings->phase = random % 352;', 'input.z = -1;'),
 'angle-local': original.replace('int random;', 'int random;\n        int angle;').replace('settings->angle = fn_800FBFB0() % 512;', 'angle = fn_800FBFB0() % 512;\n        settings->angle = angle;'),
}

results=[]
try:
 for name,s in variants.items():
  src.write_text(s)
  cmd=['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80088A04.o']
  p=subprocess.run(cmd,cwd=root,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
  (r/(name+'.log')).write_text(p.stdout)
  if p.returncode: raise RuntimeError(p.stdout)
  cmd=['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80088A04','-o',str(r/(name+'.json')),'--format','json-pretty','-c','function_reloc_diffs=name_address','fn_80088A04']
  p=subprocess.run(cmd,cwd=root,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
  if p.returncode: raise RuntimeError(p.stdout)
  d=json.loads((r/(name+'.json')).read_text())
  syms=[next(x for x in d[side]['symbols'] if x['name']=='fn_80088A04') for side in ['left','right']]
  row={'name':name,'source_sha256':hashlib.sha256(s.encode()).hexdigest(),'score':syms[0]['match_percent'],'sizes':[x['size'] for x in syms]}
  results.append(row);print(row,flush=True)
finally:
 src.write_text(entry_source)
 (r/'experiments2.json').write_text(json.dumps(results,indent=2)+'\n')
