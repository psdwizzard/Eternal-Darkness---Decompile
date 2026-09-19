"""Assignment-specific reproduction of allocator hypotheses; run from project root."""
import collections
import difflib
import hashlib
import json
from pathlib import Path
import re
import subprocess
import sys
import itertools

ID = 'a481b335-2969-4d04-984c-a83bd46d3628'
SOURCE = Path('src/game/game_fn_800A1278.c')
BASE = subprocess.check_output(['git', 'show', 'a606311d973926c35d9168300c6aac831dc44e78:eternal-darkness-decomp/' + str(SOURCE)], text=True)
OUT = Path('reports/GEDE01')
OBJ = 'build/GEDE01/src/game/game_fn_800A1278.o'
DIFF = ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_800A1278', '-c', 'function_reloc_diffs=name_address', '--format', 'json', '-o', '-', 'fn_800A1278']
variants = [('baseline', BASE)]
for names in [('work',), ('context',), ('transform',), ('position',), ('work','context'), ('work','context','transform','position'), ('object','info','i')]:
    prefix, s = BASE.split('int fn_800A1278', 1)
    for name in names:
        s = re.sub(r'^(    )([A-Za-z0-9_*]+ +' + name + r';)$', r'\1register \2', s, flags=re.M)
    variants.append(('register_' + '_'.join(names), prefix + 'int fn_800A1278' + s))
variants.append(('do_while', BASE.replace('for (i = 0; i < 3; i++) {', 'i = 0;\n        do {').replace('fn_8006DEF8(state, context->event, 0, 0, 0);\n        }', 'fn_8006DEF8(state, context->event, 0, 0, 0);\n        } while (++i < 3);')))
variants.append(('goto_loop', BASE.replace('for (i = 0; i < 3; i++) {', 'i = 0;\n    repeat_event:\n        {').replace('fn_8006DEF8(state, context->event, 0, 0, 0);\n        }', 'fn_8006DEF8(state, context->event, 0, 0, 0);\n        }\n        if (++i < 3) goto repeat_event;')))
for order in [('work','context','state','transform','position'), ('context','work','transform','position','state')]:
    types = {'work':'Work800A1278*','context':'Context800A1278*','state':'State800A1278*','transform':'void*','position':'Vec800A1278*'}
    prefix, s = BASE.split('int fn_800A1278', 1)
    for name in order:
        if name != 'state':
            s = s.replace('    ' + types[name] + ' ' + name + ';\n', '')
    before,body = s.split('    context = fn_8006ED3C',1)
    body = '    context = fn_8006ED3C' + body
    body = re.sub(r'(?<![.>])\b('+'|'.join(order)+r')\b', r'live.\1', body)
    # The member name of state->work is not a local variable.
    decl = '    struct {\n' + ''.join('        '+types[n]+' '+n+';\n' for n in order) + '    } live;\n\n    live.state = state;\n'
    variants.append(('aggregate_'+'_'.join(order), prefix+'int fn_800A1278'+before+decl+body))

# Scalar word copies expose uses before register allocation; whole-structure
# assignments may only expand after allocator priorities have been computed.
word_base = BASE.replace('typedef struct Vec800A1278 {\n    float x;\n    float y;\n    float z;\n} Vec800A1278;', 'typedef union Vec800A1278 {\n    struct { float x, y, z; } f;\n    u32 bits[3];\n} Vec800A1278;').replace('position->z', 'position->f.z')
for first,second in [(True,False),(False,True),(True,True)]:
    s=word_base
    if first:
        s=s.replace('work->position = *position;', '\n        '.join('work->position.bits[%d] = position->bits[%d];' % (i,i) for i in range(3)))
    if second:
        s=s.replace('*position = work->position;', '\n        '.join('position->bits[%d] = work->position.bits[%d];' % (i,i) for i in range(3)))
    variants.append(('word_copies_%s_%s'%(first,second),s))
# Loading pairs into temporaries expresses the original two-load/two-store order.
for first,second in [(True,False),(False,True),(True,True)]:
    s=word_base
    if first:
        s=s.replace('work->position = *position;', '{\n            u32 x = position->bits[0];\n            u32 y = position->bits[1];\n            work->position.bits[0] = x;\n            work->position.bits[1] = y;\n            work->position.bits[2] = position->bits[2];\n        }')
    if second:
        s=s.replace('*position = work->position;', '{\n            u32 x = work->position.bits[0];\n            u32 y = work->position.bits[1];\n            position->bits[0] = x;\n            position->bits[1] = y;\n            position->bits[2] = work->position.bits[2];\n        }')
    variants.append(('word_pairs_%s_%s'%(first,second),s))

