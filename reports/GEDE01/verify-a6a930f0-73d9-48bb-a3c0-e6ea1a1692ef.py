"""Reproduce raw objdiff, ELF byte/relocation checks, DOL hash, and legal audit."""
import hashlib, json, pathlib, struct, subprocess
ID = 'a6a930f0-73d9-48bb-a3c0-e6ea1a1692ef'
OUT = pathlib.Path('reports/GEDE01')

def elf(path):
    b = pathlib.Path(path).read_bytes()
    assert b[:6] == b'\x7fELF\x01\x02', 'Expected ELF32 big endian'
    h = struct.unpack_from('>16sHHIIIIIHHHHHH', b)
    sections = [struct.unpack_from('>IIIIIIIIII', b, h[6]+i*h[11]) for i in range(h[12])]
    def data(s): return b[s[4]:s[4]+s[5]]
    def string(table, offset): return table[offset:table.index(b'\0',offset)].decode()
    names = data(sections[h[13]])
    names = [string(names,s[0]) for s in sections]
    symbols = {}
    for i,s in enumerate(sections):
        if s[1] != 2: continue
        strings = data(sections[s[6]])
        symbols[i] = []
        for off in range(s[4],s[4]+s[5],s[9]):
            n,v,size,info,other,shndx = struct.unpack_from('>IIIBBH',b,off)
            symbols[i].append(dict(name=string(strings,n),value=v,size=size,section=shndx))
    relocs=[]
    for s in sections:
        if s[1] != 4 or names[s[7]] != '.text': continue
        for off in range(s[4],s[4]+s[5],s[9]):
            address,info,addend=struct.unpack_from('>IIi',b,off)
            symbol=symbols[s[6]][info>>8]
            target={'name':symbol['name'],'symbol_value':symbol['value'],'addend':addend}
            # Local constants are compared by section+offset and actual bytes,
            # never by an arbitrary equivalence of differently named externs.
            if 0 < symbol['section'] < len(sections):
                target['section']=names[symbol['section']]
                target['section_offset']=symbol['value']+addend
                target['section_hex']=data(sections[symbol['section']]).hex()
            relocs.append({'offset':address,'type':info&255,'target':target})
    return {'sections':{n:data(s).hex() for n,s in zip(names,sections) if n in ('.text','.sdata2')},'relocations':relocs}

records=[]
for mode,opts in [('canonical',[]),('strict',['-c','function_reloc_diffs=name_address'])]:
    filename=f'objdiff-{ID}'+('-canonical' if mode=='canonical' else '')+'.json'
    cmd=['build/tools/objdiff-cli','diff','-1','build/GEDE01/obj/game/game_fn_801A9FA4.o','-2','build/GEDE01/src/game/game_fn_801A9FA4.o',*opts,'-o',str(OUT/filename),'fn_801A9FA4']
    result=subprocess.run(cmd,capture_output=True,text=True,check=True)
    raw=json.loads((OUT/filename).read_text())
    records.append({'mode':mode,'command':cmd,'returncode':result.returncode,'stdout':result.stdout,'stderr':result.stderr})
    for side in ['left','right']:
        fn=next(x for x in raw[side]['symbols'] if x['name']=='fn_801A9FA4')
        if side=='left': assert fn['match_percent']==100
        assert int(fn['size'])==996
        assert all(not x.get('diff_kind') for x in fn['instructions'])
left=elf('build/GEDE01/obj/game/game_fn_801A9FA4.o')
right=elf('build/GEDE01/src/game/game_fn_801A9FA4.o')
assert left['sections']==right['sections'], 'Raw .text or .sdata2 bytes differ'
def normalized(r):
    t=r['target']
    if 'section' in t:
        return (r['offset'],r['type'],t['section'],t['section_offset'],t['section_hex'])
    return (r['offset'],r['type'],t['name'],t['symbol_value'],t['addend'])
assert [normalized(r) for r in left['relocations']]==[normalized(r) for r in right['relocations']]
assert len(left['relocations'])==31
sha=hashlib.sha1(pathlib.Path('build/GEDE01/main.dol').read_bytes()).hexdigest()
assert sha=='ea24b6af954876ce072562ff39cdb4c81d32be1f'
def dol_slice(path, address, size):
    b=pathlib.Path(path).read_bytes()
    offsets=struct.unpack_from('>18I',b,0)
    addresses=struct.unpack_from('>18I',b,0x48)
    sizes=struct.unpack_from('>18I',b,0x90)
    for off,addr,length in zip(offsets,addresses,sizes):
        if addr <= address and address+size <= addr+length:
            return b[off+address-addr:off+address-addr+size]
    raise AssertionError('DOL address not mapped')
linked=[]
for address,size in [(0x801A9FA4,996),(0x80650E58,8)]:
    original=dol_slice('orig/GEDE01/sys/main.dol',address,size)
    generated=dol_slice('build/GEDE01/main.dol',address,size)
    assert original==generated
    linked.append({'address':hex(address),'size':size,'bytes_equal':True,'sha256':hashlib.sha256(generated).hexdigest()})
audit=subprocess.run(['python3','tools/legal_audit.py'],capture_output=True,text=True,check=True)
report={'linked_dol_ranges':linked,'objdiff_runs':records,'retail_elf':left,'compiled_elf':right,'raw_text_equal':True,'raw_sdata2_equal':True,'relocation_targets_and_addends_equal':True,'relocation_count':len(left['relocations']),'dol_sha1':sha,'legal_audit':{'command':['python3','tools/legal_audit.py'],'returncode':audit.returncode,'stdout':audit.stdout,'stderr':audit.stderr}}
(OUT/f'verification-{ID}.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({k:v for k,v in report.items() if k not in ['retail_elf','compiled_elf','objdiff_runs']},indent=2))
