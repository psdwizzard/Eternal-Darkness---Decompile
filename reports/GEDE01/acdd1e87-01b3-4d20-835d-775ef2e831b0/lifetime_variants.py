import json,pathlib,subprocess
p=pathlib.Path('src/game/game_fn_801599BC.c')
d=pathlib.Path('reports/GEDE01/acdd1e87-01b3-4d20-835d-775ef2e831b0')
s=json.loads((d/'header-initialization-run.json').read_text())['source']
variants={
 'slot-reuse-i':s.replace('        int slot;\n','').replace('slot','i'),
 'slot-reuse-count':s.replace('        int slot;\n','').replace('slot','count'),
 'slot-via-active':s.replace('        int slot;\n','').replace('        slot = lbl_8064D17C;\n        lbl_8064D178 = slot;', '        lbl_8064D178 = lbl_8064D17C;').replace('slot','lbl_8064D178'),
 'init-before-header':s.replace('        entry = lbl_805B6F80;', '        entry = lbl_805B6F80;\n        offset = 0x600000;').replace('i = 0, offset = 0x600000', 'i = 0'),
 'entry-header':s.replace('        entry = lbl_805B6F80;\n','').replace('i = 0, offset = 0x600000', 'i = 0, offset = 0x600000, entry = lbl_805B6F80'),
 'index-entry':s.replace('        entry = lbl_805B6F80;\n','').replace('            entry->offset = offset;', '            entry = &lbl_805B6F80[i];\n            entry->offset = offset;').replace('            entry++;\n',''),
}
for update in ['i++, offset += 0x199A00, entry++', 'i++, entry++, offset += 0x199A00', 'entry++, i++, offset += 0x199A00']:
 variants['header-entry-'+str(len(variants))]=s.replace('i++, offset += 0x199A00', update).replace('            entry++;\n','')
for name,src in variants.items():
 p.write_text(src)
 subprocess.run(['python3',str(d/'measure.py'),name],check=True)
