"""Read-only ELF32 big-endian byte and relocation-target/addend comparison."""
import hashlib,json,pathlib,struct
root=pathlib.Path(__file__).resolve().parents[3]
d=pathlib.Path(__file__).resolve().parent

def read_elf(p):
    b=p.read_bytes()
    assert b[:6]==b'\x7fELF\x01\x02'
    shoff=struct.unpack_from('>I',b,32)[0]
    shentsize,shnum,shstrndx=struct.unpack_from('>HHH',b,46)
    sections=[struct.unpack_from('>10I',b,shoff+i*shentsize) for i in range(shnum)]
    def data(sh):return b[sh[4]:sh[4]+sh[5]]
    names=data(sections[shstrndx])
    def name(sh):return names[sh[0]:].split(b'\0')[0].decode()
    text_index=next(i for i,s in enumerate(sections) if name(s)=='.text')
    relocs=[]
    for sh in sections:
        if sh[1]!=4 or sh[7]!=text_index:continue
        syms=sections[sh[6]]
        strings=data(sections[syms[6]])
        for pos in range(sh[4],sh[4]+sh[5],sh[9]):
            offset,info,addend=struct.unpack_from('>IIi',b,pos)
            sym=struct.unpack_from('>IIIBBH',b,syms[4]+(info>>8)*syms[9])
            target=strings[sym[0]:].split(b'\0')[0].decode()
            relocs.append({'offset':offset,'type':info&255,'target':target,'addend':addend})
    return data(sections[text_index]),relocs

paths=['build/GEDE01/obj/game/game_fn_801599BC.o','build/GEDE01/src/game/game_fn_801599BC.o']
(a,ar),(b,br)=[read_elf(root/p) for p in paths]
obj=json.loads((d/'final-strict.json').read_text())
counts={side:sum('relocation' in item.get('instruction',{}) for s in obj[side]['symbols'] if s['name']=='fn_801599BC' for item in s['instructions']) for side in ['left','right']}
out={'inputs':paths,'text_sizes':[len(a),len(b)],'text_sha256':[hashlib.sha256(x).hexdigest() for x in [a,b]],'instruction_words':len(a)//4,'differing_instruction_words':[{'offset':hex(i),'retail':a[i:i+4].hex(),'generated':b[i:i+4].hex()} for i in range(0,min(len(a),len(b)),4) if a[i:i+4]!=b[i:i+4]],'elf_relocations_equal_including_targets_and_addends':ar==br,'elf_relocation_counts':[len(ar),len(br)],'objdiff_relocation_bearing_instruction_counts':counts,'elf_relocations':{'retail':ar,'generated':br}}
(d/'byte-relocation-audit.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({k:v for k,v in out.items() if k!='elf_relocations'},indent=2))
