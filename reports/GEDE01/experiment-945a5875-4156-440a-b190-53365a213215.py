"""Run from eternal-darkness-decomp; preserve an exact source experiment and raw evidence."""
import difflib
import hashlib
import json
from pathlib import Path
import subprocess

ID = '945a5875-4156-440a-b190-53365a213215'
REPORT = Path('reports/GEDE01')
SOURCE = Path('src/game/game_fn_8017B4F4.c')
OBJ = 'build/GEDE01/src/game/game_fn_8017B4F4.o'
RETAIL = 'build/GEDE01/obj/game/game_fn_8017B4F4.o'
UNIT = 'main/game/game_fn_8017B4F4'

def run(args):
    p = subprocess.run(args, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    r = dict(command=args, cwd='eternal-darkness-decomp', exit_code=p.returncode,
             stdout=p.stdout, stderr=p.stderr)
    return r

def inspect(label):
    out = {}
    for kind, extra in [('canonical', []), ('relocation_strict', ['-c', 'function_reloc_diffs=name_address'])]:
        dest = 'build/GEDE01/' + ID + '-' + label + '-' + kind + '.json'
        result = run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', UNIT,
                      '-o', dest, '--format', 'json-pretty'] + extra)
        if result['exit_code'] == 0:
            result['raw_result'] = json.loads(Path(dest).read_text())
        out[kind] = result
    out['symbols_relocations'] = run(['build/binutils/powerpc-eabi-readelf', '-sWr', OBJ])
    out['disassembly'] = run(['build/binutils/powerpc-eabi-objdump', '-dr', OBJ])
    return out

baseline = SOURCE.read_text()
variant = baseline.replace('float fn_8017B4F4', '''extern double lbl_80650910;
/* Big-endian IEEE-754 bias conversion, expressed through C storage. */
#define INT_AS_FLOAT(v, bits) \\
    ((bits).words[0] = 0x43300000U, \\
     (bits).words[1] = (unsigned int)(v) ^ 0x80000000U, \\
     (float)((bits).number - lbl_80650910))

float fn_8017B4F4''').replace('    int base;','''    int base;
    union { unsigned int words[2]; double number; } elapsed_bits, base_bits;''')
variant = variant.replace('(float)elapsed', 'INT_AS_FLOAT(elapsed, elapsed_bits)').replace('(float)base', 'INT_AS_FLOAT(base, base_bits)')
variant = variant.replace('value = fn_8017B8AC();','value = INT_AS_FLOAT(fn_8017B8AC(), elapsed_bits);').replace('value = fn_8017B904();','value = INT_AS_FLOAT(fn_8017B904(), elapsed_bits);')
out = dict(version=1, assignment_id=ID, target='fn_8017B4F4',
           hypothesis='Explicit union-based bias conversion referencing external lbl_80650910 can remove synthesized conversion-literal relocations while retaining the signed-conversion instruction sequence. This actively replaces each conversion, unlike the previously discarded unused constant seed.',
           baseline_source_sha256=hashlib.sha256(baseline.encode()).hexdigest(),
           baseline_source=baseline,
           experimental_source=variant,
           experimental_patch=''.join(difflib.unified_diff(baseline.splitlines(True), variant.splitlines(True), fromfile=str(SOURCE), tofile=str(SOURCE))))
try:
    SOURCE.write_text(variant)
    out['experimental_build'] = run(['.tools/bin/ninja', '-j2', '-v', OBJ])
    if out['experimental_build']['exit_code'] == 0:
        out['experiment'] = inspect('experiment')
finally:
    SOURCE.write_text(baseline)
    out['restored_build'] = run(['.tools/bin/ninja', '-j2', '-v', OBJ])
out['final'] = inspect('final')
out['retail_symbols_relocations'] = run(['build/binutils/powerpc-eabi-readelf', '-sWr', RETAIL])
out['retail_disassembly'] = run(['build/binutils/powerpc-eabi-objdump', '-dr', RETAIL])
out['text_comparison'] = []
for label, obj in [('retail', RETAIL), ('generated', OBJ)]:
    dest = 'build/GEDE01/' + ID + '-' + label + '.text'
    out['text_comparison'].append(run(['build/binutils/powerpc-eabi-objcopy', '-O', 'binary', '--only-section=.text', obj, dest]))
    data = Path(dest).read_bytes()
    out['text_comparison'].append(dict(label=label, size=len(data), sha256=hashlib.sha256(data).hexdigest()))
out['text_comparison'].append(run(['cmp', 'build/GEDE01/'+ID+'-retail.text', 'build/GEDE01/'+ID+'-generated.text']))
out['configure'] = run(['python3', 'configure.py'])
out['final_build'] = run(['.tools/bin/ninja', '-j2'])
out['dol_sha1'] = run(['sha1sum', 'build/GEDE01/main.dol', 'orig/GEDE01/sys/main.dol'])
out['legal_audit'] = run(['python3', 'tools/legal_audit.py'])
(REPORT / ('objdiff-' + ID + '.json')).write_text(json.dumps(out, indent=2)+'\n')
for label in ['experiment','final']:
    for kind in ['canonical','relocation_strict']:
        result = out.get(label,{}).get(kind,{})
        syms = result.get('raw_result',{}).get('left',{}).get('symbols',[])
        print(label, kind, [(s['name'],s.get('size'),s.get('match_percent')) for s in syms if s['name']=='fn_8017B4F4'])
print(out['dol_sha1'])
print(out['legal_audit'])
