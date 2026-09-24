"""Reproduce assignment 625a7dba candidates; retains original source on exit."""
import difflib, json, subprocess
from pathlib import Path
root = Path(__file__).resolve().parents[2]
report = root / 'reports/GEDE01'
aid = '625a7dba-c44c-421d-8849-f453fcdeb340'
source = root / 'src/game/game_fn_80198C8C.c'
original = subprocess.check_output(['git','show','f348aa68c2399fe240db271e700a4f09fbde6697:eternal-darkness-decomp/src/game/game_fn_80198C8C.c'],text=True,cwd=root)
restore = source.read_text()
variants = {'baseline': original}
variants['wide-half-late-narrow'] = original.replace('u8 half;', 'int half;').replace('i < half;', 'i < (u8)half;').replace('half * 0x38', '(u8)half * 0x38')
variants['level-declared-first'] = original.replace('u8 half;\n            u8 level;', 'u8 level;\n            u8 half;')
variants['quotient-before-half'] = original.replace('u8* p;','u8* p;\n            int bands;').replace('half = count >> 1;', 'bands = (value - 150) / step;\n            half = count >> 1;').replace('(step / 2) * ((value - 150) / step)', '(step / 2) * bands')
variants['difference-before-half'] = original.replace('u8* p;', 'u8* p;\n            int difference;').replace('half = count >> 1;', 'difference = value - 150;\n            half = count >> 1;').replace('((value - 150) / step)', '(difference / step)')
variants['wide-level-store-narrow'] = original.replace('u8 level;', 'int level;')
ordered = variants['level-declared-first']
half = '            half = count >> 1;\n'
level = '            level = (step / 2) * ((value - 150) / step) + 60;\n'
store = '            entry[1] = kind;\n            entry[5] = step;\n'
variants['ordered-level-first'] = ordered.replace(half+level,level+half)
variants['ordered-half-after-stores'] = ordered.replace(half,'').replace(store,store+half)
variants['ordered-stores-before-level'] = ordered.replace(store,'').replace(level,store+level)
variants['ordered-stores-before-both'] = ordered.replace(store,'').replace(half,store+half)
variants['ordered-product-first'] = ordered.replace('(step / 2) * ((value - 150) / step)', '((value - 150) / step) * (step / 2)')
variants['ordered-split-narrow'] = ordered.replace('u8* p;', 'u8* p;\n            int raw_level;').replace(half+level,'            raw_level = (step / 2) * ((value - 150) / step) + 60;\n'+half+'            level = raw_level;\n')
variants['ordered-split-product'] = ordered.replace('u8* p;', 'u8* p;\n            int product;').replace(half+level,'            product = (step / 2) * ((value - 150) / step);\n'+half+'            level = product + 60;\n')
variants['ordered-half-divide'] = ordered.replace('count >> 1', 'count / 2')
variants['ordered-split-difference'] = ordered.replace('u8* p;', 'u8* p;\n            int difference;').replace(half, '            difference = value - 150;\n'+half).replace('((value - 150) / step)', '(difference / step)')
variants['ordered-int-count'] = ordered.replace('u8 count =', 'int count =')
variants['ordered-uint-count'] = ordered.replace('u8 count =', 'unsigned int count =')
variants['ordered-add-first'] = ordered.replace('(step / 2) * ((value - 150) / step) + 60', '60 + (step / 2) * ((value - 150) / step)')
variants['ordered-negative-offset'] = ordered.replace('(value - 150)', '(value + -150)')
variants['ordered-half-assignment-shift'] = ordered.replace('half = count >> 1;', 'half = count;\n            half >>= 1;')
variants['ordered-separate-level-add'] = ordered.replace(' + 60;', ';\n            level += 60;')
variants['ordered-signed-half'] = ordered.replace('u8 half;', 's8 half;')
variants['ordered-count-local-half'] = ordered.replace(half, '            half = object[1] >> 1;\n')
variants['ordered-split-division'] = ordered.replace('u8* p;', 'u8* p;\n            int bands;\n            int half_step;').replace(level, '            bands = (value - 150) / step;\n            half_step = step / 2;\n            level = half_step * bands + 60;\n')
variants['ordered-split-division-interleave'] = variants['ordered-split-division'].replace(half, '').replace('            half_step =', half+'            half_step =')
variants['ordered-split-division-stores'] = variants['ordered-split-division-interleave'].replace(store, '').replace('            level =', store+'            level =')
nohalf = ordered.replace(half, '')
variants['ordered-comma-step'] = nohalf.replace('(step / 2)', '((half = count >> 1), step / 2)')
variants['ordered-comma-bands'] = nohalf.replace('((value - 150) / step)', '((half = count >> 1), (value - 150) / step)')
variants['ordered-comma-add'] = nohalf.replace(' + 60;', ' + ((half = count >> 1), 60);')
variants['ordered-half-wide-intermediate'] = ordered.replace('u8* p;', 'u8* p;\n            int half_count;').replace(half, '            half_count = count >> 1;\n').replace(level, level+'            half = half_count;\n')
variants['ordered-half-wide-before-stores'] = ordered.replace('u8* p;', 'u8* p;\n            int half_count;').replace(half, '            half_count = count >> 1;\n').replace(store, store+'            half = half_count;\n')
variants['ordered-half-middle-product'] = ordered.replace('u8* p;', 'u8* p;\n            int bands;').replace(half+level, '            bands = (value - 150) / step;\n'+half+'            level = bands * (step / 2) + 60;\n')
records=[]
def run(cmd):
    p=subprocess.run(cmd,cwd=root,text=True,capture_output=True)
    rec={'cwd':'eternal-darkness-decomp','argv':cmd,'returncode':p.returncode,'stdout':p.stdout,'stderr':p.stderr}
    records.append(rec)
    if p.returncode: raise RuntimeError(rec)
    return p.stdout
try:
    for name,text in variants.items():
        source.write_text(text)
        patch=''.join(difflib.unified_diff(original.splitlines(True),text.splitlines(True),fromfile='base/src/game/game_fn_80198C8C.c',tofile=name+'/src/game/game_fn_80198C8C.c'))
        records.append({'variant':name,'source_patch':patch})
        run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80198C8C.o'])
        output=f'reports/GEDE01/experiment-{aid}-{name}.json'
        run(['build/tools/objdiff-cli','diff','-1','build/GEDE01/obj/game/game_fn_80198C8C.o','-2','build/GEDE01/src/game/game_fn_80198C8C.o','-c','function_reloc_diffs=name_address','--format','json','-o',output,'fn_80198C8C'])
        data=json.loads((root/output).read_text())
        sym=next(s for s in data['left']['symbols'] if s['name']=='fn_80198C8C')
        print(name,sym.get('match_percent'),flush=True)
finally:
    source.write_text(restore)
    run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_80198C8C.o'])
    (report/f'experiments-{aid}.json').write_text(json.dumps(records,indent=2)+'\n')
