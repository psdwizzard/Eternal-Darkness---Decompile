import json,pathlib,subprocess
p=pathlib.Path('src/game/game_fn_801599BC.c')
d=pathlib.Path('reports/GEDE01/acdd1e87-01b3-4d20-835d-775ef2e831b0')
s=json.loads((d/'corrected-alias-run.json').read_text())['source']
old='''            entry->state = -1;
            entry->kind = 5;
            entry->offset = offset;
            entry->size = 0x199A00;
            offset = entry->offset + entry->size;
            entry++;'''
variants={
 'compound-offset': '''            entry->offset = offset;
            offset += 0x199A00;
            entry->state = -1;
            entry->kind = 5;
            entry->size = 0x199A00;
            entry++;''',
 'assignment-expression': '''            offset = (entry->offset = offset) + 0x199A00;
            entry->state = -1;
            entry->kind = 5;
            entry->size = 0x199A00;
            entry++;''',
 'offset-first-alias': '''            entry->offset = offset;
            entry->state = -1;
            entry->kind = 5;
            entry->size = 0x199A00;
            offset = entry->offset + entry->size;
            entry++;''',
 'size-first-assignment': '''            entry->size = 0x199A00;
            entry->offset = offset;
            offset += entry->size;
            entry->state = -1;
            entry->kind = 5;
            entry++;''',
 'chained-offset': '''            entry->offset = offset;
            entry->state = -1;
            entry->kind = 5;
            offset += (entry->size = 0x199A00);
            entry++;''',
}
for name,body in variants.items():
 p.write_text(s.replace(old,body))
 subprocess.run(['python3',str(d/'measure.py'),name],check=True)
