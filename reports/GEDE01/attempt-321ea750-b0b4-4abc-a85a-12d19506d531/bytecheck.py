"""Compare ELF32 big-endian function bytes and resolved RELA records without exporting bytes."""
import hashlib,json,pathlib,struct
root=pathlib.Path(__file__).resolve().parents[3]
report=pathlib.Path(__file__).resolve().parent

def inspect(relative):
    data=(root/relative).read_bytes()
    assert data[:6]==b'\x7fELF\x01\x02'
    hdr=struct.unpack_from('>HHIIIIIHHHHHH',data,16)
    assert hdr[1]==20 # EM_PPC
    shoff,shentsize,shnum,shstrndx=hdr[5],hdr[10],hdr[11],hdr[12]
    sections=[struct.unpack_from('>IIIIIIIIII',data,shoff+i*shentsize) for i in range(shnum)]
    def contents(sec): return data[sec[4]:sec[4]+sec[5]]
    def string(table,offset): return table[offset:table.index(0,offset)].decode()
    names=contents(sections[shstrndx])
    ti=next(i for i,s in enumerate(sections) if string(names,s[0])=='.text')
    text=contents(sections[ti])
    relocs=[]
    for sec in sections:
        if sec[1]!=4 or sec[7]!=ti: continue
        syms=sections[sec[6]]
        strings=contents(sections[syms[6]])
        for off in range(sec[4],sec[4]+sec[5],sec[9]):
            offset,info,addend=struct.unpack_from('>IIi',data,off)
            sym=struct.unpack_from('>IIIBBH',data,syms[4]+(info>>8)*syms[9])
            relocs.append({'offset':offset,'type':info&255,'target':string(strings,sym[0]),'symbol_value':sym[1],'addend':addend})
    return text,{'path':'eternal-darkness-decomp/'+relative,'text_size':len(text),'text_sha256':hashlib.sha256(text).hexdigest(),'relocations':relocs}
a,ar=inspect('build/GEDE01/obj/game/game_fn_80198850.o')
b,br=inspect('build/GEDE01/src/game/game_fn_80198850.o')
result={'target':ar,'candidate':br,'bytes_equal':a==b,'relocations_equal':ar['relocations']==br['relocations']}
print(json.dumps(result,indent=2))
assert result['bytes_equal'] and result['relocations_equal']
