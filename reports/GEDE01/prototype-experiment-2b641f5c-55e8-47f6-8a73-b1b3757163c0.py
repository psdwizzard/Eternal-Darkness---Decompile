import runpy
m=runpy.run_path('reports/GEDE01/experiment-2b641f5c-55e8-47f6-8a73-b1b3757163c0.py')
import json
m['results'].extend(json.loads((m['REPORT']/f"experiments-{m['ID']}.json").read_text()))
b=m['base']; run=m['run']
original_source=m['SOURCE'].read_text()
try:
    proto=b.replace('extern void fn_801A7518();','extern void fn_801A7518(void*, short);')
    run('short_prototype',proto)
    run('short_prototype_int_amount',proto.replace('register short amount;','register int amount;'))
    run('short_prototype_unhinted_amount',proto.replace('register short amount;','short amount;'))
    run('unhinted_locals',b.replace('register ',''))
finally:
    m['SOURCE'].write_text(original_source)
