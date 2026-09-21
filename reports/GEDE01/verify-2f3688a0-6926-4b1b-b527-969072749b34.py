"""Reproduce assignment verification without modifying compiler policy or registration.
Run from eternal-darkness-decomp with python3 reports/GEDE01/verify-....py.
"""
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess

ASSIGNMENT = '2f3688a0-6926-4b1b-b527-969072749b34'
ROOT = Path(__file__).resolve().parents[2]
REPORTS = ROOT / 'reports/GEDE01'
PREFIX = 'eternal-darkness-decomp/reports/GEDE01/'
TARGET = 'fn_800DCBC0'
UNIT = 'main/game/game_fn_800DCBC0'
SOURCE = ROOT / 'src/game/game_fn_800DCBC0.c'
MEASUREMENTS = []

def run(command):
    p = subprocess.run(command, cwd=ROOT, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    MEASUREMENTS.append({'cwd': 'eternal-darkness-decomp', 'command': command,
                         'exit_code': p.returncode, 'stdout': p.stdout, 'stderr': p.stderr})
    if p.returncode:
        raise RuntimeError(MEASUREMENTS[-1])
    return p.stdout

def text_section(path):
    data = path.read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    shoff = struct.unpack_from('>I', data, 32)[0]
    entsize, count, names_index = struct.unpack_from('>HHH', data, 46)
    sections = [struct.unpack_from('>10I', data, shoff + i * entsize) for i in range(count)]
    names_header = sections[names_index]
    names = data[names_header[4]:names_header[4] + names_header[5]]
    for header in sections:
        name = names[header[0]:].split(b'\0', 1)[0]
        if name == b'.text':
            return data[header[4]:header[4]+header[5]]
    raise ValueError('missing .text')

def relocations(output):
    rows = []
    for line in output.splitlines():
        m = re.fullmatch(r'([0-9a-f]{8})\s+[0-9a-f]{8}\s+(R_PPC_\w+)\s+([0-9a-f]{8})\s+(\S+)\s+([+-])\s+([0-9a-f]+)', line.strip())
        if m:
            offset, kind, value, name, sign, addend = m.groups()
            rows.append({'offset': int(offset, 16), 'type': kind,
                         'target_name': name, 'target_symbol_value': int(value, 16),
                         'addend': int(addend, 16) * (-1 if sign == '-' else 1)})
    return rows

run(['python3', 'configure.py'])
run(['.tools/bin/ninja', '-j2'])
compiler_command = run(['.tools/bin/ninja', '-t', 'commands', 'build/GEDE01/src/game/game_fn_800DCBC0.o'])
run(['sha256sum', 'compilers/GC/1.3/mwcceppc.exe'])
run(['build/tools/objdiff-cli', '--version'])
config = json.loads((ROOT / 'objdiff.json').read_text())
unit_config = next(u for u in config['units'] if u['name'] == UNIT)
raw_files = {}
scores = {}
for mode in ['canonical', 'reloc-strict']:
    name = f'objdiff-{ASSIGNMENT}-{mode}.raw.json'
    command = ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', UNIT, TARGET,
               '-o', 'reports/GEDE01/' + name, '--format', 'json-pretty']
    if mode == 'reloc-strict':
        command += ['-c', 'function_reloc_diffs=name_address']
    run(command)
    raw_files[mode] = PREFIX + name
    raw = json.loads((REPORTS / name).read_text())
    symbols = {side: next(s for s in raw[side]['symbols'] if s['name'] == TARGET)
               for side in ['left', 'right']}
    scores[mode] = {side: {'size': s['size'], 'match_percent': s['match_percent']}
                    for side, s in symbols.items()}

left_path = 'build/GEDE01/obj/game/game_fn_800DCBC0.o'
right_path = 'build/GEDE01/src/game/game_fn_800DCBC0.o'
relocs = {}
for side, path in [('left', left_path), ('right', right_path)]:
    output = run(['build/binutils/powerpc-eabi-readelf', '-rW', path])
    relocs[side] = relocations(output)
    assert len(relocs[side]) == 53
