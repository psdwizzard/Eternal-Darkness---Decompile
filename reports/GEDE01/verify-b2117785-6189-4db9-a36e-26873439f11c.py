"""Run from eternal-darkness-decomp after the canonical Matching build."""
import collections
import hashlib
import json
from pathlib import Path
import struct
import subprocess

ASSIGNMENT = 'b2117785-6189-4db9-a36e-26873439f11c'
TARGET = 'fn_80050B08'
REPORTS = Path('reports/GEDE01')
PREFIX = 'eternal-darkness-decomp/'


def run(args):
    result = subprocess.run(args, check=True, text=True, capture_output=True)
    return result.stdout


def elf_text(path):
    data = path.read_bytes()
    offset = struct.unpack_from('>I', data, 32)[0]
    entsize, count, names_index = struct.unpack_from('>HHH', data, 46)
    sections = [struct.unpack_from('>10I', data, offset + i * entsize) for i in range(count)]
    names = sections[names_index]
    strings = data[names[4]:names[4] + names[5]]
    for section in sections:
        name = strings[section[0]:strings.find(b'\0', section[0])]
        if name == b'.text':
            return data[section[4]:section[4] + section[5]]
    raise AssertionError('missing .text')


def relocations(path):
    raw = run(['build/binutils/powerpc-eabi-readelf', '-rW', str(path)])
    rows = []
    for line in raw.splitlines():
        fields = line.split()
        if len(fields) >= 7 and fields[2].startswith('R_PPC_'):
            rows.append([fields[0], fields[2], fields[4], fields[5], fields[6]])
    # Symbol-table indexes and the unused st_value of undefined symbols are not
    # relocation targets/addends. Preserve raw readelf output as well as these
    # normalized offset/type/name/addend records.
    return raw, rows


summaries = {}
raw_files = []
for mode, options in [('canonical', []), ('reloc-strict', ['-c', 'function_reloc_diffs=name_address'])]:
    output = REPORTS / f'objdiff-{ASSIGNMENT}-{mode}.raw.json'
    run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_80050B08', TARGET,
         '-o', str(output), '--format', 'json', *options])
    raw_files.append(PREFIX + str(output))
    result = json.loads(output.read_text())
    left, right = [next(s for s in result[side]['symbols'] if s['name'] == TARGET)
                   for side in ('left', 'right')]
    differences = collections.Counter(row['diff_kind'] for row in left['instructions']
                                     if row.get('diff_kind') not in (None, 'DIFF_NONE'))
    summaries[mode] = {'target_bytes': int(left['size']), 'generated_bytes': int(right['size']),
                       'match_percent': left['match_percent'],
                       'aligned_instruction_rows': len(left['instructions']),
                       'differing_rows': sum(differences.values()), 'diff_kinds': dict(differences)}
    assert left['match_percent'] == 100.0 and not differences

objects = [Path('build/GEDE01/obj/game/game_fn_80050B08.o'),
           Path('build/GEDE01/src/game/game_fn_80050B08.o')]
texts = [elf_text(path) for path in objects]
assert texts[0] == texts[1] and len(texts[0]) == 5904
relocs = [relocations(path) for path in objects]
assert relocs[0][1] == relocs[1][1] and len(relocs[0][1]) == 75
sha1 = run(['sha1sum', 'build/GEDE01/main.dol'])
assert sha1.split()[0] == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
legal = run(['python3', 'tools/legal_audit.py'])
build_log = Path('build/GEDE01/b2117785-matching-build.log').read_text()
assert 'build/GEDE01/main.dol: OK' in build_log
assert 'EXTERNALIZE JUMPTABLES build/GEDE01/src/game/game_fn_80050B08.o' in build_log
build_report = REPORTS / f'build-{ASSIGNMENT}.log'
build_report.write_text(build_log)

