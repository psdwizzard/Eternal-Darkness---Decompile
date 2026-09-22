"""Read-only verification of this assignment's already-built C candidate.
Run from eternal-darkness-decomp after configure.py, ninja, and both objdiff runs.
"""
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess

ASSIGNMENT = 'b34c9785-fcd8-483d-81d5-eb978c35a7e2'
TARGET = 'fn_8012C804'
ROOT_PREFIX = 'eternal-darkness-decomp/'
REPORTS = Path('reports/GEDE01')

def elf_function(path):
    data = path.read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    header = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    shoff, shentsize, shnum = header[6], header[11], header[12]
    sections = [struct.unpack_from('>IIIIIIIIII', data, shoff + i * shentsize) for i in range(shnum)]
    def section_bytes(index):
        s = sections[index]
        return data[s[4]:s[4] + s[5]]
    def cstring(blob, offset):
        return blob[offset:blob.index(b'\0', offset)].decode()
    tables = {}
    for i, s in enumerate(sections):
        if s[1] == 2:
            strings = section_bytes(s[6])
            syms = []
            for off in range(s[4], s[4] + s[5], s[9]):
                name, value, size, info, other, section = struct.unpack_from('>IIIBBH', data, off)
                syms.append({'name': cstring(strings, name), 'value': value, 'size': size, 'section': section})
            tables[i] = syms
    sym = next(s for table in tables.values() for s in table if s['name'] == TARGET)
    code = section_bytes(sym['section'])[sym['value']:sym['value'] + sym['size']]
    relocs = []
    for s in sections:
        if s[1] == 4 and s[7] == sym['section']:
            for off in range(s[4], s[4] + s[5], s[9]):
                address, info, addend = struct.unpack_from('>IIi', data, off)
                if sym['value'] <= address < sym['value'] + sym['size']:
                    relocs.append({'offset': address - sym['value'], 'type': info & 255,
                                   'target': tables[s[6]][info >> 8]['name'], 'addend': addend})
    return code, relocs

canonical_path = REPORTS / f'canonical-{ASSIGNMENT}.json'
canonical_path.write_bytes(Path('build/GEDE01/fndiff_fn_8012C804.json').read_bytes())
canonical = json.loads(canonical_path.read_text())
strict = json.loads((REPORTS / f'strict-{ASSIGNMENT}.json').read_text())
def symbol(doc, side):
    return next(s for s in doc[side]['symbols'] if s['name'] == TARGET)

left, right = symbol(canonical, 'left'), symbol(canonical, 'right')
target_bytes, target_relocs = elf_function(Path('build/GEDE01/obj/game/game_fn_8012C804.o'))
candidate_bytes, candidate_relocs = elf_function(Path('build/GEDE01/src/game/game_fn_8012C804.o'))
sha = subprocess.run(['sha1sum', 'build/GEDE01/main.dol'], check=True, text=True, capture_output=True).stdout.strip()
assert sha.split()[0] == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
audit = subprocess.run(['python3', 'tools/legal_audit.py'], check=True, text=True, capture_output=True).stdout.strip()
source = Path('src/game/game_fn_8012C804.c').read_text()
assert not re.search(r'\b(?:asm|__asm|GLOBAL_ASM)\b', source)
commands = subprocess.run(['.tools/bin/ninja', '-t', 'commands', 'build/GEDE01/src/game/game_fn_8012C804.o'], check=True, capture_output=True, text=True).stdout.strip()
raw_diff = (REPORTS / f'fndiff-{ASSIGNMENT}.txt').read_text()
differences = [line for line in raw_diff.splitlines() if line.startswith('*')]
assert len(target_bytes) == len(candidate_bytes) == 704
assert target_relocs == candidate_relocs and len(target_relocs) == 4
assert left['match_percent'] == symbol(strict, 'left')['match_percent'] == 98.806816
mismatches = [i for i in range(0, len(target_bytes), 4) if target_bytes[i:i+4] != candidate_bytes[i:i+4]]
divergence = ('704/704 bytes; canonical and functionRelocDiffs=all objdiff both 98.806816%, with 4/4 ELF relocations equal by offset, type, target and signed addend. '
              'Remaining codegen differences are register allocation only: retail uses r29 for the initialization zero/first graph counter and r30 for the selected-index byte offset; candidate swaps r29/r30. '
              'The copy loop swaps retail flags r5 and counter r6. The inherited-state path swaps retail inherited pointer r5 and graph pointer r6. '
              'The widened child-tag mask and all graph-entry/child instructions now match. No opcode-order, function-size or relocation divergence remains.')
