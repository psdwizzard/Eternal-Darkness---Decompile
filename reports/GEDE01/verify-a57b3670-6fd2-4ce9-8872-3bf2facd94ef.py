"""Run from eternal-darkness-decomp after its canonical build; read-only ELF audit."""
import hashlib
import json
from pathlib import Path
import struct

A = 'a57b3670-6fd2-4ce9-8872-3bf2facd94ef'
R = Path('reports/GEDE01')


def elf(path):
    data = Path(path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    hdr = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    sections = [struct.unpack_from('>IIIIIIIIII', data, hdr[6] + i * hdr[11]) for i in range(hdr[12])]
    def content(s):
        return data[s[4]:s[4] + s[5]]
    def string(buf, off):
        return buf[off:buf.index(b'\0', off)].decode()
    names = content(sections[hdr[13]])
    section_names = [string(names, s[0]) for s in sections]
    text_index = section_names.index('.text')
    text = content(sections[text_index])
    tables = {}
    for index, section in enumerate(sections):
        if section[1] != 2:
            continue
        strings = content(sections[section[6]])
        syms = []
        for offset in range(section[4], section[4] + section[5], section[9]):
            name, value, size, info, other, shndx = struct.unpack_from('>IIIBBH', data, offset)
            syms.append(dict(name=string(strings, name), value=value, size=size, section=shndx))
        tables[index] = syms
    records = []
    for index, section in enumerate(sections):
        if section[1] != 4 or section[7] != text_index:
            continue
        for offset in range(section[4], section[4] + section[5], section[9]):
            addr, info, addend = struct.unpack_from('>IIi', data, offset)
            symbol = tables[section[6]][info >> 8]
            records.append(dict(offset=addr, type=info & 255, target=symbol['name'], addend=addend, target_value=symbol['value']))
    return dict(path='eternal-darkness-decomp/' + path, elf_sha256=hashlib.sha256(data).hexdigest(), text_size=len(text), text_sha256=hashlib.sha256(text).hexdigest(), relocations=records), text

left, left_text = elf('build/GEDE01/obj/game/game_fn_800E33B8.o')
right, right_text = elf('build/GEDE01/src/game/game_fn_800E33B8.o')
measurements = {}
for suffix in ['', '-reloc-strict']:
    d = json.loads((R / ('objdiff-' + A + suffix + '.json')).read_text())
    l = next(s for s in d['left']['symbols'] if s['name'] == 'fn_800E33B8')
    r = next(s for s in d['right']['symbols'] if s['name'] == 'fn_800E33B8')
    diffs = []
    for i, (x, y) in enumerate(zip(l['instructions'], r['instructions'])):
        if x.get('diff_kind') or y.get('diff_kind'):
            diffs.append(dict(offset=i * 4, retail=x['instruction']['formatted'], generated=y['instruction']['formatted'], retail_word=left_text[i*4:i*4+4].hex(), generated_word=right_text[i*4:i*4+4].hex(), diff_kind=x.get('diff_kind')))
    measurements[suffix or 'canonical'] = dict(score=l['match_percent'], retail_size=l['size'], generated_size=r['size'], differences=diffs)
source = Path('src/game/game_fn_800E33B8.c').read_bytes()
result = dict(version=1, assignment_id=A, target='fn_800E33B8', status='attempted',
    retained_experiment='aggregate_subset_object_argument (only pointer declaration whitespace normalized)',
    source_sha256=hashlib.sha256(source).hexdigest(), retail=left, generated=right,
    relocation_records_equal=left['relocations']==right['relocations'], measurements=measurements,
    byte_equality=left_text==right_text,
    register_mapping={'retail':dict(event_data='r30',object='r31',mode='r28',argument='r29'), 'generated':dict(event_data='r31',object='r30',mode='r28',argument='r29')},
    history_review='All five supplied preserved commits inspected. Accepted base already held the same C as dbc30a9b3500584cb72a2fbb6a11588ff4367e31; no recovery overwrite needed.',
    new_hypothesis='Unescaped local aggregate scalar replacement changes virtual-register creation/coalescing. Grouping object and argument improves the baseline without changing branches, scheduling, call order, constants, frame, or relocations.',
    experiments='eternal-darkness-decomp/reports/GEDE01/experiments-'+A+'.json',
    experiment_evidence='44 exact C spellings, raw build stdout/stderr and raw objdiff stdout/stderr. Scalar copies and declaration permutations from earlier attempts were not rerun; new aggregate interactions and CFG forms are explicitly identified.',
    registration='Existing independent NonMatching translation unit; canonical GC/1.3 flags and existing -use_lmw_stmw on unchanged.',
    dol_limitation='NonMatching registration links the retail object. DOL hash is the required integration gate and is not proof that this C function matches.',
    initial_dirty_file='CLAUDE.md was modified before this assignment and was left untouched.',
    correction='Interim commentary said five differences; direct measurement shows six register-operand differences.',
    experiment_driver_note='An initial objdiff invocation omitted -o and produced no JSON; corrected to -o - before the 44 recorded measurements. No result is claimed for the failed invocation.')
assert result['relocation_records_equal'] and len(left['relocations']) == 14
assert len(measurements['canonical']['differences']) == 6
assert measurements['canonical']['score'] == measurements['-reloc-strict']['score'] == 99.52381
assert not result['byte_equality']
(R / ('verification-' + A + '.json')).write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps({'score':measurements['canonical']['score'], 'differences':len(measurements['canonical']['differences']), 'relocations_equal_including_addends':result['relocation_records_equal'], 'relocation_count':len(left['relocations'])}))
