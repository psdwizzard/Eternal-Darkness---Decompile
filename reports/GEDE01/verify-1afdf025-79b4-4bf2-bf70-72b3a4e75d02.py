"""Run from eternal-darkness-decomp; read-only verification of this assignment."""
import hashlib
import json
from pathlib import Path
import struct
import subprocess

ASSIGNMENT = '1afdf025-79b4-4bf2-bf70-72b3a4e75d02'


def sha1(data):
    return hashlib.sha1(data).hexdigest()


def elf(path):
    data = Path(path).read_bytes()
    header = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    assert data[:6] == b'\x7fELF\x01\x02'
    sections = [struct.unpack_from('>IIIIIIIIII', data, header[6] + i * header[11])
                for i in range(header[12])]

    def contents(section):
        return data[section[4]:section[4] + section[5]]

    def string(table, offset):
        return table[offset:table.index(b'\0', offset)].decode()

    names = contents(sections[header[13]])
    text = next(contents(s) for s in sections if string(names, s[0]) == '.text')
    relocations = []
    for section in sections:
        if section[1] not in (4, 9):
            continue
        symbols = sections[section[6]]
        strings = contents(sections[symbols[6]])
        for offset in range(section[4], section[4] + section[5], section[9]):
            address, info = struct.unpack_from('>II', data, offset)
            addend = struct.unpack_from('>i', data, offset + 8)[0] if section[1] == 4 else None
            name_offset = struct.unpack_from('>I', data, symbols[4] + (info >> 8) * symbols[9])[0]
            relocations.append(dict(section=string(names, sections[section[7]][0]),
                                    offset=address, type=info & 255,
                                    target=string(strings, name_offset), addend=addend))
    return text, dict(path=path, object_sha1=sha1(data), text_size=len(text),
                      text_sha1=sha1(text), relocations=relocations)


def dol_slice(data, address, size):
    for i in range(18):
        offset = struct.unpack_from('>I', data, 4 * i)[0]
        start = struct.unpack_from('>I', data, 0x48 + 4 * i)[0]
        length = struct.unpack_from('>I', data, 0x90 + 4 * i)[0]
        if start <= address and address + size <= start + length:
            return data[offset + address - start:offset + address - start + size]
    raise ValueError('Address is outside DOL sections')


target_text, target = elf('build/GEDE01/obj/game/game_fn_8017C1C8.o')
base_text, base = elf('build/GEDE01/src/game/game_fn_8017C1C8.o')
assert target_text == base_text and len(base_text) == 232
assert target['relocations'] == base['relocations']
assert len([r for r in base['relocations'] if r['type']]) == 13
assert all(r['addend'] == 0 for r in base['relocations'] if r['type'])
retail = Path('orig/GEDE01/sys/main.dol').read_bytes()
built = Path('build/GEDE01/main.dol').read_bytes()
assert sha1(built) == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
assert built == retail
assert dol_slice(retail, 0x8017C1C8, 232) == dol_slice(built, 0x8017C1C8, 232)
commands = []
for args in [
    ['build/tools/objdiff-cli', '--version'],
    ['.tools/bin/ninja', '-t', 'commands', 'build/GEDE01/src/game/game_fn_8017C1C8.o'],
    ['python3', 'tools/legal_audit.py'],
    ['sha1sum', 'build/GEDE01/main.dol'],
]:
    result = subprocess.run(args, text=True, capture_output=True)
    commands.append(dict(argv=args, returncode=result.returncode,
                         stdout=result.stdout, stderr=result.stderr))
    assert result.returncode == 0
for name, config in [('objdiff', []), ('objdiff-strict', ['-c', 'function_reloc_diffs=all'])]:
    path = f'reports/GEDE01/{name}-{ASSIGNMENT}.json'
    args = ['build/tools/objdiff-cli', 'diff', '-1', target['path'], '-2', base['path'],
            *config, '-o', path, '--format', 'json-pretty']
    result = subprocess.run(args, text=True, capture_output=True)
    commands.append(dict(argv=args, returncode=result.returncode,
                         stdout=result.stdout, stderr=result.stderr))
    assert result.returncode == 0
    diff = json.loads(Path(path).read_text())
    symbol = next(s for s in diff['left']['symbols'] if s['name'] == 'fn_8017C1C8')
    assert symbol['match_percent'] == 100.0 and symbol['size'] == '232'
print(json.dumps(dict(
    assignment_id=ASSIGNMENT, target=target, generated=base,
    unrelocated_text_equal=True, all_relocation_records_equal=True,
    dol_sha1=sha1(built), full_retail_dol_equal=True,
    linked_function_equal=True,
    diagnostic_string=dol_slice(retail, 0x80250FC4, 16).split(b'\0')[0].decode(),
    compiler_sha1=sha1(Path('compilers/GC/1.3/mwcceppc.exe').read_bytes()),
    commands=commands), indent=2))