run(['build/binutils/powerpc-eabi-readelf', '-p', '.comment', right_path])
left = text_section(ROOT / left_path)
right = text_section(ROOT / right_path)
assert len(left) == len(right) == 1056
byte_offsets = [i for i, (a, b) in enumerate(zip(left, right)) if a != b]
word_offsets = [i for i in range(0, len(left), 4) if left[i:i+4] != right[i:i+4]]
word_differences = [{'offset': hex(i), 'retail': left[i:i+4].hex(), 'candidate': right[i:i+4].hex()}
                    for i in word_offsets]

raw = json.loads((REPORTS / f'objdiff-{ASSIGNMENT}-reloc-strict.raw.json').read_text())
def instructions(side):
    s = next(s for s in raw[side]['symbols'] if s['name'] == TARGET)
    return {int(row['instruction'].get('address', 0)): row['instruction']['formatted']
            for row in s['instructions'] if 'instruction' in row}
lhs, rhs = instructions('left'), instructions('right')
differences = [{'offset': hex(i), 'retail': lhs.get(i), 'candidate': rhs.get(i)}
               for i in sorted(lhs.keys() | rhs.keys()) if lhs.get(i) != rhs.get(i)]
dol = run(['sha1sum', 'build/GEDE01/main.dol'])
assert dol.split()[0] == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
run(['python3', 'tools/legal_audit.py'])
run(['git', 'diff', '--check', '--', 'src/game/game_fn_800DCBC0.c'])

divergence = ('Size-exact 1056-byte NonMatching reconstruction; canonical and relocation-strict objdiff '
              '99.166664%. Remaining callee-saved register allocation differences: retail context/message/phase '
              'r30/r25/r27 versus candidate r29/r30/r25; phase-1 source model and flag-difference use '
              'retail r24/r29 versus candidate r25/r24. Object r31, call/branch offsets, all 53 relocation '
              'offset/type/target/value/addend tuples, and inequality operand order agree. '
              f'{len(word_offsets)} of 264 instruction words and {len(byte_offsets)} of 1056 unrelocated .text bytes differ.')
audit = {
    'version': 1, 'assignment_id': ASSIGNMENT, 'target': TARGET,
    'source_sha256': hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
    'compiler_command_raw': compiler_command, 'objdiff_unit_config': unit_config,
    'objdiff_global_options': {k: v for k, v in config.items() if k != 'units'},
    'raw_objdiff_files': raw_files, 'measurements': MEASUREMENTS,
    'derived_summary': {
        'scores': scores, 'relocations': relocs, 'relocations_equal': relocs['left'] == relocs['right'],
        'text_bytes_equal': left == right, 'differing_byte_offsets': byte_offsets,
        'differing_words': word_differences, 'instruction_differences': differences,
        'dol_sha1': dol.split()[0], 'status': 'attempted', 'divergence': divergence,
        'dol_scope': 'The function remains NonMatching, so the verified DOL uses the retail fallback for this unit.'},
    'hypothesis': 'Reuse dead message storage for the phase-1 source pointer and dead kind storage for transition flags. '
                  'MWCC live-range coalescing, unlike register storage-class hints, changes allocation. '
                  'Reverse the pure inequality operand order to reproduce the retail subf order.',
    'semantic_review': 'The last read of the original message precedes its phase-1 source assignment. '
                       'Every use of transition flags follows kind=0x30 or kind=0x10030; dispatch kind is dead. '
                       'Both inequality operands are initialized integers without side effects. '
                       'No assembly, helper function, compiler override, or neighbor edit was introduced.'}
assert audit['derived_summary']['relocations_equal']
assert scores['canonical']['right']['match_percent'] == scores['reloc-strict']['right']['match_percent'] == 99.166664
(REPORTS / f'objdiff-{ASSIGNMENT}.json').write_text(json.dumps(audit, indent=2) + '\n')
envelope = {'version': 1, 'assignment_id': ASSIGNMENT, 'attempt': 5,
            'base_commit': '8b72cee89312a710f6ce188e205b9d1cf3be4954', 'target': TARGET,
            'status': 'attempted',
            'evidence': [PREFIX + f'objdiff-{ASSIGNMENT}.json', *raw_files.values(),
                         PREFIX + f'trials-{ASSIGNMENT}.json', PREFIX + f'verify-{ASSIGNMENT}.py'],
            'divergence': divergence}
(REPORTS / f'durable-{ASSIGNMENT}.json').write_text(json.dumps(envelope, indent=2) + '\n')
print(json.dumps(audit['derived_summary']['scores'], indent=2))
print(divergence)
print(dol, end='')
