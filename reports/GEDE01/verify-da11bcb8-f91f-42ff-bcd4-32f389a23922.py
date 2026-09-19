"""Verify this assignment's bytes and exact relocation tuples (run from project root)."""
import hashlib
import json
import struct
import subprocess
from pathlib import Path

ASSIGNMENT = 'da11bcb8-f91f-42ff-bcd4-32f389a23922'

def elf(path):
    data = path.read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    shoff = struct.unpack_from('>I', data, 32)[0]
    entsize, count, strindex = struct.unpack_from('>HHH', data, 46)
    sections = [struct.unpack_from('>10I', data, shoff + i * entsize) for i in range(count)]
    def contents(section):
        return data[section[4]:section[4] + section[5]]
    def string(table, offset):
        return table[offset:table.index(0, offset)].decode()
    names = contents(sections[strindex])
    indexes = {string(names, s[0]): i for i,s in enumerate(sections)}
    text_index = indexes['.text']
    symbols = sections[indexes['.symtab']]
    strings = contents(sections[symbols[6]])
    symnames = [string(strings, struct.unpack_from('>I', data, symbols[4] + i)[0]) for i in range(0, symbols[5], symbols[9])]
    relocs = []
    for s in sections:
        if s[1] != 4 or s[7] != text_index:
            continue
        for i in range(s[4], s[4] + s[5], s[9]):
            offset, info, addend = struct.unpack_from('>IIi', data, i)
            relocs.append({'offset': offset, 'type': info & 255, 'target': symnames[info >> 8], 'addend': addend})
    text = contents(sections[text_index])
    return text, relocs

base = Path('build/GEDE01')
target, target_relocs = elf(base / 'obj/game/game_fn_801E995C.o')
candidate, candidate_relocs = elf(base / 'src/game/game_fn_801E995C.o')
report = {
    'assignment_id': ASSIGNMENT,
    'compiler': 'GC/1.3',
    'compiler_flags_changed': False,
    'source': 'eternal-darkness-decomp/src/game/game_fn_801E995C.c',
    'source_sha256': hashlib.sha256(Path('src/game/game_fn_801E995C.c').read_bytes()).hexdigest(),
    'text_size': len(candidate),
    'instruction_count': len(candidate) // 4,
    'raw_text_bytes_equal': target == candidate,
    'target_text_sha256': hashlib.sha256(target).hexdigest(),
    'candidate_text_sha256': hashlib.sha256(candidate).hexdigest(),
    'relocation_tuples_equal': target_relocs == candidate_relocs,
    'target_relocations': target_relocs,
    'candidate_relocations': candidate_relocs,
}
for kind, filename in [('canonical','objdiff-canonical'), ('relocation_strict','objdiff')]:
    diff = json.loads(Path(f'reports/GEDE01/{filename}-{ASSIGNMENT}.json').read_text())
    symbol = next(s for s in diff['left']['symbols'] if s['name'] == 'fn_801E995C')
    report[kind + '_percent'] = symbol['match_percent']
    assert symbol['match_percent'] == 100
unit = next(u for u in json.loads(Path('objdiff.json').read_text())['units'] if u['name'] == 'main/game/game_fn_801E995C')
report['registered_matching'] = unit['metadata']['complete']
assert report['registered_matching']
commands = [
    ['.tools/bin/ninja', '-t', 'commands', 'build/GEDE01/src/game/game_fn_801E995C.externalized'],
    ['sha1sum', 'build/GEDE01/main.dol'],
    ['python3', 'tools/legal_audit.py'],
    ['git', 'diff', '--check'],
    ['build/binutils/powerpc-eabi-readelf', '-r', 'build/GEDE01/obj/game/game_fn_801E995C.o'],
    ['build/binutils/powerpc-eabi-readelf', '-r', 'build/GEDE01/src/game/game_fn_801E995C.o'],
]
report['raw_commands'] = []
for command in commands:
    run = subprocess.run(command, capture_output=True, text=True)
    report['raw_commands'].append({'command': command, 'exit_code': run.returncode, 'stdout': run.stdout, 'stderr': run.stderr})
    assert run.returncode == 0
report['dol_sha1'] = hashlib.sha1((base / 'main.dol').read_bytes()).hexdigest()
assert report['dol_sha1'] == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
assert target == candidate
assert target_relocs == candidate_relocs
Path(f'reports/GEDE01/verification-{ASSIGNMENT}.json').write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps({k:v for k,v in report.items() if k not in ('target_relocations','candidate_relocations','raw_commands')}, indent=2))
