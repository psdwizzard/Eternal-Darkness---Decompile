import hashlib, json, pathlib, re, struct, subprocess
ROOT = pathlib.Path(__file__).resolve().parents[2]
ID = "3c952361-ba01-426a-be54-2d29cc63214a"
REPORT = ROOT / "reports/GEDE01"
commands = []
def run(args):
    p = subprocess.run(args, cwd=ROOT, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    commands.append({"command":args,"cwd":"eternal-darkness-decomp","exit_code":p.returncode,"output":p.stdout})
    (REPORT/('verification-commands-'+ID+'.json')).write_text(json.dumps(commands,indent=2)+'\n')
    if p.returncode: raise RuntimeError(p.stdout)
    return p.stdout
run(['python3','configure.py'])
run(['.tools/bin/ninja','-j2'])
for suffix, flags in [('',[]),('-strict',['-c','function_reloc_diffs=name_address'])]:
    run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_8018F948','fn_8018F948','-o','reports/GEDE01/objdiff-'+ID+suffix+'.json','--format','json-pretty']+flags)
run(['sha1sum','build/GEDE01/main.dol'])
assert hashlib.sha1((ROOT/'build/GEDE01/main.dol').read_bytes()).hexdigest()=='ea24b6af954876ce072562ff39cdb4c81d32be1f'
run(['python3','tools/legal_audit.py'])
# Resolve every ELF32 big-endian RELA target plus signed addend against canonical symbols.
addresses = {m[1]:int(m[2],16) for m in re.finditer(r'^(\w+) = [^:]+:0x([0-9A-Fa-f]+);', (ROOT/'config/GEDE01/symbols.txt').read_text(),re.M)}
def elf(path):
    data=(ROOT/path).read_bytes()
    assert data[:6]==b'\x7fELF\x01\x02'
    shoff=struct.unpack_from('>I',data,32)[0]
    entsize,count,names=struct.unpack_from('>HHH',data,46)
    sections=[struct.unpack_from('>10I',data,shoff+i*entsize) for i in range(count)]
    def blob(s): return data[s[4]:s[4]+s[5]]
    def string(b,n):return b[n:b.index(b'\0',n)].decode()
    ns=blob(sections[names]); section_names=[string(ns,s[0]) for s in sections]
    result=[]
    for sec in sections:
        if sec[1]!=4 or section_names[sec[7]]!='.text':continue
        syms=sections[sec[6]]; strings=blob(sections[syms[6]])
        for offset in range(sec[4],sec[4]+sec[5],sec[9]):
            at,info,addend=struct.unpack_from('>IIi',data,offset)
            sym=struct.unpack_from('>IIIBBH',data,syms[4]+(info>>8)*syms[9])
            name=string(strings,sym[0]); address=addresses.get(name)
            assert address is not None, name
            result.append({'offset':at,'type':info&255,'target':name,'addend':addend,'resolved_target':hex(address+addend)})
    return {'path':path,'text_sha256':hashlib.sha256(blob(sections[section_names.index('.text')])).hexdigest(),'relocations':result}
a=elf('build/GEDE01/obj/game/game_fn_8018F948.o'); b=elf('build/GEDE01/src/game/game_fn_8018F948.o')
normalize=lambda x:[(r['type'],r['resolved_target']) for r in x['relocations']]
result={'method':'Read all .rela.text ELF entries, resolve named targets through config/GEDE01/symbols.txt, add signed ELF addends, compare ordered (type, resolved target) pairs. Offsets may differ because instruction scheduling differs.','retail':a,'candidate':b,'ordered_targets_and_addends_equivalent':normalize(a)==normalize(b),'relocation_offsets_identical':[r['offset'] for r in a['relocations']]==[r['offset'] for r in b['relocations']]}
(REPORT/('relocations-'+ID+'.json')).write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps({'targets_and_addends_equivalent':result['ordered_targets_and_addends_equivalent'],'retail_relocations':len(a['relocations']),'candidate_relocations':len(b['relocations'])}))
