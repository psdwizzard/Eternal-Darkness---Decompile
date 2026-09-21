"""Reproduce bounded fn_8018DE9C experiments with unchanged canonical flags.
Run from eternal-darkness-decomp. Restores source after each invocation.
"""
import difflib
import json
from pathlib import Path
import subprocess
import sys

ASSIGNMENT = '852a86cb-79c9-494b-9358-821e592e1e73'
BASE = '4699695f625149aaf3025d960da54524af7e33ea'
SOURCE = Path('src/game/game_fn_8018DE9C.c')
REPORTS = Path('reports/GEDE01')
LOG = REPORTS / ('experiments-' + ASSIGNMENT + '.json')
base = subprocess.check_output(['git', 'show', BASE + ':eternal-darkness-decomp/' + str(SOURCE)], text=True)
variants = {
    'baseline': base,
    'indexed_scratch': base.replace('    s16* scratch;\n', '').replace('    scratch = lbl_80607900;\n', '').replace('*(u32*)scratch', '*(u32*)&lbl_80607900[i * 3]').replace('scratch[2]', 'lbl_80607900[i * 3 + 2]').replace('        scratch += 3;\n', ''),
}

indexed = variants['indexed_scratch']
variants['named_float_constants'] = indexed.replace('extern u8 lbl_80607120[];', 'extern float lbl_80650A68;\nextern float lbl_80650AB4;\nextern float lbl_80650AB8;\nextern u8 lbl_80607120[];').replace('0.0f', 'lbl_80650A68').replace('1.0f', 'lbl_80650AB4').replace('0.5f', 'lbl_80650AB8')
variants['inline_body'] = indexed.replace('void fn_8018DE9C(u8* object)', 'static inline void render_body(u8* object)') + '\nvoid fn_8018DE9C(u8* object) { render_body(object); }\n'
variants['coordinate_indexed'] = indexed.replace('    u16* coordinate;\n', '').replace('    coordinate = (u16*)transform;\n', '').replace('coordinate[7]', '((u16*)transform)[i + 7]').replace('        coordinate++;\n','')
variants['unsigned_counter'] = indexed.replace('    int i;', '    unsigned int i;').replace('(float)i', '(float)(int)i')

# Inlining changes MWCC virtual-register creation order; test the four long-lived
# declarations as a group, without changing the executable statement order.
variants['inline_reverse_buffers'] = variants['inline_body'].replace('    register u8* vertex_data;\n    register u8* index_data;\n    register u8* color_data;', '    register u8* color_data;\n    register u8* index_data;\n    register u8* vertex_data;')
variants['inline_no_register'] = variants['inline_body'].replace('register ', '')
variants['no_register'] = variants['named_float_constants'].replace('register ', '')
# A named double bias is an explicit, portable representation of signed-int to
# double conversion. It tests whether the final anonymous relocation can be removed.
variants['explicit_conversion'] = variants['named_float_constants'].replace('extern float lbl_80650A68;', 'extern double lbl_80650A70;\nextern float lbl_80650A68;').replace('        int shade;', '        int shade;\n        union { double number; struct { u32 high; u32 low; } words; } conversion;').replace('        shade = (int)((float)i', '        conversion.words.high = 0x43300000;\n        conversion.words.low = (u32)i ^ 0x80000000;\n        shade = (int)((float)(conversion.number - lbl_80650A70)')

variants['const_named_floats'] = variants['named_float_constants'].replace('extern float', 'extern const float')

def run(argv):
    p = subprocess.run(argv, text=True, capture_output=True)
    r = {'argv': argv, 'returncode': p.returncode, 'stdout': p.stdout, 'stderr': p.stderr}
    record['commands'].append(r)
    if p.returncode:
        raise RuntimeError(r)
    return p.stdout

original = SOURCE.read_text()
results = json.loads(LOG.read_text()) if LOG.exists() else {'base_commit': BASE, 'working_directory': 'eternal-darkness-decomp', 'runs': []}
try:
    name = sys.argv[1]
    candidate = variants[name]
    record = {'variant': name, 'source_diff': ''.join(difflib.unified_diff(base.splitlines(True), candidate.splitlines(True), fromfile=str(SOURCE)+' (base)', tofile=str(SOURCE)+' ('+name+')')), 'commands': []}
    SOURCE.write_text(candidate)
    run(['.tools/bin/ninja', '-t', 'commands', 'build/GEDE01/src/game/game_fn_8018DE9C.o'])
    run(['.tools/bin/ninja', '-j2', 'build/GEDE01/src/game/game_fn_8018DE9C.o'])
    for label, config in [('canonical', []), ('strict', ['-c', 'functionRelocDiffs=all'])]:
        dest = REPORTS / ('experiment-' + ASSIGNMENT + '-' + name + '-' + label + '.json')
        run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_8018DE9C', 'fn_8018DE9C', *config, '-o', str(dest), '--format', 'json'])
        data = json.loads(dest.read_text())
        left = next(s for s in data['left']['symbols'] if s['name'] == 'fn_8018DE9C')
        right = next(s for s in data['right']['symbols'] if s['name'] == 'fn_8018DE9C')
        record[label] = {'match_percent': left['match_percent'], 'target_size': left['size'], 'generated_size': right['size'], 'raw_output': 'eternal-darkness-decomp/' + str(dest)}
    print(json.dumps({k:v for k,v in record.items() if k not in ['commands', 'source_diff']}, indent=2))
finally:
    SOURCE.write_text(original)
    if 'record' in globals():
        results['runs'].append(record)
        LOG.write_text(json.dumps(results, indent=2)+'\n')
