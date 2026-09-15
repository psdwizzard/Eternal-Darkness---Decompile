"""Run from eternal-darkness-decomp after the canonical configure/build."""
import hashlib
import json
from pathlib import Path
import struct
import subprocess

AID = 'f3dee8dc-4f9d-4776-a328-7a8a1f988d89'
REPORTS = Path('reports/GEDE01')
verification = REPORTS / f'verification-{AID}.json'
data = json.loads(verification.read_text())

def command(args):
    result = subprocess.run(args, capture_output=True, text=True)
    data['commands'].append(dict(command=' '.join(args), exit_code=result.returncode,
                                 stdout=result.stdout, stderr=result.stderr))
    assert result.returncode == 0, result.stdout + result.stderr
    return result.stdout

for label, suffix, options in [('canonical', '', []), ('relocation_strict', '-reloc-strict',
        ['-c', 'function_reloc_diffs=name_address'])]:
    artifact = REPORTS / f'objdiff-{AID}{suffix}.json'
    command(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u',
             'main/game/game_fn_80058834', 'fn_80058834', '-o', str(artifact),
             '--format', 'json-pretty'] + options)
    diff = json.loads(artifact.read_text())
    sides = [next(s for s in diff[side]['symbols'] if s['name'] == 'fn_80058834')
             for side in ('left', 'right')]
    for side in sides:
        assert side['match_percent'] == 100
        assert int(side['size']) == 1984
        assert len(side['instructions']) == 496
        assert all(row.get('diff_kind') in (None, 'DIFF_NONE') for row in side['instructions'])
    relocations = [[row['instruction']['relocation'] for row in side['instructions']
                    if row.get('instruction', {}).get('relocation')] for side in sides]
    assert len(relocations[0]) == len(relocations[1]) == 110
    data[label] = dict(match_percent=100, retail_bytes=1984, generated_bytes=1984,
                       instruction_count=496, differing_rows=0,
                       retail_relocation_bearing_rows=110, generated_relocation_bearing_rows=110)

def elf_text_and_relocations(path):
    blob = path.read_bytes()
    header = struct.unpack_from('>16sHHIIIIIHHHHHH', blob)
    assert header[0][:6] == b'\x7fELF\x01\x02'
    sections = [struct.unpack_from('>IIIIIIIIII', blob, header[6] + i * header[11])
                for i in range(header[12])]
    string_section = sections[header[13]]
    names = blob[string_section[4]:string_section[4] + string_section[5]]
    for index, section in enumerate(sections):
        if names[section[0]:].split(b'\0', 1)[0] == b'.text':
            text_index = index
            text = blob[section[4]:section[4] + section[5]]
    relocations = []
    for section in sections:
        if section[1] != 4 or section[7] != text_index:
            continue
        symbols = sections[section[6]]
        strings_section = sections[symbols[6]]
        strings = blob[strings_section[4]:strings_section[4] + strings_section[5]]
        for offset in range(section[4], section[4] + section[5], section[9]):
            address, info, addend = struct.unpack_from('>IIi', blob, offset)
            symbol = struct.unpack_from('>IIIBBH', blob,
                                        symbols[4] + (info >> 8) * symbols[9])
            name = strings[symbol[0]:].split(b'\0', 1)[0].decode()
            relocations.append(dict(offset=address, type=info & 255, target=name,
                                    addend=addend, symbol_value=symbol[1]))
    return text, relocations

objects = [Path('build/GEDE01/obj/game/game_fn_80058834.o'),
           Path('build/GEDE01/src/game/game_fn_80058834.o')]
retail, generated = [elf_text_and_relocations(path) for path in objects]
assert retail[0] == generated[0]
assert retail[1] == generated[1]
assert len(retail[1]) == 102
relocation_report = dict(retail_object=str(objects[0]), generated_object=str(objects[1]),
    text_bytes=len(retail[0]), text_bytes_identical=True,
    text_sha256=hashlib.sha256(retail[0]).hexdigest(),
    retail_relocations=retail[1], generated_relocations=generated[1],
    relocation_types_targets_addends_identical=True,
    note='ELF has 102 actual relocation records; objdiff includes 8 additional inferred relocation-bearing instructions.')
(REPORTS / f'relocations-{AID}.json').write_text(json.dumps(relocation_report, indent=2) + '\n')
data['elf_text'] = {k:v for k,v in relocation_report.items()
                    if k not in ('retail_relocations', 'generated_relocations')}
data['dol_sha1'] = hashlib.sha1(Path('build/GEDE01/main.dol').read_bytes()).hexdigest()
assert data['dol_sha1'] == 'ea24b6af954876ce072562ff39cdb4c81d32be1f'
data['source_sha256'] = hashlib.sha256(Path('src/game/game_fn_80058834.c').read_bytes()).hexdigest()
data['recovery'] = 'Accepted base source equals preserved c7c4ab65cc0c2d4a6aa0d5280567dcad3a65a4a4; its resolved/action reuse was retained.'
data['hypothesis_and_result'] = ('Splitting initial heading from the later distance threshold fixed all ten FPR differences. '
    'Logical negation for blocked, reusing its dead signed local for callback tags, and copying current into the dead state_ref '
    'fixed the remaining GPR allocation differences without compiler or instruction changes. '
    'The explicit current temporary preserves the two-move sequence; directly assigning the call result to state_ref loses one move. '
    'All experiments and failed builds are recorded in the experiments report; only the matching C translation unit is retained.')
command(['python3', 'tools/legal_audit.py'])
verification.write_text(json.dumps(data, indent=2) + '\n')
print(json.dumps(dict(canonical=100, relocation_strict=100, text_bytes=1984,
                     instructions=496, actual_relocations=102, objdiff_relocation_rows=110,
                     dol_sha1=data['dol_sha1'], legal_audit='passed'), indent=2))
