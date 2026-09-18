"""Run from eternal-darkness-decomp after the final build."""
import hashlib
import json
from pathlib import Path
import struct
import subprocess

OUT = Path('reports/GEDE01/e11b057e-69b6-4c87-b03b-7732ad8af301')
commands = json.loads((OUT / 'final-commands.json').read_text())

def run(args, name):
    p = subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    (OUT / (name + '.log')).write_text(p.stdout)
    commands.append({'cwd': 'eternal-darkness-decomp', 'argv': args, 'exit_code': p.returncode, 'raw_output': str(OUT / (name + '.log'))})
    (OUT / 'final-commands.json').write_text(json.dumps(commands, indent=2) + '\n')
    assert p.returncode == 0, p.stdout

def inspect(path):
    data = Path(path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    h = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    assert h[2] == 20  # PowerPC
    sections = [struct.unpack_from('>IIIIIIIIII', data, h[6] + i*h[11]) for i in range(h[12])]
    def payload(s):
        return data[s[4]:s[4]+s[5]]
    def string(table, pos):
        return table[pos:table.index(b'\0', pos)].decode()
    names = payload(sections[h[13]])
    text_index = next(i for i,s in enumerate(sections) if string(names,s[0]) == '.text')
    text = payload(sections[text_index])
    relocs = []
    for s in sections:
        if s[1] != 4 or s[7] != text_index:
            continue
        symtab = sections[s[6]]
        strings = payload(sections[symtab[6]])
        for pos in range(s[4],s[4]+s[5],s[9]):
            offset,info,addend = struct.unpack_from('>IIi', data, pos)
            symbol = struct.unpack_from('>IIIBBH', data, symtab[4]+(info>>8)*symtab[9])
            relocs.append({'offset':offset,'type':info&255,'symbol':string(strings,symbol[0]),'symbol_value':symbol[1],'symbol_section_index':symbol[5],'addend':addend})
    return text, {'path':path,'object_sha256':hashlib.sha256(data).hexdigest(),'text_size':len(text),'text_sha256':hashlib.sha256(text).hexdigest(),'text_relocations':relocs}

for mode in ['canonical','strict']:
    args = ['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_801A82FC','fn_801A82FC','-o',str(OUT / ('final-'+mode+'.json')),'--format','json-pretty']
    if mode == 'strict':
        args += ['-c','function_reloc_diffs=name_address']
    run(args, 'final-'+mode)
    result = json.loads((OUT / ('final-'+mode+'.json')).read_text())
    for side in ['left','right']:
        symbol = next(s for s in result[side]['symbols'] if s['name']=='fn_801A82FC')
        if side == 'left':
            assert symbol['match_percent'] == 100
        assert int(symbol['size']) == 168

left, retail = inspect('build/GEDE01/obj/game/game_fn_801A82FC.o')
right, compiled = inspect('build/GEDE01/src/game/game_fn_801A82FC.o')
assert left == right
assert retail['text_relocations'] == compiled['text_relocations']
assert retail['text_relocations'] == [{'offset':24,'type':10,'symbol':'fn_8015C28C','symbol_value':0,'symbol_section_index':0,'addend':0}]
result = {'retail':retail,'compiled':compiled,'text_bytes_equal':True,'relocations_equal_including_target_and_addend':True}
(OUT / 'byte-relocation-verification.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps(result,indent=2))
