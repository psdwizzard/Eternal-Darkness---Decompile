"""Read-only measurement of the final assignment candidate; writes its report."""
import hashlib
import json
from pathlib import Path
import struct
import subprocess

ROOT = Path(__file__).resolve().parents[2]
AID = 'ce3c1c2f-d87b-440a-a138-65458f0a6e05'
REPORTS = ROOT / 'reports/GEDE01'


def elf(path):
    data = path.read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    shoff = struct.unpack_from('>I', data, 32)[0]
    entsize, count, names_index = struct.unpack_from('>HHH', data, 46)
    sections = [struct.unpack_from('>10I', data, shoff + i * entsize) for i in range(count)]
    def payload(section):
        return data[section[4]:section[4] + section[5]]
    def string(table, offset):
        return table[offset:table.index(b'\0', offset)].decode()
    section_names = payload(sections[names_index])
    text_index = next(i for i, sec in enumerate(sections) if string(section_names, sec[0]) == '.text')
    relocs = []
    for sec in sections:
        if sec[1] != 4 or sec[7] != text_index:
            continue
        symtab = sections[sec[6]]
        strings = payload(sections[symtab[6]])
        for offset in range(sec[4], sec[4] + sec[5], sec[9]):
            address, info, addend = struct.unpack_from('>IIi', data, offset)
            sym = struct.unpack_from('>IIIBBH', data, symtab[4] + (info >> 8) * symtab[9])
            relocs.append(dict(offset=address, type=info & 255, target=string(strings, sym[0]), target_value=sym[1], addend=addend))
    return payload(sections[text_index]), relocs


paths = ['build/GEDE01/obj/game/game_fn_801807B0.o', 'build/GEDE01/src/game/game_fn_801807B0.o']
objects = [elf(ROOT / p) for p in paths]
assert objects[0][1] == objects[1][1]
raw = {}
for path in paths:
    result = subprocess.run(['readelf', '-r', path], cwd=ROOT, capture_output=True, text=True, check=True)
    raw[path] = result.stdout
mismatches = []
canonical = json.loads((REPORTS / ('objdiff-' + AID + '.json')).read_text())
strict = json.loads((REPORTS / ('strict-' + AID + '.json')).read_text())
def symbol(report, side):
    return next(s for s in report[side]['symbols'] if s['name'] == 'fn_801807B0')
left, right = symbol(canonical, 'left'), symbol(canonical, 'right')
assert len(objects[0][0]) == len(objects[1][0]) == 412
for a, b in zip(left['instructions'], right['instructions']):
    ai, bi = a['instruction'], b['instruction']
    if ai['formatted'] != bi['formatted']:
        offset = int(ai.get('address', 0))
        mismatches.append(dict(offset=offset, target=ai['formatted'], candidate=bi['formatted'], target_word=objects[0][0][offset:offset+4].hex(), candidate_word=objects[1][0][offset:offset+4].hex(), diff_kind=a.get('diff_kind')))
assert len(mismatches) == 14
hashes = {p: hashlib.sha1((ROOT / p).read_bytes()).hexdigest() for p in ['build/GEDE01/main.dol', 'orig/GEDE01/sys/main.dol']}
assert set(hashes.values()) == {'ea24b6af954876ce072562ff39cdb4c81d32be1f'}
experiments = json.loads((REPORTS / ('experiments-' + AID + '.json')).read_text())['results']
source = ROOT / 'src/game/game_fn_801807B0.c'
audit = subprocess.run(['python3', 'tools/legal_audit.py'], cwd=ROOT, text=True, capture_output=True, check=True)
result = {
    'target': 'fn_801807B0',
    'compiler': 'GC/1.3, unchanged canonical flags recorded in experiments report',
    'canonical_percent': left['match_percent'],
    'relocation_strict_percent': symbol(strict, 'left')['match_percent'],
    'strict_config': 'function_reloc_diffs=all',
    'target_bytes': len(objects[0][0]),
    'candidate_bytes': len(objects[1][0]),
    'instruction_count': len(right['instructions']),
    'instruction_mismatches': mismatches,
    'relocations_equal_including_offsets_targets_values_and_addends': True,
    'relocations': objects[0][1],
    'readelf_raw_outputs': raw,
    'dol_sha1': hashes,
    'dol_note': 'Target remains NonMatching, so the canonical linked DOL uses its retail split object; the DOL hash does not establish a C match.',
    'source_sha256': hashlib.sha256(source.read_bytes()).hexdigest(),
    'experiments_measured': len(experiments),
    'experiments_compiled': sum(x['build_exit'] == 0 for x in experiments),
    'best_score': max(x.get('score', 0) for x in experiments),
    'legal_audit_command': 'python3 tools/legal_audit.py',
    'legal_audit_exit': audit.returncode,
    'legal_audit_stdout': audit.stdout,
    'legal_audit_stderr': audit.stderr,
}
(REPORTS / ('verification-' + AID + '.json')).write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps({k: result[k] for k in ['canonical_percent', 'relocation_strict_percent', 'experiments_measured', 'experiments_compiled', 'dol_sha1', 'legal_audit_stdout']}, indent=2))
