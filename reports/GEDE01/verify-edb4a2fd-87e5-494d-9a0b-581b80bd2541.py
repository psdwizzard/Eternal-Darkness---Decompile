"""Run from eternal-darkness-decomp; verify this assignment without changing objects."""
import hashlib
import json
import struct
import subprocess
from pathlib import Path

ASSIGNMENT = 'edb4a2fd-87e5-494d-9a0b-581b80bd2541'
REPORTS = Path('reports/GEDE01')
UNIT = 'main/game/game_fn_800DC4D4'
SYMBOL = 'fn_800DC4D4'
EXPECTED = 'ea24b6af954876ce072562ff39cdb4c81d32be1f'


def run(command):
    result = subprocess.run(command, text=True, capture_output=True)
    return dict(command=command, exit_code=result.returncode,
                stdout=result.stdout, stderr=result.stderr)


def elf_function(path):
    data = Path(path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    start = struct.unpack_from('>I', data, 0x20)[0]
    stride, count = struct.unpack_from('>HH', data, 0x2e)
    sections = [struct.unpack_from('>10I', data, start + i * stride) for i in range(count)]
    tables = {}
    for index, section in enumerate(sections):
        if section[1] != 2:
            continue
        strings = sections[section[6]]
        names = data[strings[4]:strings[4] + strings[5]]
        symbols = []
        for offset in range(section[4], section[4] + section[5], section[9]):
            name, value, size, info, other, shndx = struct.unpack_from('>IIIBBH', data, offset)
            symbols.append(dict(name=names[name:].split(b'\0', 1)[0].decode(),
                                value=value, size=size, section=shndx))
        tables[index] = symbols
    symbol = next(s for table in tables.values() for s in table if s['name'] == SYMBOL)
    section = sections[symbol['section']]
    offset = section[4] + symbol['value']
    code = data[offset:offset + symbol['size']]
    relocations = []
    for section in sections:
        if section[1] not in (4, 9) or section[7] != symbol['section']:
            continue
        assert section[1] == 4, 'Explicit RELA addends required'
        for offset in range(section[4], section[4] + section[5], section[9]):
            address, info, addend = struct.unpack_from('>IIi', data, offset)
            if not symbol['value'] <= address < symbol['value'] + symbol['size']:
                continue
            target = tables[section[6]][info >> 8]
            relocations.append(dict(offset=address - symbol['value'], type=info & 255,
                                    target=target['name'], target_value=target['value'],
                                    addend=addend))
    relocations.sort(key=lambda r: r['offset'])
    return code, dict(path=path, size=len(code), text_sha1=hashlib.sha1(code).hexdigest(),
                      relocations=relocations)


unit = next(u for u in json.loads(Path('objdiff.json').read_text())['units'] if u['name'] == UNIT)
commands = []
scores = {}
for mode, filename, flags in [
    ('canonical', f'objdiff-{ASSIGNMENT}.json', []),
    ('relocation_strict', f'objdiff-strict-{ASSIGNMENT}.json', ['-c', 'function_reloc_diffs=name_address']),
]:
    output = REPORTS / filename
    commands.append(run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', UNIT,
                         '-o', str(output), '--format', 'json-pretty', *flags, SYMBOL]))
    assert commands[-1]['exit_code'] == 0, commands[-1]
    diff = json.loads(output.read_text())
    scores[mode] = {side: next(s for s in diff[side]['symbols'] if s['name'] == SYMBOL)['match_percent']
                    for side in ('left', 'right')}
left_code, left = elf_function(unit['target_path'])
right_code, right = elf_function(unit['base_path'])
commands.append(run(['sha1sum', 'build/GEDE01/main.dol']))
commands.append(run(['python3', 'tools/legal_audit.py']))
for path in (unit['target_path'], unit['base_path']):
    commands.append(run(['build/binutils/powerpc-eabi-readelf', '-Wr', path]))
sha1 = hashlib.sha1(Path('build/GEDE01/main.dol').read_bytes()).hexdigest()
report = dict(version=1, assignment_id=ASSIGNMENT, working_directory='eternal-darkness-decomp',
              unit=unit, scores=scores, target=left, generated=right,
              text_bytes_equal=left_code == right_code,
              relocations_equal=left['relocations'] == right['relocations'],
              expected_dol_sha1=EXPECTED, dol_sha1=sha1,
              raw_commands=commands)
(REPORTS / f'verification-{ASSIGNMENT}.json').write_text(json.dumps(report, indent=2) + '\n')
assert all(c['exit_code'] == 0 for c in commands)
assert all(score == 100 for side in scores.values() for score in side.values()), scores
assert report['text_bytes_equal'] and report['relocations_equal']
assert sha1 == EXPECTED
print(json.dumps(dict(scores=scores, text_bytes_equal=True, relocations_equal=True,
                      relocation_count=len(left['relocations']), dol_sha1=sha1), indent=2))
