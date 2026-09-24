"""Run from eternal-darkness-decomp; preserve assignment-specific raw checks."""
import hashlib
import json
from pathlib import Path
import struct
import subprocess

ASSIGNMENT = 'b6c2346d-b4f7-437c-9daf-659fa86f6d65'
report = Path(f'reports/GEDE01/objdiff-{ASSIGNMENT}.json')
result = {'assignment_id': ASSIGNMENT, 'cwd': 'eternal-darkness-decomp',
          'target': 'fn_801EA900', 'commands': []}


def save():
    report.write_text(json.dumps(result, indent=2) + '\n')


def run(command):
    process = subprocess.run(command, text=True, capture_output=True)
    result['commands'].append({'command': command, 'exit_code': process.returncode,
                               'stdout': process.stdout, 'stderr': process.stderr})
    save()
    print(' '.join(command), 'exit', process.returncode, flush=True)
    if process.returncode:
        raise SystemExit(process.returncode)
    return process.stdout


run(['python3', 'configure.py'])
run(['.tools/bin/ninja', '-j2'])
commands = run(['.tools/bin/ninja', '-t', 'commands',
                'build/GEDE01/src/game/game_fn_801EA900.o'])
result['compiler'] = {'version': 'GC/1.3', 'commands': commands,
    'sha256': hashlib.sha256(Path('compilers/GC/1.3/mwcceppc.exe').read_bytes()).hexdigest()}
run(['build/tools/objdiff-cli', '--version'])
target = 'build/GEDE01/obj/game/game_fn_801EA900.o'
base = 'build/GEDE01/src/game/game_fn_801EA900.o'
for mode, options in [('canonical', []),
                       ('reloc-strict', ['-c', 'function_reloc_diffs=name_address'])]:
    path = f'build/GEDE01/objdiff-{ASSIGNMENT}-{mode}.json'
    run(['build/tools/objdiff-cli', 'diff', '-1', target, '-2', base,
         *options, '--format', 'json', '-o', path])
    raw = json.loads(Path(path).read_text())
    result[mode] = raw
    symbol = next(s for s in raw['left']['symbols'] if s['name'] == 'fn_801EA900')
    assert symbol['match_percent'] == 100.0
    save()


def elf_sections(path):
    data = Path(path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    offset = struct.unpack_from('>I', data, 32)[0]
    size, count, strings = struct.unpack_from('>HHH', data, 46)
    headers = [struct.unpack_from('>10I', data, offset + i * size) for i in range(count)]
    names_header = headers[strings]
    names = data[names_header[4]:names_header[4] + names_header[5]]
    sections = {}
    for h in headers:
        name = names[h[0]:].split(b'\0')[0].decode()
        sections[name] = (h, data[h[4]:h[4] + h[5]])
    return sections


left, right = elf_sections(target), elf_sections(base)
a, b = left['.text'][1], right['.text'][1]
result['byte_verification'] = {
    'method': 'ELF32 big-endian .text section comparison',
    'target_size': len(a), 'generated_size': len(b), 'identical': a == b,
    'target_sha256': hashlib.sha256(a).hexdigest(),
    'generated_sha256': hashlib.sha256(b).hexdigest(),
    'different_word_offsets': [i for i in range(0, max(len(a), len(b)), 4)
                               if a[i:i+4] != b[i:i+4]]}
assert a == b and len(a) == 248
result['relocations'] = {}
for side, path, sections in [('target', target, left), ('generated', base, right)]:
    output = run(['readelf', '-rW', path])
    relocation_sections = [{'name': name, 'size': h[5], 'entry_size': h[9]}
                           for name, (h, _) in sections.items() if h[1] in (4, 9)]
    assert all(s['size'] == 0 for s in relocation_sections)
    result['relocations'][side] = {'sections': relocation_sections, 'count': 0,
                                   'readelf_stdout': output}
result['relocations']['conclusion'] = 'Neither object has relocations; target and addend sets are both empty.'
sha = run(['sha1sum', 'build/GEDE01/main.dol'])
assert sha.split()[0] == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
result['dol_sha1'] = sha.split()[0]
run(['python3', 'tools/legal_audit.py'])
result['source_sha256'] = hashlib.sha256(Path('src/game/game_fn_801EA900.c').read_bytes()).hexdigest()
result['hypothesis'] = ('Typed 8-byte record indexing lets MWCC synthesize the byte induction variable; '
                        'direct field expressions remove the explicit encoded-pointer temporary. '
                        'These changes reproduce retail scheduling and register allocation.')
result['experiment_evidence'] = f'eternal-darkness-decomp/reports/GEDE01/experiments-{ASSIGNMENT}.json'
save()
