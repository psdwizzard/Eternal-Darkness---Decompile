"""Reproduce final raw evidence from the canonical project build (project-root cwd)."""
from pathlib import Path
import hashlib
import json
import shlex
import struct
import subprocess

ID = 'b2ce7d09-cb0d-47ee-91b3-fdc67aacfab6'
OUT = Path('reports/GEDE01') / ID
CANONICAL = Path('reports/GEDE01') / ('objdiff-' + ID + '.json')
TARGET = Path('build/GEDE01/obj/game/game_fn_80129D54.o')
BASE = Path('build/GEDE01/src/game/game_fn_80129D54.o')
SYMBOL = 'fn_80129D54'

def run(cmd, filename):
    result = subprocess.run(cmd, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    (OUT / filename).write_text('$ ' + shlex.join(cmd) + '\n' + result.stdout + '\nexit_code=' + str(result.returncode) + '\n')
    result.check_returncode()
    return result.stdout

run(['python3', 'configure.py'], 'configure-final.log')
run(['.tools/bin/ninja', '-j2'], 'build-final.log')
run(['.tools/bin/ninja', '-t', 'commands', str(BASE)], 'compiler-command.log')
run(['build/tools/objdiff-cli', '--version'], 'objdiff-version.log')
common = ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_80129D54', SYMBOL]
run(common + ['-o', str(CANONICAL), '--format', 'json-pretty'], 'canonical-command.log')
strict_path = OUT / 'relocation-strict.json'
run(common + ['-c', 'functionRelocDiffs=all', '-o', str(strict_path), '--format', 'json-pretty'], 'strict-command.log')
for name, path in [('retail', TARGET), ('generated', BASE)]:
    run(['build/binutils/powerpc-eabi-readelf', '-Wrs', str(path)], name + '-elf.log')
    run(['build/binutils/powerpc-eabi-objdump', '-dr', str(path)], name + '-disassembly.log')
run(['sha1sum', 'build/GEDE01/main.dol'], 'dol-sha1.log')
assert hashlib.sha1(Path('build/GEDE01/main.dol').read_bytes()).hexdigest() == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
run(['python3', 'tools/legal_audit.py'], 'legal-audit.log')

# Parse ELF32 big-endian directly, independently of objdiff's relocation display.
def elf(path):
    data = path.read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    shoff = struct.unpack_from('>I', data, 32)[0]
    entsize, count, names_index = struct.unpack_from('>HHH', data, 46)
    sections = [struct.unpack_from('>10I', data, shoff + n * entsize) for n in range(count)]
    def contents(section):
        return data[section[4]:section[4] + section[5]]
    def string(table, offset):
        return table[offset:table.index(b'\0', offset)].decode()
    names = contents(sections[names_index])
    text_index = next(n for n, sec in enumerate(sections) if string(names, sec[0]) == '.text')
    relocations = []
    for sec in sections:
        if sec[1] != 4 or sec[7] != text_index:
            continue
        symtab = sections[sec[6]]
        strings = contents(sections[symtab[6]])
        for offset in range(sec[4], sec[4] + sec[5], sec[9]):
            address, info, addend = struct.unpack_from('>IIi', data, offset)
            sym = struct.unpack_from('>IIIBBH', data, symtab[4] + (info >> 8) * symtab[9])
            relocations.append({'offset': address, 'type': info & 255, 'target': string(strings, sym[0]), 'addend': addend})
    return contents(sections[text_index]), relocations

canonical = json.loads(CANONICAL.read_text())
strict = json.loads(strict_path.read_text())
assert canonical == strict
left = next(s for s in canonical['left']['symbols'] if s['name'] == SYMBOL)
right = next(s for s in canonical['right']['symbols'] if s['name'] == SYMBOL)
left_text, left_relocs = elf(TARGET)
right_text, right_relocs = elf(BASE)
assert len(left_text) == 140 and len(right_text) == 136
pairs = [(a.get('instruction'), b.get('instruction')) for a, b in zip(left['instructions'], right['instructions'])]
address_map = {int(a.get('address', 0)): int(b.get('address', 0)) for a, b in pairs if a and b}
missing = [a for a, b in pairs if a and not b]
assert len(missing) == 1 and int(missing[0]['address']) == 0x48
assert not any(b and not a for a, b in pairs)
relocation_pairs = []
for a, b in zip(left_relocs, right_relocs):
    mapped = address_map[a['offset'] & ~3] + (a['offset'] & 3)
    assert mapped == b['offset']
    assert (a['type'], a['target'], a['addend']) == (b['type'], b['target'], b['addend'])
    relocation_pairs.append({'retail': a, 'generated': b, 'type_target_addend_equal': True, 'mapped_offset_equal': True})
assert len(left_relocs) == len(right_relocs) == 3

def branch(word, offset):
    opcode = word >> 26
    if opcode == 18:
        mask, width = 0x03fffffc, 26
    elif opcode == 16:
        mask, width = 0x0000fffc, 16
    else:
        return None
    displacement = word & mask
    if displacement & (1 << (width - 1)):
        displacement -= 1 << width
    destination = displacement if word & 2 else offset + displacement
    return word & ~mask, destination

branch_pairs = []
relocated_instructions = {r['offset'] & ~3 for r in left_relocs}
for a, b in address_map.items():
    aw = struct.unpack_from('>I', left_text, a)[0]
    bw = struct.unpack_from('>I', right_text, b)[0]
    ab, bb = branch(aw, a), branch(bw, b)
    if ab is not None and a not in relocated_instructions:
        assert bb is not None and ab[0] == bb[0]
        assert address_map[ab[1]] == bb[1]
        branch_pairs.append({'retail_offset': a, 'generated_offset': b, 'retail_target': ab[1], 'generated_target': bb[1], 'normalized_equal': True})
    else:
        assert aw == bw, (a, b, aw, bw)
assert branch(struct.unpack_from('>I', left_text, 0x48)[0], 0x48) == (0x48000000, 0x68)
assert branch(struct.unpack_from('>I', left_text, 0x44)[0], 0x44) == (0x48000000, 0x68)
assert not any(branch(struct.unpack_from('>I', left_text, a)[0], a) and branch(struct.unpack_from('>I', left_text, a)[0], a)[1] == 0x48 for a in range(0, len(left_text), 4))
result = {
    'canonical_percent': left['match_percent'],
    'relocation_strict_percent': next(s for s in strict['left']['symbols'] if s['name'] == SYMBOL)['match_percent'],
    'canonical_and_strict_raw_json_equal': True,
    'retail_text_bytes': len(left_text), 'generated_text_bytes': len(right_text),
    'raw_elf_relocations': relocation_pairs,
    'propagated_reference_note': 'Objdiff also displays R_PPC_NONE at retail 0x58 / generated 0x54 for fn_801A9FA4; this is not an ELF relocation.',
    'missing_instruction': missing[0],
    'normalized_branch_pairs': branch_pairs,
    'all_other_instruction_words_equal_after_local_branch_normalization': True,
    'exact_byte_match': False,
    'sha256': {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in [Path('src/game/game_fn_80129D54.c'), Path('compilers/GC/1.3/mwcceppc.exe'), TARGET, BASE]},
}
(OUT / 'verification.json').write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps(result, indent=2))
