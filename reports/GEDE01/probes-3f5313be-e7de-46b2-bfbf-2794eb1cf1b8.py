"""Run from eternal-darkness-decomp; preserves exact source and raw measurements."""
import json
import subprocess
import hashlib
from pathlib import Path

AID = '3f5313be-e7de-46b2-bfbf-2794eb1cf1b8'
ROOT = Path('.')
SOURCE = Path('src/game/game_fn_8018CB70.c')
REPORT = Path(f'reports/GEDE01/probes-{AID}.json')
BASELINE = subprocess.check_output(['git', 'show', 'a30aee164a819a82b55a1c12054d4ce793a39d09:eternal-darkness-decomp/src/game/game_fn_8018CB70.c'], text=True)
results = []

def run(args):
    p = subprocess.run(args, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    return {'command': args, 'cwd': 'eternal-darkness-decomp', 'exit_code': p.returncode, 'raw_output': p.stdout}

def probe(name, source, hypothesis):
    SOURCE.write_text(source)
    entry = {'name': name, 'hypothesis': hypothesis, 'source': source, 'commands': []}
    results.append(entry)
    entry['commands'].append(run(['.tools/bin/ninja', '-j2', 'build/GEDE01/src/game/game_fn_8018CB70.o']))
    if entry['commands'][-1]['exit_code'] == 0:
        out = f'reports/GEDE01/.probe-{AID}.json'
        entry['commands'].append(run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_8018CB70', '-o', out, '--format', 'json', '-c', 'function_reloc_diffs=name_address', 'fn_8018CB70']))
        entry['objdiff'] = json.loads(Path(out).read_text())
        Path(out).unlink()
        syms = [s for s in entry['objdiff']['left']['symbols'] if s['name'] == 'fn_8018CB70']
        entry['score'] = syms[0].get('match_percent')
        entry['object_sha256'] = hashlib.sha256(Path('build/GEDE01/src/game/game_fn_8018CB70.o').read_bytes()).hexdigest()
        entry['commands'].append(run(['build/binutils/powerpc-eabi-objdump', '-dr', 'build/GEDE01/src/game/game_fn_8018CB70.o']))
        print(name, entry['score'], flush=True)
    REPORT.write_text(json.dumps({'assignment_id': AID, 'probes': results}, indent=2) + '\n')

try:
    probe('baseline', BASELINE, 'Reproduce retained NonMatching reconstruction under canonical flags.')
    stores = '\n'.join(f'            *dest++ = {v};' for v in ['0x200','0x200','0','0x200','0','0','0x200','0'])
    begin = BASELINE.index('            dest[0]')
    end = BASELINE.index('            dest += 8;') + len('            dest += 8;')
    probe('sequential_postincrement', BASELINE[:begin] + stores + BASELINE[end:], 'Sequential advancing stores may change pointer induction lowering and allocator interference while folding to the same store offsets.')
    probe('inner_postincrement_test', BASELINE.replace('int i;\n        for (i = 0; i < length; i++) {', 'int i = 0;\n        while (i++ < length) {'), 'The induction value is unused by stores; moving its increment into the test may change loop canonicalization and lifetime of the invariant bound.')
    probe('outer_do_while', BASELINE.replace('int group;', 'int group = 0;').replace('for (group = 0; group < 2; group++) {', 'do {').replace('        dest = second;\n    }', '        dest = second;\n    } while (++group < 2);'), 'Express the guaranteed two outer iterations directly as do/while to change preheader construction without changing store behavior.')
    probe('outer_update_expression', BASELINE.replace('group++) {', 'group++, dest = second) {').replace('        dest = second;\n', ''), 'Move the pointer reset to the outer-loop update expression to change the latch IR feeding pointer allocation.')
    probe('inner_inclusive_bound', BASELINE.replace('i < length;', 'i <= (int)length - 1;'), 'Equivalent inclusive trip-count expression introduces count-minus-one before unrolling; this differs from manually introducing the prior count-minus-eight bound.')
finally:
    SOURCE.write_text(BASELINE)
