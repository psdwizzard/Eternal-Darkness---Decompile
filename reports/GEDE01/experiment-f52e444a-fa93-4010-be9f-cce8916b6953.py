"""Run assignment-local variants using only canonical Ninja compile commands.
Run from eternal-darkness-decomp. Restores the baseline even after a failure.
"""
import difflib
import json
from pathlib import Path
import subprocess

ASSIGNMENT = 'f52e444a-fa93-4010-be9f-cce8916b6953'
ROOT = Path('reports/GEDE01')
SOURCE = Path('src/game/game_fn_800D3620.c')
BASE = '8cda957d20d6e590dd58d647abca8c1911c9c6bc'
TARGET = 'build/GEDE01/src/game/game_fn_800D3620.o'
OUT = ROOT / ('experiments-' + ASSIGNMENT + '.json')
baseline = subprocess.check_output(['git', 'show', BASE + ':eternal-darkness-decomp/' + str(SOURCE)], text=True)
records = []

def run(args):
    p = subprocess.run(args, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return dict(argv=args, cwd='eternal-darkness-decomp', exit_code=p.returncode, stdout=p.stdout, stderr=p.stderr)

def measure(name, source, hypothesis):
    SOURCE.write_text(source)
    rec = dict(name=name, hypothesis=hypothesis,
               patch=''.join(difflib.unified_diff(baseline.splitlines(True), source.splitlines(True), fromfile=str(SOURCE), tofile=str(SOURCE))),
               source=source, commands=[])
    records.append(rec)
    rec['commands'].append(run(['.tools/bin/ninja', '-j2', '-v', TARGET]))
    if rec['commands'][-1]['exit_code'] == 0:
        for setting in ['canonical', 'strict']:
            args=['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_800D3620', 'fn_800D3620', '--format', 'json', '-o', str(ROOT / ('raw-' + ASSIGNMENT + '.json'))]
            if setting == 'strict': args += ['-c', 'function_reloc_diffs=name_address']
            result=run(args)
            rec['commands'].append(result)
            if result['exit_code'] == 0:
                raw=json.loads((ROOT / ('raw-' + ASSIGNMENT + '.json')).read_text())
                (ROOT / ('raw-' + ASSIGNMENT + '.json')).unlink()
                result['raw_json']=raw
                symbol=next(s for s in raw['left']['symbols'] if s['name']=='fn_800D3620')
                other=next(s for s in raw['right']['symbols'] if s['name']=='fn_800D3620')
                rec[setting]=dict(score=symbol.get('match_percent'),retail_size=symbol['size'],generated_size=other['size'])
        print(name, rec.get('strict'), flush=True)
    else: print(name, rec['commands'][-1], flush=True)
    OUT.write_text(json.dumps(dict(assignment_id=ASSIGNMENT, baseline_commit=BASE, experiments=records), indent=2)+'\n')

if __name__ == '__main__':
    try:
        measure('baseline', baseline, 'Reproduce accepted scalar candidate.')
        for params in ['state', 'object', 'both']:
            s=baseline
            if params in ['state','both']: s=s.replace('fn_800D3620(void *state', 'fn_800D3620(register void *state')
            if params in ['object','both']: s=s.replace(', void *object)', ', register void *object)')
            measure('register-parameter-'+params,s,'Explicit incoming parameter register priority may prevent object/value coalescing and assign state to r31.')
        s=baseline.replace('fn_800D3620(void *state, void *object)', 'fn_800D3620(register void *state, register void *object)')
        s=s.replace('    void *resource =', '    register void *resource =').replace('    int value =', '    register int value =').replace('    int id =', '    register int id =')
        measure('register-parameters-and-locals',s,'Prior local-only register experiment omitted incoming parameters; qualify all scalar lifetimes.')
        s=baseline.replace('    int id = fn_80201B54(object);', '').replace('    Vec3 second;', '    Vec3 second;\n\n    object = (void *)fn_80201B54(object);').replace(', id, value,', ', (int)object, value,')
        measure('historical-overwrite-object-reproduction',s,'Historical control only: reproduce attempt 4 with exact source and raw comparisons to repair the review evidence gap, not a new hypothesis.')
        calls='    fn_8020123C(157, id, value, &second);\n    fn_8020123C(160, id, value, 0);'
        s=baseline.replace('    Vec3 first;', '    int event;\n    Vec3 first;').replace(calls, '    for (event = 157; event <= 160; event += 3) {\n        fn_8020123C(event, id, value, event == 157 ? &second : 0);\n    }')
        measure('bounded-event-loop',s,'Two event calls may originate from an unrolled bounded loop, changing allocation costs and object/value coalescing.')
        s=baseline.replace('    Vec3 first;', '    int event;\n    Vec3 first;').replace(calls, '    for (event = 0; event < 2; ++event) {\n        fn_8020123C(157 + 3 * event, id, value, event == 0 ? &second : 0);\n    }')
        measure('bounded-event-index-loop',s,'Zero-based equivalent tests whether O4 recognizes and unrolls two event iterations.')
        s=baseline.replace('extern void* fn_80201B94();','extern void* fn_80201B94(void *);').replace('extern int fn_80201B54();','extern int fn_80201B54(void *);').replace('extern void fn_8011F114();','extern void fn_8011F114(Vec3 *, void *);').replace('extern unsigned long long fn_8020123C();','extern unsigned long long fn_8020123C(int, int, int, Vec3 *);')
        measure('fully-prototyped-calls',s,'Complete prototypes can alter MWCC call IR and allocation even with identical integer ABI.')
    finally:
        SOURCE.write_text(baseline)