# Vary real copy temporaries and their scope; this changes graph nodes without
# adding dummy operations, aliases, or changing compiler options.
for first,second in [(True,False),(False,True),(True,True)]:
    for reverse_loads,reverse_decls,scope in itertools.product([False,True],[False,True],['block','function']):
        s=word_base
        declarations=[]
        for which,enabled in [('save',first),('restore',second)]:
            if not enabled: continue
            src,dst=('position->bits','work->position.bits') if which=='save' else ('work->position.bits','position->bits')
            names=[which+'_x',which+'_y']
            decl_names=names[::-1] if reverse_decls else names
            loads=[names[i]+' = '+src+'[%d];'%i for i in range(2)]
            if reverse_loads: loads.reverse()
            decl='u32 '+', '.join(decl_names)+';'
            stores=[dst+'[%d] = '%i+names[i]+';' for i in range(2)] + [dst+'[2] = '+src+'[2];']
            copy='\n            '.join(loads+stores)
            if scope=='block': copy=decl+'\n            '+copy
            else: declarations.append('    '+decl+'\n')
            copy='{\n            '+copy+'\n        }'
            old='work->position = *position;' if which=='save' else '*position = work->position;'
            s=s.replace(old,copy)
        if declarations: s=s.replace('    int i;','    int i;\n'+''.join(declarations))
        variants.append(('copy_scope_%s_%s_%s_%s_%s'%(first,second,reverse_loads,reverse_decls,scope),s))

# Partial aggregate copies keep block-copy lowering but expose separate uses.
partial_base=word_base.replace('    u32 bits[3];', '    u32 bits[3];\n    struct { struct { u32 x, y; } xy; u32 z; } words;')
for first,second,offset in itertools.product([False,True],repeat=3):
    if not (first or second or offset): continue
    s=partial_base
    if first:
        s=s.replace('work->position = *position;', 'work->position.words.xy = position->words.xy;\n        work->position.bits[2] = position->bits[2];')
    if second:
        s=s.replace('*position = work->position;', 'position->words.xy = work->position.words.xy;\n        position->bits[2] = work->position.bits[2];')
    if offset:
        s=s.replace('offset = lbl_802396E0;', 'offset.words.xy = lbl_802396E0.words.xy;\n        offset.bits[2] = lbl_802396E0.bits[2];')
    variants.append(('partial_copy_%s_%s_%s'%(first,second,offset),s))
# All three real components in temporaries can change priority and scheduling.
for first,second in [(True,False),(False,True),(True,True)]:
    s=word_base
    for enabled,src,dst,old in [(first,'position->bits','work->position.bits','work->position = *position;'),(second,'work->position.bits','position->bits','*position = work->position;')]:
        if enabled:
            code=['u32 x = '+src+'[0];','u32 y = '+src+'[1];','u32 z = '+src+'[2];']
            code += [dst+'[%d] = '%i+n+';' for i,n in enumerate(['x','y','z'])]
            s=s.replace(old,'{\n            '+'\n            '.join(code)+'\n        }')
    variants.append(('three_temps_%s_%s'%(first,second),s))

results=[]
best_source=BASE
best_score=-1
if '--new-only' in sys.argv:
    results=json.loads((OUT/('experiments-'+ID+'.json')).read_text())
    names={x['variant'] for x in results}
    variants=[x for x in variants if x[0] not in names]
    best_source=SOURCE.read_text()
    best_score=max(x.get('left',{}).get('match_percent',-1) for x in results)
try:
    for name,s in variants:
        SOURCE.write_text(s)
        build=subprocess.run(['.tools/bin/ninja','-j2',OBJ],text=True,capture_output=True)
        item={'variant':name,'source_patch':''.join(difflib.unified_diff(BASE.splitlines(True),s.splitlines(True),fromfile='baseline',tofile=name)), 'build_command':['.tools/bin/ninja','-j2',OBJ], 'build_exit':build.returncode,'build_stdout':build.stdout,'build_stderr':build.stderr}
        if build.returncode==0:
            run=subprocess.run(DIFF,text=True,capture_output=True)
            item.update(diff_command=DIFF,diff_exit=run.returncode,diff_stderr=run.stderr)
            if run.returncode==0:
                diff=json.loads(run.stdout)
                for side in ['left','right']:
                    sym=next(x for x in diff[side]['symbols'] if x['name']=='fn_800A1278')
                    item[side]={k:v for k,v in sym.items() if k!='instructions'}
                    item[side]['instructions']=[i.get('diff_kind','DIFF_NONE')+' | '+i.get('instruction',{}).get('address','0')+' | '+i.get('instruction',{}).get('formatted','<alignment gap>') for i in sym['instructions']]
                item['mismatch_counts']=dict(collections.Counter(i.get('diff_kind','DIFF_NONE') for i in sym['instructions']))
                item['object_sha256']=hashlib.sha256(Path(OBJ).read_bytes()).hexdigest()
                score=item['left']['match_percent']
                if score>best_score:
                    best_score=score
                    best_source=s
                print(name,score,item['right']['size'],item['mismatch_counts'],flush=True)
        results.append(item)
        (OUT/('experiments-'+ID+'.json')).write_text(json.dumps(results,indent=2)+'\n')
finally:
    SOURCE.write_text(best_source)
print('Best score:', best_score,flush=True)
