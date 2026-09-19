"""Reproduce the assigned TU's raw objdiff, ELF-relocation and whole-DOL checks."""
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
AID = 'd8561a38-e67b-4494-a749-a5a581824937'
REPORTS = ROOT / 'reports/GEDE01'
TARGET = 'fn_8007930C'
EXPECTED = 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
previous = REPORTS / ('checks-' + AID + '.json')
checks = {'version': 1, 'assignment_id': AID, 'target': TARGET,
          'commands': json.loads(previous.read_text())['commands'] if previous.exists() else []}


def run(args, expected=0):
    proc = subprocess.run(args, cwd=ROOT, text=True, stdout=subprocess.PIPE,
                          stderr=subprocess.STDOUT)
    checks['commands'].append({'cwd': 'eternal-darkness-decomp', 'argv': args,
                               'exit_code': proc.returncode, 'raw_output': proc.stdout})
    assert proc.returncode == expected, (args, proc.returncode, proc.stdout)
    return proc.stdout


def digest(path, algorithm='sha256'):
    return hashlib.new(algorithm, path.read_bytes()).hexdigest()


def elf_relocations(path):
    data = path.read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02', 'Requires ELF32 big endian'
    header = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    sections = [struct.unpack_from('>IIIIIIIIII', data, header[6] + i * header[11])
                for i in range(header[12])]

    def section_data(index):
        s = sections[index]
        return data[s[4]:s[4] + s[5]]

    def string(table, index):
        return table[index:table.index(0, index)].decode('utf-8')

    names = section_data(header[13])
    result = []
    for section in sections:
        if section[1] != 4:  # SHT_RELA, explicit signed addends
            continue
        assert string(names, section[0]) == '.rela.text'
        symbols = sections[section[6]]
        symbol_names = section_data(symbols[6])
        for offset in range(section[4], section[4] + section[5], section[9]):
            address, info, addend = struct.unpack_from('>IIi', data, offset)
            symbol = struct.unpack_from('>IIIBBH', data,
                                        symbols[4] + (info >> 8) * symbols[9])
            result.append({'offset': address, 'type': info & 255,
                           'symbol_name': string(symbol_names, symbol[0]),
                           'symbol_value': symbol[1], 'symbol_section': symbol[5],
                           'addend': addend})
    return result


try:
    if '--reuse-build' not in sys.argv:
        run(['python3', 'configure.py'])
        run(['.tools/bin/ninja', '-j2'])
    run(['.tools/bin/ninja', '-t', 'commands',
         'build/GEDE01/src/game/game_fn_8007930C.o'])
    canonical = REPORTS / ('objdiff-' + AID + '.json')
    strict = REPORTS / ('objdiff-' + AID + '-reloc-strict.json')
    for path, settings in [(canonical, []), (strict, ['-c', 'function_reloc_diffs=name_address'])]:
        run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u',
             'main/game/game_fn_8007930C', TARGET, '-o', str(path.relative_to(ROOT)),
             '--format', 'json-pretty'] + settings)
    analyses = []
    for path in [canonical, strict]:
        report = json.loads(path.read_text())
        left = next(s for s in report['left']['symbols'] if s['name'] == TARGET)
        right = next(s for s in report['right']['symbols'] if s['name'] == TARGET)
        assert left['size'] == right['size'] == '552'
        assert len(left['instructions']) == len(right['instructions']) == 138
        differences = []
        annotations = []
        for side in [left, right]:
            annotations.append([
                {'address': row['instruction'].get('address', '0'),
                 'formatted_without_registers': re.sub(r'\br\d+\b', 'REG', row['instruction']['formatted']),
                 'relocation': row['instruction']['relocation']}
                for row in side['instructions'] if 'relocation' in row['instruction']])
        for a, b in zip(left['instructions'], right['instructions']):
            ai, bi = a['instruction'], b['instruction']
            assert ai.get('address', '0') == bi.get('address', '0')
            assert re.sub(r'\br\d+\b', 'REG', ai['formatted']) == re.sub(
                r'\br\d+\b', 'REG', bi['formatted'])
            if a.get('diff_kind') not in (None, 'DIFF_NONE'):
                assert a['diff_kind'] == 'DIFF_ARG_MISMATCH'
                differences.append({'offset': ai.get('address', '0'),
                                    'kind': a['diff_kind'], 'retail': ai['formatted'],
                                    'candidate': bi['formatted']})
        assert annotations[0] == annotations[1]
        analyses.append({'path': 'eternal-darkness-decomp/' + str(path.relative_to(ROOT)),
                         'sha256': digest(path), 'match_percent': left['match_percent'],
                         'size': 552, 'instruction_count': 138,
                         'differing_rows': len(differences), 'differences': differences,
                         'instruction_relocation_annotations': len(annotations[0]),
                         'instruction_relocation_annotations_equal': True})
    checks['objdiff'] = analyses
    checks['canonical_strict_byte_identical'] = canonical.read_bytes() == strict.read_bytes()
    assert checks['canonical_strict_byte_identical']
    retail_object = ROOT / 'build/GEDE01/obj/game/game_fn_8007930C.o'
    candidate_object = ROOT / 'build/GEDE01/src/game/game_fn_8007930C.o'
    left_relocs = elf_relocations(retail_object)
    right_relocs = elf_relocations(candidate_object)
    checks['elf_relocations'] = {'retail_count': len(left_relocs),
                                'candidate_count': len(right_relocs),
                                'offsets_types_symbols_values_sections_addends_equal': left_relocs == right_relocs,
                                'retail': left_relocs, 'candidate': right_relocs}
    assert left_relocs == right_relocs
    run(['sha1sum', 'build/GEDE01/main.dol', 'orig/GEDE01/sys/main.dol'])
    run(['cmp', '-s', 'build/GEDE01/main.dol', 'orig/GEDE01/sys/main.dol'])
    checks['dol_sha1'] = digest(ROOT / 'build/GEDE01/main.dol', 'sha1')
    assert checks['dol_sha1'] == EXPECTED
    checks['dol_scope'] = 'The candidate remains NonMatching; the full canonical link uses the retail split for this TU.'
    checks['fingerprints'] = {p: digest(ROOT / p) for p in [
        'src/game/game_fn_8007930C.c', 'compilers/GC/1.3/mwcceppc.exe',
        'build/tools/objdiff-cli', 'build/GEDE01/src/game/game_fn_8007930C.o',
        'build/GEDE01/obj/game/game_fn_8007930C.o']}
    run(['rg', '-n', r'asm|__asm|#pragma|register[ \t]+(void|u8|int|float|double|short|char)',
         'src/game/game_fn_8007930C.c'], expected=1)
    run(['python3', 'tools/legal_audit.py'])
    checks['success'] = True
    print(json.dumps({'score': analyses[0]['match_percent'],
                      'differing_rows': analyses[0]['differing_rows'],
                      'elf_relocations': len(left_relocs), 'dol_sha1': checks['dol_sha1']}))
finally:
    (REPORTS / ('checks-' + AID + '.json')).write_text(json.dumps(checks, indent=2) + '\n')
