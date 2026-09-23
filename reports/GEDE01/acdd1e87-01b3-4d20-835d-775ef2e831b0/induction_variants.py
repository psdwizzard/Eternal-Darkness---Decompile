import json,pathlib,subprocess
p=pathlib.Path('src/game/game_fn_801599BC.c')
d=pathlib.Path('reports/GEDE01/acdd1e87-01b3-4d20-835d-775ef2e831b0')
s=json.loads((d/'offset-first-loaded-literal-run.json').read_text())['source']
variants={
'register-loaded':s.replace('int offset =', 'register int offset ='),
'register-literal':s.replace('int offset =', 'register int offset =').replace('offset = entry->offset + 0x199A00;', 'offset += 0x199A00;'),
'unsigned-loaded':s.replace('int offset =', 'unsigned int offset ='),
'header-induction':s.replace('for (i = 0; i < 4; i++) {','for (i = 0; i < 4; i++, offset += 0x199A00) {').replace('            offset = entry->offset + 0x199A00;\n',''),
'pointer-loaded':s.replace('int offset = 0x600000;', 'char* offset = (char*)0x600000;').replace('entry->offset = offset;', 'entry->offset = (int)offset;').replace('offset = entry->offset + 0x199A00;', 'offset = (char*)entry->offset + 0x199A00;'),
}
start=s.index('        for (i = 0; i < 4; i++) {',s.index('if (clear != 0)'))
end=s.index('        slot =',start)
body=s[start:end].split('{\n',1)[1].rsplit('        }',1)[0]
variants['explicit-sequential']=s[:start]+body*4+s[end:]
variants['explicit-literal']=variants['explicit-sequential'].replace('offset = entry->offset + 0x199A00;', 'offset += 0x199A00;')
for name,src in variants.items():
 p.write_text(src)
 subprocess.run(['python3',str(d/'measure.py'),name],check=True)
