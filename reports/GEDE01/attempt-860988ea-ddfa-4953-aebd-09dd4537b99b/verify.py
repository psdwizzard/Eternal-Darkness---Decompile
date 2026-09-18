#!/usr/bin/env python3
"""Run from eternal-darkness-decomp. Rebuild and record raw verification evidence."""
import hashlib
import json
from pathlib import Path
import struct
import subprocess

ID = '860988ea-ddfa-4953-aebd-09dd4537b99b'
OUT = Path('reports/GEDE01')
DETAIL = OUT / ('attempt-' + ID)
commands = []

def run(argv):
    proc = subprocess.run(argv, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    commands.append({'command': argv, 'exit_code': proc.returncode, 'output': proc.stdout})
    (DETAIL / 'verification-commands.json').write_text(json.dumps(commands, indent=2) + '\n')
    if proc.returncode:
        raise RuntimeError(argv)

def elf(path):
    raw = path.read_bytes()
    assert raw[:6] == b'\x7fELF\x01\x02'
    header = struct.unpack_from('>16sHHIIIIIHHHHHH', raw)
    shoff, shsize, shcount, shstr = header[6], header[11], header[12], header[13]
    sections = [struct.unpack_from('>IIIIIIIIII', raw, shoff + i * shsize) for i in range(shcount)]
    def data(section):
        return raw[section[4]:section[4]+section[5]]
    def string(table, offset):
        return table[offset:table.index(b'\0', offset)].decode()
    names = [string(data(sections[shstr]), section[0]) for section in sections]
    text_index = names.index('.text')
    text = data(sections[text_index])
    records = []
    for section in sections:
        if section[1] != 4 or section[7] != text_index:
            continue
        symtab = sections[section[6]]
        strings = data(sections[symtab[6]])
        syms = [struct.unpack_from('>IIIBBH', data(symtab), i) for i in range(0, symtab[5], symtab[9])]
        for offset in range(0, section[5], section[9]):
            addr, info, addend = struct.unpack_from('>IIi', data(section), offset)
            sym = syms[info >> 8]
            records.append({'offset': hex(addr), 'type': info & 255, 'target': string(strings, sym[0]), 'target_value': sym[1], 'addend': addend})
    return text, sorted(records, key=lambda r: int(r['offset'], 16))

if __name__ == '__main__':
    # Rebuild the claimed function from source and relink the DOL; no shared input is removed.
    clean_paths = ['build/GEDE01/src/game/game_fn_801ED5F4.o',
                   'build/GEDE01/src/game/game_fn_801ED5F4.externalized',
                   'build/GEDE01/main.elf', 'build/GEDE01/main.dol']
    for name in clean_paths:
        Path(name).unlink(missing_ok=True)
    (DETAIL / 'cleaned-generated-outputs.json').write_text(json.dumps(clean_paths, indent=2) + '\n')
    run(['python3', 'configure.py'])
    run(['.tools/bin/ninja', '-j2'])
    for label, extra in [('canonical', []), ('strict', ['-c', 'function_reloc_diffs=name_address'])]:
        destination = OUT / ('objdiff-' + ID + '.json') if label == 'canonical' else DETAIL / 'final-strict.objdiff.json'
        run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_801ED5F4', 'fn_801ED5F4', '-o', str(destination), '--format', 'json'] + extra)
        report = json.loads(destination.read_text())
        symbol = next(s for s in report['left']['symbols'] if s['name'] == 'fn_801ED5F4')
        assert symbol['match_percent'] == 100.0, (label, symbol['match_percent'])
    target = Path('build/GEDE01/obj/game/game_fn_801ED5F4.o')
    candidate = Path('build/GEDE01/src/game/game_fn_801ED5F4.o')
    for path in [target, candidate]:
        run(['build/binutils/powerpc-eabi-readelf', '-Wr', str(path)])
    a, ar = elf(target)
    b, br = elf(candidate)
    equality = {'target': str(target), 'candidate': str(candidate),
                'target_text_size': len(a), 'candidate_text_size': len(b),
                'target_text_sha256': hashlib.sha256(a).hexdigest(),
                'candidate_text_sha256': hashlib.sha256(b).hexdigest(),
                'text_bytes_equal': a == b, 'relocations_equal': ar == br,
                'target_relocations': ar, 'candidate_relocations': br}
    (DETAIL / 'byte-and-relocation-comparison.json').write_text(json.dumps(equality, indent=2) + '\n')
    assert a == b and len(a) == 1140
    assert ar == br and len(ar) == 39
    run(['sha1sum', 'build/GEDE01/main.dol'])
    assert hashlib.sha1(Path('build/GEDE01/main.dol').read_bytes()).hexdigest() == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
    run(['python3', 'tools/legal_audit.py'])
    print('PASS: canonical=100 strict=100 .text=1140 exact bytes relocations=39 exact DOL SHA-1 verified')
