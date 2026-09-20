"""Reproduce bounded constant-folding experiments; run from project root."""
from pathlib import Path
import hashlib, json, subprocess

ROOT = Path.cwd()
OUT = ROOT / 'reports/GEDE01/b2ce7d09-cb0d-47ee-91b3-fdc67aacfab6'
SRC = ROOT / 'src/game/game_fn_80129D54.c'
original = SRC.read_text()
empty_case = 'case 1:\n            break;'
variants = {
    'baseline': None,
    'case_do_zero': 'case 1:\n            do { } while (0);\n            break;',
    'case_do_break': 'case 1:\n            do { break; } while (1);\n            break;',
    'case_while_break': 'case 1:\n            while (1) { break; }\n            break;',
    'case_nested_constant_switch': 'case 1:\n            switch (1) { case 1: break; default: break; }\n            break;',
    'case_nested_same_switch': 'case 1:\n            switch (current->kind) { case 1: break; default: break; }\n            break;',
    'case_if_both_break': 'case 1:\n            if (current->kind) break; else break;',
    'case_zero_trip_call': 'case 1:\n            while (0) { fn_801287C4(owner, fn_801A9FA4, (unsigned short)current->value, current->packed >> 17); }\n            break;',
    'case_local_constant_loop': 'case 1: {\n            int once = 1;\n            while (once) { once = 0; }\n            break;\n        }',
}
results = []
def run(cmd, log):
    p = subprocess.run(cmd, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    log.write('$ ' + ' '.join(cmd) + '\n' + p.stdout + '\nexit_code=' + str(p.returncode) + '\n')
    log.flush()
    p.check_returncode()
try:
    with (OUT / 'hypotheses.log').open('w') as log:
        for name, replacement in variants.items():
            source = original if replacement is None else original.replace(empty_case, replacement)
            assert source != original or name == 'baseline'
            SRC.write_text(source)
            run(['.tools/bin/ninja', '-j2', 'build/GEDE01/src/game/game_fn_80129D54.o'], log)
            output = OUT / (name + '.json')
            run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_80129D54', 'fn_80129D54', '-o', str(output.relative_to(ROOT)), '--format', 'json'], log)
            data = json.loads(output.read_text())
            symbol = next(s for s in data['left']['symbols'] if s['name']=='fn_80129D54')
            right = next(s for s in data['right']['symbols'] if s['name']=='fn_80129D54')
            result = {'name': name, 'replacement': replacement, 'source_sha256': hashlib.sha256(source.encode()).hexdigest(), 'canonical_percent': symbol['match_percent'], 'retail_bytes': symbol['size'], 'generated_bytes': right['size'], 'raw_objdiff': str(output.relative_to(ROOT))}
            results.append(result)
            print(json.dumps(result), flush=True)
            (OUT / 'hypotheses-results.json').write_text(json.dumps(results, indent=2)+'\n')
finally:
    SRC.write_text(original)
