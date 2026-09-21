"""Reproduce the assigned function's byte, relocation, DOL and legal checks."""
import hashlib
import json
from pathlib import Path
import struct
import subprocess

ROOT = Path(__file__).resolve().parents[2]
ASSIGNMENT = '46d0628c-89d2-4033-a04c-9089208f0437'
REPORTS = ROOT / 'reports/GEDE01'

def capture(args):
    p = subprocess.run(args, cwd=ROOT, text=True, capture_output=True)
    return {'command': args, 'exit_code': p.returncode, 'stdout': p.stdout, 'stderr': p.stderr}

def elf(path):
    data = (ROOT / path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    shoff = struct.unpack_from('>I', data, 32)[0]
    shentsize, shnum, shstridx = struct.unpack_from('>HHH', data, 46)
    sections = [struct.unpack_from('>10I', data, shoff + i * shentsize) for i in range(shnum)]
    def section(i):
        s = sections[i]
        return data[s[4]:s[4]+s[5]]
    def string(blob, offset):
        return blob[offset:blob.index(b'\0', offset)].decode()
    names = [string(section(shstridx), s[0]) for s in sections]
    textidx = names.index('.text')
    symbols = []
    for i, s in enumerate(sections):
        if s[1] == 2:
            strings = section(s[6])
            for offset in range(0, s[5], s[9]):
                sym = struct.unpack_from('>IIIBBH', section(i), offset)
                symbols.append({'name': string(strings, sym[0]), 'value': sym[1], 'size': sym[2], 'section': sym[5]})
    relocs = []
    for i, s in enumerate(sections):
        if s[1] == 4 and s[7] == textidx:
            for offset in range(0, s[5], s[9]):
                addr, info, addend = struct.unpack_from('>IIi', section(i), offset)
                sym = symbols[info >> 8]
                relocs.append({'offset': addr, 'type': info & 255, 'target': sym['name'], 'symbol_value': sym['value'], 'addend': addend})
    return section(textidx), relocs

units = json.loads((ROOT / 'objdiff.json').read_text())['units']
unit = next(u for u in units if u['name'] == 'main/game/game_fn_8014BA14')
result = {'assignment_id': ASSIGNMENT, 'commands': []}
for strict in (False, True):
    name = ('objdiff-strict-' if strict else 'objdiff-') + ASSIGNMENT + '.json'
    args = ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', unit['name'], 'fn_8014BA14', '-o', 'reports/GEDE01/' + name, '--format', 'json']
    if strict:
        args += ['-c', 'function_reloc_diffs=name_address']
    c = capture(args)
    assert c['exit_code'] == 0, c
    result['commands'].append(c)
    d = json.loads((REPORTS / name).read_text())
    symbol = next(s for s in d['left']['symbols'] if s['name'] == 'fn_8014BA14')
    result['strict_score' if strict else 'canonical_score'] = symbol['match_percent']

a, ar = elf(unit['target_path'])
b, br = elf(unit['base_path'])
result['text'] = {'retail_bytes': len(a), 'generated_bytes': len(b), 'exact_equal_bytes_at_same_offset': sum(x == y for x, y in zip(a, b)), 'different_instruction_offsets': [hex(i) for i in range(0, min(len(a), len(b)), 4) if a[i:i+4] != b[i:i+4]], 'retail_sha256': hashlib.sha256(a).hexdigest(), 'generated_sha256': hashlib.sha256(b).hexdigest()}
result['relocations'] = {'retail': ar, 'generated': br, 'equal_offsets_types_targets_symbol_values_and_addends': ar == br}
for path in [unit['target_path'], unit['base_path']]:
    result['commands'].append(capture(['build/binutils/powerpc-eabi-readelf', '-rW', path]))
result['commands'].append(capture(['sha1sum', 'build/GEDE01/main.dol']))
result['dol_sha1'] = hashlib.sha1((ROOT / 'build/GEDE01/main.dol').read_bytes()).hexdigest()
assert result['dol_sha1'] == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
result['commands'].append(capture(['python3', 'tools/legal_audit.py']))
assert all(c['exit_code'] == 0 for c in result['commands'])
result['nonmatching_note'] = 'DOL verification passes using the retail split for this NonMatching function; it does not certify the C reconstruction as byte-matched.'
(REPORTS / ('verification-' + ASSIGNMENT + '.json')).write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps({k: v for k, v in result.items() if k not in ['commands', 'relocations']}, indent=2))
print('Relocations equal:', ar == br, 'counts:', len(ar), len(br))
