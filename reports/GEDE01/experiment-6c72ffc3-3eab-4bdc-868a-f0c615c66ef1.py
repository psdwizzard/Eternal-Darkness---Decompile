"""Assignment-only reproducible local-aggregate scalar-replacement experiments.
Run from eternal-darkness-decomp; restores the single original C source.
"""
import itertools
import json
from pathlib import Path
import subprocess
import time

ID = '6c72ffc3-3eab-4bdc-868a-f0c615c66ef1'
REPORTS = Path('reports/GEDE01')
SOURCE = Path('src/game/game_fn_80120B58.c')
OBJECT = 'build/GEDE01/src/game/game_fn_80120B58.o'
BASELINE = SOURCE.read_text()
LOG = {'assignment_id': ID, 'hypothesis': 'Local aggregate scalar replacement may create a different virtual-FPR ordering from separate scalar temporaries, without changing canonical compiler settings.', 'commands': [], 'variants': []}

def run(argv):
    started = time.time()
    p = subprocess.run(argv, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    record = {'cwd': 'eternal-darkness-decomp', 'argv': argv, 'exit_code': p.returncode, 'stdout': p.stdout, 'stderr': p.stderr, 'elapsed_seconds': time.time() - started}
    LOG['commands'].append(record)
    if p.returncode:
        raise RuntimeError(record)
    return p.stdout

def save():
    (REPORTS / ('variants-' + ID + '.json')).write_text(json.dumps(LOG, indent=2) + '\n')

def measure(name, source):
    SOURCE.write_text(source)
    start = len(LOG['commands'])
    run(['.tools/bin/ninja', '-j2', OBJECT])
    raw = run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_80120B58', 'fn_80120B58', '-o', '-', '--format', 'json'])
    result = json.loads(raw)
    symbol = next(s for s in result['left']['symbols'] if s['name'] == 'fn_80120B58')
    LOG['variants'].append({'name': name, 'source': source, 'command_indices': list(range(start, len(LOG['commands']))), 'match_percent': symbol['match_percent'], 'retail_size': symbol['size'], 'generated_size': next(s['size'] for s in result['right']['symbols'] if s['name'] == 'fn_80120B58')})
    save()
    print(name, symbol['match_percent'], flush=True)

try:
    run(['python3', 'configure.py'])
    run(['.tools/bin/ninja', '-t', 'commands', OBJECT])
    run(['build/tools/objdiff-cli', '--version'])
    measure('baseline', BASELINE)
    for representation in ['struct', 'array']:
        for order in itertools.permutations(['value', 'step', 'bound']):
            source = BASELINE
            for step, bound, expr in [('decrement', 'minimum', 'object->decrement'), ('increment', 'maximum', 'lbl_806500C4')]:
                old = f'        float value = object->value;\n        float {step} = {expr};\n        float {bound} = ' + ('lbl_806500A0;' if step == 'decrement' else 'lbl_806500C8;')
                if representation == 'struct':
                    declaration = '        struct { ' + ' '.join('float '+x+';' for x in order) + ' } locals;\n'
                    fields = {x: 'locals.'+x for x in order}
                else:
                    declaration = '        float locals[3];\n'
                    fields = {x: f'locals[{order.index(x)}]' for x in order}
                replacement = declaration + f'        {fields["value"]} = object->value;\n        {fields["step"]} = {expr};\n        {fields["bound"]} = ' + ('lbl_806500A0;' if step == 'decrement' else 'lbl_806500C8;')
                source = source.replace(old, replacement)
                source = source.replace(f'value {"-" if step == "decrement" else "+"} {step}', f'{fields["value"]} {"-" if step == "decrement" else "+"} {fields["step"]}')
                source = source.replace('<= '+bound, '<= '+fields['bound']).replace(bound+' ==', fields['bound']+' ==').replace('= '+bound+';', '= '+fields['bound']+';')
            measure(representation+'_'+'_'.join(order), source)
finally:
    SOURCE.write_text(BASELINE)
    run(['.tools/bin/ninja', '-j2', OBJECT])
    save()
