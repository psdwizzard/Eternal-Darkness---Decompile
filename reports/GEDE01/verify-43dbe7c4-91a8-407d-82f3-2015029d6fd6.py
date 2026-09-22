"""Assignment-local measurement; run from eternal-darkness-decomp."""
import hashlib, json, pathlib, struct, subprocess
ID = '43dbe7c4-91a8-407d-82f3-2015029d6fd6'
ROOT = pathlib.Path('reports/GEDE01')
TARGET = 'fn_80088298'
def elf(path):
    data = pathlib.Path(path).read_bytes()
    assert data[:6] == b'\x7fELF\x01\x02'
    off = struct.unpack_from('>I', data, 32)[0]
    size, count, names_index = struct.unpack_from('>HHH', data, 46)
    sections = [struct.unpack_from('>10I', data, off+i*size) for i in range(count)]
    def contents(s): return data[s[4]:s[4]+s[5]]
    names = contents(sections[names_index])
    def string(table, i): return table[i:table.index(b'\0', i)].decode()
    by_name = {string(names, s[0]):s for s in sections}
    rel = by_name['.rela.text']; sym = sections[rel[6]]; strings = contents(sections[sym[6]])
    symbols = [struct.unpack_from('>IIIBBH', data, p) for p in range(sym[4],sym[4]+sym[5],sym[9])]
    rows = []
    for p in range(rel[4], rel[4]+rel[5], rel[9]):
        address, info, addend = struct.unpack_from('>IIi', data, p)
        target = symbols[info >> 8]
        rows.append({'address':address, 'type':info & 255, 'target':string(strings,target[0]), 'target_value':target[1], 'addend':addend})
    return contents(by_name['.text']), rows

def measure():
    dest = ROOT / ('objdiff-'+ID+'.json')
    report = json.loads(dest.read_text()) if dest.exists() else {}
    report.update({'version':1, 'assignment_id':ID, 'target':TARGET, 'compiler':'GC/1.3', 'extra_cflags':['-use_lmw_stmw on']})
    for mode, flags in [('canonical',[]), ('relocation_strict',['-c','function_reloc_diffs=name_address'])]:
        scratch = ROOT / ('objdiff-'+ID+'-scratch.json')
        cmd = ['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80088298',TARGET,'-o',str(scratch),'--format','json-pretty']+flags
        p = subprocess.run(cmd, text=True, capture_output=True, check=True)
        raw = json.loads(scratch.read_text())
        left = raw['left']['symbols'][0]; right = raw['right']['symbols'][0]
        instructions = [(l['instruction'],r['instruction']) for l,r in zip(left['instructions'],right['instructions'])]
        report[mode] = {'command':cmd, 'exit_code':p.returncode, 'stdout':p.stdout, 'stderr':p.stderr,
            'raw_sections':raw['left']['sections'], 'raw_symbol':{k:v for k,v in left.items() if k!='instructions'},
            'expected_instruction_count':len(left['instructions']), 'generated_instruction_count':len(right['instructions']),
            'opcode_mismatch_count':sum(l['parts'][0]!=r['parts'][0] for l,r in instructions),
            'formatted_instruction_mismatch_count':sum(l['formatted']!=r['formatted'] for l,r in instructions)}
        if mode=='relocation_strict':
            report['operand_difference_metadata'] = [
                {'address':int(l.get('address','0')), 'mnemonic':l['parts'][0]['opcode']['mnemonic'],
                 'expected_registers':[p['arg']['opaque'] for p in l['parts'] if 'opaque' in p.get('arg',{})],
                 'generated_registers':[p['arg']['opaque'] for p in r['parts'] if 'opaque' in p.get('arg',{})]}
                for l,r in instructions if l['formatted']!=r['formatted']]
        scratch.unlink()
    target, tr = elf('build/GEDE01/obj/game/game_fn_80088298.o')
    generated, gr = elf('build/GEDE01/src/game/game_fn_80088298.o')
    report['elf_verification'] = {'expected_text_size':len(target),'generated_text_size':len(generated),
        'text_bytes_equal':target==generated,'equal_byte_count':sum(x==y for x,y in zip(target,generated)),
        'equal_instruction_word_count':sum(target[i:i+4]==generated[i:i+4] for i in range(0,len(target),4)),
        'expected_text_sha256':hashlib.sha256(target).hexdigest(),'generated_text_sha256':hashlib.sha256(generated).hexdigest(),
        'relocation_tuples_equal':tr==gr, 'expected_relocations':tr,'generated_relocations':gr}
    report['source_sha256'] = hashlib.sha256(pathlib.Path('src/game/game_fn_80088298.c').read_bytes()).hexdigest()
    dest=ROOT/('objdiff-'+ID+'.json');dest.write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps({mode:report[mode]['raw_symbol'] for mode in ['canonical','relocation_strict']},indent=2))
    print('relocations equal:',tr==gr,'count:',len(tr),'text bytes equal:',target==generated)
if __name__=='__main__': measure()