report = {
    'version': 1, 'assignment_id': ASSIGNMENT, 'attempt': 6, 'target': TARGET,
    'compiler': 'Canonical GC/1.3 configuration, -O4,p, -use_lmw_stmw on; unchanged compiler policy',
    'commands': ['python3 configure.py', '.tools/bin/ninja -j2 > build/GEDE01/b2117785-matching-build.log 2>&1',
                 f'python3 reports/GEDE01/verify-{ASSIGNMENT}.py'],
    'objdiff_raw_files': raw_files,
    'canonical_objdiff_raw': summaries['canonical'],
    'relocation_strict_objdiff_raw': summaries['reloc-strict'],
    'text_byte_verification': {'bytes_equal': True, 'bytes': len(texts[0]),
                               'target_sha1': hashlib.sha1(texts[0]).hexdigest(),
                               'generated_sha1': hashlib.sha1(texts[1]).hexdigest()},
    'relocation_verification': {'targets_and_addends_equal': True, 'count_per_object': 75,
                                'normalized_offset_type_target_addend': relocs[0][1],
                                'target_readelf_raw': relocs[0][0], 'generated_readelf_raw': relocs[1][0]},
    'jump_table_verification': {
        'tables': 12, 'entries': 440, 'bytes': 1760,
        'method': 'Existing externalize_elf_symbol.py --require-relocation-match on each table; '
                  '--require-section-symbols covers all twelve tables before section removal. '
                  'All guards passed in the canonical build. No instruction rewriting or gate changes.'},
    'dol_sha1_raw': sha1, 'legal_audit_raw': legal,
    'build_output': PREFIX + str(build_report),
    'hypothesis': 'Branch-label fidelity and call-crossing live ranges, rather than compiler flags: '
                  'restore actor 112, the empty selector 0x47 arm, and two single-case switches; '
                  'move response-state assignments after helper calls; read the selector before '
                  'initializing its conditional result; correct the pointer-return selector prototype; '
                  'declare the result before the duration to reproduce the remaining register tie.',
    'measured_sequence': [
        {'variant': 'fresh preserved source', 'score': 95.50203, 'bytes': 5884},
        {'variant': 'missing actor and empty selector labels', 'score': 95.729, 'bytes': 5896},
        {'variant': 'single-case switches and final flag accumulator', 'score': 95.91193, 'bytes': 5904},
        {'variant': 'pointer-return helper prototype', 'score': 96.060974, 'bytes': 5904},
        {'variant': 'fourteen response-state assignments after calls', 'score': 98.59078, 'bytes': 5904},
        {'variant': 'conditional expression probe', 'score': 98.80081, 'bytes': 5904},
        {'variant': 'selector evaluated before default assignment', 'score': 98.875336, 'bytes': 5904},
        *json.loads((REPORTS / f'probes-{ASSIGNMENT}.json').read_text()),
        {'variant': 'retail-verified jump-table registration', 'score': 100.0, 'bytes': 5904}],
    'divergence': ''}
summary = REPORTS / f'objdiff-{ASSIGNMENT}.json'
summary.write_text(json.dumps(report, indent=2) + '\n')
envelope = {'version': 1, 'assignment_id': ASSIGNMENT, 'attempt': 6,
            'base_commit': '367b61ce697ea84cc58c24cf89c06c9f9bdbb634', 'target': TARGET,
            'status': 'matched', 'evidence': [PREFIX + str(summary), *raw_files,
                PREFIX + str(build_report), PREFIX + f'reports/GEDE01/verify-{ASSIGNMENT}.py',
                PREFIX + f'reports/GEDE01/probes-{ASSIGNMENT}.json'],
            'divergence': ''}
(REPORTS / f'durable-{ASSIGNMENT}.json').write_text(json.dumps(envelope, indent=2) + '\n')
print(json.dumps({'canonical': summaries['canonical'], 'strict': summaries['reloc-strict'],
                  'text_bytes_equal': True, 'relocations_equal': True, 'dol_sha1_raw': sha1,
                  'legal_audit_raw': legal}, indent=2))
