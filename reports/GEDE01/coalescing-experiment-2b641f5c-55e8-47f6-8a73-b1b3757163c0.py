import runpy,json
m=runpy.run_path('reports/GEDE01/experiment-2b641f5c-55e8-47f6-8a73-b1b3757163c0.py')
m['results'].extend(json.loads((m['REPORT']/f"experiments-{m['ID']}.json").read_text()))
b=m['base']; run=m['run']
original_source=m['SOURCE'].read_text()
try:
    explicit=b.replace('            fn_80128C28(converted_resource, fn_80204810, value | 0x77);\n            fn_80128C44(converted_resource, fn_80204810, value | 0x77);','            value |= 0x77;\n            fn_80128C28(converted_resource, fn_80204810, value);\n            fn_80128C44(converted_resource, fn_80204810, value);')
    run('explicit_event_id',explicit)
    room=b.replace('int source_id = fn_80200C20(source);','room = fn_80200C20(source);').replace('source_id == current_id','room == current_id').replace('int object_id = fn_80201B54(object);','room = fn_80201B54(object);').replace('object_id','room')
    run('context_id_coalescing',room)
    ternary=b.replace('            amount = -0x23;\n            if (runtime->kind == 10) {\n                amount = 0x32;\n            }','            amount = runtime->kind == 10 ? 0x32 : -0x23;')
    run('conditional_amount',ternary)
    run('conditional_amount_inverted',ternary.replace('runtime->kind == 10 ? 0x32 : -0x23','runtime->kind != 10 ? -0x23 : 0x32'))
    branch=b.replace('            amount = -0x23;\n            if (runtime->kind == 10) {\n                amount = 0x32;\n            }','            if (runtime->kind == 10) {\n                amount = 0x32;\n            } else {\n                amount = -0x23;\n            }')
    run('two_branch_amount',branch)
finally:
    m['SOURCE'].write_text(original_source)
