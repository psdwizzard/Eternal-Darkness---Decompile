"""Read-only verification of the final assigned object and linked DOL.

Run from eternal-darkness-decomp after the canonical Ninja build and objdiff.
Outputs only assignment-specific reports, using standard-library ELF parsing.
"""
import hashlib
import json
from pathlib import Path
import struct

ASSIGNMENT = '72c01144-98d0-4afe-b445-9484fbe58b63'
REPORT = Path('reports/GEDE01') / ASSIGNMENT
EXPECTED = 'ea24b6af954876ce072562ff39cdb4c81d32be1f'


def parse_elf(path):
    data = path.read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02', 'Expected ELF32 big-endian'
    shoff = struct.unpack_from('>I', data, 32)[0]
    shsize, shnum, shstridx = struct.unpack_from('>HHH', data, 46)
    headers = [struct.unpack_from('>10I', data, shoff + i * shsize) for i in range(shnum)]

    def payload(index):
        h = headers[index]
        return data[h[4]:h[4] + h[5]]

    def string(blob, offset):
        return blob[offset:blob.index(0, offset)].decode()

    names = payload(shstridx)
    sections = {string(names, h[0]): i for i, h in enumerate(headers)}
    text_index = sections['.text']
    relocations = []
    for index, h in enumerate(headers):
        if h[1] != 4 or h[7] != text_index:
            continue
        symbols = payload(h[6])
        symstrings = payload(headers[h[6]][6])
        raw = payload(index)
        for pos in range(0, len(raw), h[9]):
            offset, info, addend = struct.unpack_from('>IIi', raw, pos)
            symidx = info >> 8
            symbol = struct.unpack_from('>IIIBBH', symbols, symidx * 16)
            relocations.append(dict(offset=offset, type=info & 255,
                                    symbol=string(symstrings, symbol[0]),
                                    symbol_value=symbol[1], addend=addend))
    return dict(path=str(path), object_sha256=hashlib.sha256(data).hexdigest(),
                text=payload(text_index), relocations=relocations)


def function(path, side):
    data = json.loads(path.read_text())
    return next(s for s in data[side]['symbols'] if s['name'] == 'fn_8008A96C')


def main():
    target = parse_elf(Path('build/GEDE01/obj/game/game_fn_8008A96C.o'))
    generated = parse_elf(Path('build/GEDE01/src/game/game_fn_8008A96C.o'))
    differences = []
    for offset in range(0, max(len(target['text']), len(generated['text'])), 4):
        a, b = target['text'][offset:offset + 4], generated['text'][offset:offset + 4]
        if a != b:
            differences.append(dict(offset=offset, target_word=a.hex(), generated_word=b.hex()))
    for side in [target, generated]:
        side['text_size'] = len(side['text'])
        side['text_sha256'] = hashlib.sha256(side.pop('text')).hexdigest()
    assert target['relocations'] == generated['relocations'], 'Relocation target/addend mismatch'
    assert len(target['relocations']) == 38
    assert target['text_size'] == generated['text_size'] == 608
    assert [d['offset'] for d in differences] == [0x78, 0x7C]
    canonical_path = REPORT / 'canonical-final.json'
    strict_path = Path('reports/GEDE01') / ('objdiff-' + ASSIGNMENT + '.json')
    canonical = function(canonical_path, 'left')
    strict = function(strict_path, 'left')
    assert canonical['match_percent'] == strict['match_percent'] == 98.68421
    hashes = {}
    for path in [Path('orig/GEDE01/sys/main.dol'), Path('build/GEDE01/main.dol')]:
        hashes[str(path)] = hashlib.sha1(path.read_bytes()).hexdigest()
        assert hashes[str(path)] == EXPECTED
    (REPORT / 'dol-sha1.txt').write_text(''.join(f'{sha}  {path}\n' for path, sha in hashes.items()))
    result = dict(assignment_id=ASSIGNMENT, target=target, generated=generated,
                  canonical_match_percent=canonical['match_percent'],
                  relocation_strict_match_percent=strict['match_percent'],
                  relocation_records_equal=True, differing_instruction_words=differences,
                  dol_sha1=hashes,
                  dol_note='The retained TU remains NonMatching; the matching DOL uses its retail split object.')
    (REPORT / 'verification.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps({k: v for k, v in result.items() if k not in ['target', 'generated']}, indent=2))


if __name__ == '__main__':
    main()