report = {
    'version': 1, 'assignment_id': ASSIGNMENT, 'target': TARGET,
    'baseline': {'commit': '70b91e0a5860549d9968393c031e51e26e7161a2', 'canonical_match_percent': 96.505684},
    'preserved_attempts_reviewed': ['c8aee74d98780755979420ab75f806114bd014a2', '99f17d997c97913d6845d85c21b0a1016b443ac7', 'f1b58f0035f7fa55586593c68ed952746e2d9fb4', '877c7f70ee9f94a336933c07ed5ab76d2d3b48e3'],
    'hypothesis': 'Retail clears bit 15 of an integer-promoted graph entry with & ~0x8000, not a 15-bit value mask. Reusing the 16-bit entry temporary for copy flags and letting MWCC derive byte offsets from natural loop indices improves lifetime allocation further.',
    'canonical': {'command': 'python3 tools/fndiff.py game/game_fn_8012C804.c fn_8012C804', 'raw_summary': raw_diff.splitlines()[0], 'match_percent': left['match_percent'], 'target_size': left['size'], 'candidate_size': right['size'], 'raw_output': ROOT_PREFIX + str(canonical_path)},
    'relocation_strict': {'command': f'build/tools/objdiff-cli diff -p . -u main/game/game_fn_8012C804 -c functionRelocDiffs=all fn_8012C804 -o reports/GEDE01/strict-{ASSIGNMENT}.json --format json', 'match_percent': symbol(strict, 'left')['match_percent'], 'raw_output': ROOT_PREFIX + str(REPORTS / f'strict-{ASSIGNMENT}.json'), 'records_equal': target_relocs == candidate_relocs, 'target_records': target_relocs, 'candidate_records': candidate_relocs},
    'raw_byte_comparison': {'equal': target_bytes == candidate_bytes, 'identical_instruction_words': len(target_bytes)//4-len(mismatches), 'instruction_words': len(target_bytes)//4, 'mismatch_offsets': mismatches, 'target_text_sha1': hashlib.sha1(target_bytes).hexdigest(), 'candidate_text_sha1': hashlib.sha1(candidate_bytes).hexdigest()},
    'compiler_command': commands,
    'build': {'command': 'python3 configure.py && .tools/bin/ninja -j2', 'raw_output': ROOT_PREFIX + str(REPORTS / f'build-{ASSIGNMENT}.txt'), 'registration': 'NonMatching; retail object remains linked in verified DOL', 'log_normalization': 'CRLF line endings normalized to LF; output text otherwise unchanged'},
    'dol_sha1': {'command': 'sha1sum build/GEDE01/main.dol', 'raw_output': sha},
    'legal_audit': {'command': 'python3 tools/legal_audit.py', 'raw_output': audit, 'source_assembly_check': 'No asm, __asm, or GLOBAL_ASM tokens; one independent C translation unit; no compiler, gate, runtime, neighboring-function or global-progress changes.'},
    'source_sha256': hashlib.sha256(source.encode()).hexdigest(),
    'experiments': ROOT_PREFIX + str(REPORTS / f'experiments-{ASSIGNMENT}.json'),
    'exact_instruction_differences': differences,
    'divergence': divergence,
}
main_report = REPORTS / f'objdiff-{ASSIGNMENT}.json'
main_report.write_text(json.dumps(report, indent=2) + '\n')
evidence = [ROOT_PREFIX + str(main_report)] + [ROOT_PREFIX + str(REPORTS / f'{prefix}-{ASSIGNMENT}.{suffix}') for prefix,suffix in [('canonical','json'),('strict','json'),('fndiff','txt'),('experiments','json'),('build','txt'),('verify','py')]]
envelope = {'version':1, 'assignment_id':ASSIGNMENT, 'attempt':5, 'base_commit':'70b91e0a5860549d9968393c031e51e26e7161a2', 'target':TARGET, 'status':'attempted', 'evidence':evidence, 'divergence':divergence}
(REPORTS / f'durable-{ASSIGNMENT}.json').write_text(json.dumps(envelope, indent=2)+'\n')
print(json.dumps({'canonical':left['match_percent'],'strict':symbol(strict,'left')['match_percent'],'exact_words':176-len(mismatches),'relocations_equal':target_relocs==candidate_relocs,'dol':sha,'audit':audit},indent=2))
