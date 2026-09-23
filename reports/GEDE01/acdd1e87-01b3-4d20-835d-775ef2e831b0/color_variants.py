import json,pathlib,subprocess
p=pathlib.Path('src/game/game_fn_801599BC.c')
d=pathlib.Path('reports/GEDE01/acdd1e87-01b3-4d20-835d-775ef2e831b0')
s=json.loads((d/'header-initialization-run.json').read_text())['source']
variants={
 'global-slot':s.replace('        int slot;\n','').replace('        slot = lbl_8064D17C;\n','').replace('slot', 'lbl_8064D17C'),
 'slot-decl-last':s.replace('        int slot;\n','').replace('        Slot* entry;', '        Slot* entry;\n        int slot;'),
 'slot-register':s.replace('int slot;', 'register int slot;'),
 'size-local':s.replace('        int slot;', '        int slot;\n        int size;').replace('        entry = lbl_805B6F80;', '        entry = lbl_805B6F80;\n        size = 0x199A00;').replace('entry->size = 0x199A00;', 'entry->size = size;'),
 'offset-increment-first':s.replace('i++, offset += 0x199A00', 'offset += 0x199A00, i++'),
 'slot-assign-expression':s.replace('        slot = lbl_8064D17C;\n        lbl_8064D178 = slot;', '        lbl_8064D178 = slot = lbl_8064D17C;'),
 'slot-unsigned':s.replace('int slot;', 'unsigned int slot;').replace('if (slot < 4)', 'if ((int)slot < 4)'),
 'size-before-state':s.replace('            entry->state = -1;\n            entry->kind = 5;\n            entry->size = 0x199A00;', '            entry->size = 0x199A00;\n            entry->state = -1;\n            entry->kind = 5;'),
}
for name,src in variants.items():
 p.write_text(src)
 subprocess.run(['python3',str(d/'measure.py'),name],check=True)
