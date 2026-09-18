"""Run from eternal-darkness-decomp; writes only assignment-local evidence.

Variant patches apply with git apply from the workspace root at the accepted
base commit 9b2d1399073021f018e13bdbd999e0f255c8bfda.
"""
import difflib
import hashlib
import json
import pathlib
import subprocess

AID = 'e11b057e-69b6-4c87-b03b-7732ad8af301'
OUT = pathlib.Path('reports/GEDE01') / AID
SOURCE = pathlib.Path('src/game/game_fn_801A82FC.c')
GIT_SOURCE = 'eternal-darkness-decomp/' + str(SOURCE)
BASE = '9b2d1399073021f018e13bdbd999e0f255c8bfda'
baseline = subprocess.check_output(['git', 'show', BASE + ':' + GIT_SOURCE], text=True)
original_source = SOURCE.read_text()
records = []

def run(args, log):
    p = subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    (OUT / log).write_text(p.stdout)
    records.append({'cwd': 'eternal-darkness-decomp', 'argv': args,
                    'exit_code': p.returncode, 'raw_output': str(OUT / log)})
    (OUT / 'commands.json').write_text(json.dumps(records, indent=2) + '\n')
    if p.returncode:
        raise RuntimeError(p.stdout)
    return p.stdout

variants = {'baseline': baseline}
variants['recovered4_signed_offset'] = baseline.replace('u32 offset = 0;', 'int offset = 0;')
variants['recovered4_unsigned_both'] = baseline.replace('int index = 0;', 'u32 index = 0;')
variants['recovered5_register_offset'] = baseline.replace('u32 offset = 0;', 'register u32 offset = 0;')
variants['recovered5_register_index'] = baseline.replace('int index = 0;', 'register int index = 0;')
variants['recovered5_register_both'] = variants['recovered5_register_offset'].replace('int index = 0;', 'register int index = 0;')
variants['recovered5_for_loop'] = baseline.replace('u32 offset = 0;\n            int index = 0;\n\n            while (index < buffer->count) {', 'u32 offset;\n            int index;\n\n            for (offset = 0, index = 0; index < buffer->count;\n                 offset += 0x74, index++) {').replace('                offset += 0x74;\n                index++;\n', '')
variants['new_typed_records'] = baseline.replace('typedef struct Buffer801A82FC {', 'typedef struct Record801A82FC {\n    u8 pad[0x2C];\n    u32 key;\n    u8 rest[0x44];\n} Record801A82FC;\n\ntypedef struct Buffer801A82FC {').replace('void* data;', 'Record801A82FC* data;').replace('            u32 offset = 0;\n', '').replace('*(u32*)((u8*)buffer->data + offset + 0x2C)', 'buffer->data[index].key').replace('(u8*)buffer->data + index * 0x74', '&buffer->data[index]').replace('                offset += 0x74;\n', '')
variants['new_word_index'] = baseline.replace('*(u32*)((u8*)buffer->data + offset + 0x2C)', '((u32*)buffer->data)[offset + 0xB]').replace('offset += 0x74;', 'offset += 0x1D;')
variants['new_field_first_address'] = baseline.replace('(u8*)buffer->data + offset + 0x2C', '(u8*)buffer->data + 0x2C + offset')
variants['new_commuted_address'] = baseline.replace('(u8*)buffer->data + offset + 0x2C', 'offset + (u8*)buffer->data + 0x2C')

try:
    run(['python3', 'configure.py'], 'configure.log')
    cfg = json.loads(pathlib.Path('objdiff.json').read_text())
    unit = next(u for u in cfg['units'] if u['name'] == 'main/game/game_fn_801A82FC')
    (OUT / 'configuration.json').write_text(json.dumps({'base_commit': BASE, 'baseline_sha256': hashlib.sha256(baseline.encode()).hexdigest(), 'unit': unit, 'canonical_config': {}, 'strict_config': {'function_reloc_diffs': 'name_address'}}, indent=2) + '\n')
    for name, source in variants.items():
        patch = ''.join(difflib.unified_diff(baseline.splitlines(True), source.splitlines(True), fromfile='a/'+GIT_SOURCE, tofile='b/'+GIT_SOURCE))
        (OUT / (name + '.patch')).write_text(patch)
        SOURCE.write_text(source)
        run(['.tools/bin/ninja', '-j2', 'build/GEDE01/src/game/game_fn_801A82FC.o'], name + '-build.log')
        for mode in ['canonical', 'strict']:
            args = ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', unit['name'], 'fn_801A82FC', '-o', str(OUT / (name + '-' + mode + '.json')), '--format', 'json-pretty']
            if mode == 'strict':
                args += ['-c', 'function_reloc_diffs=name_address']
            run(args, name + '-' + mode + '.log')
        data = json.loads((OUT / (name + '-strict.json')).read_text())
        print(name, [(s.get('name'), s.get('match_percent'), s.get('size')) for s in data['left']['symbols'] if s.get('name') == 'fn_801A82FC'], flush=True)
finally:
    SOURCE.write_text(original_source)
