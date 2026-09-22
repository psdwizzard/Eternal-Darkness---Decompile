#!/usr/bin/env python3
"""Reproduce canonical build, strict comparison, legal audit, and retail hash."""
import hashlib, json, pathlib, struct, subprocess
ROOT=pathlib.Path(__file__).resolve().parents[3]
REPORT=pathlib.Path(__file__).resolve().parent
ASSIGNMENT='604d11eb-73b5-4201-91e1-63481c5ce62a'
records=[]
def run(argv):
    p=subprocess.run(argv,cwd=ROOT,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    records.append({'argv':argv,'cwd':'eternal-darkness-decomp','exit_code':p.returncode,'raw_output':p.stdout})
    (REPORT/'verification-commands.json').write_text(json.dumps(records,indent=2)+'\n')
    print(' '.join(argv), 'exit='+str(p.returncode), p.stdout[-1400:],flush=True)
    if p.returncode: raise SystemExit(p.returncode)
    return p.stdout
run(['python3','configure.py'])
# Recompile the final TU so its guarded externalization is explicitly exercised.
(ROOT/'src/game/game_fn_801E504C.c').touch()
run(['.tools/bin/ninja','-j2'])
run(['.tools/bin/ninja','-t','commands','build/GEDE01/src/game/game_fn_801E504C.externalized'])
for strict in [False,True]:
    output=(ROOT/'reports/GEDE01'/('objdiff-'+ASSIGNMENT+'.json')) if strict else REPORT/'canonical.json'
    argv=['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_801E504C','-o',str(output.relative_to(ROOT))]
    if strict: argv+=['-c','function_reloc_diffs=name_address']
    run(argv+['fn_801E504C'])
    j=json.loads(output.read_text())
    for k in ['left','right']:
        f=next(s for s in j[k]['symbols'] if s['name']=='fn_801E504C')
        assert f['match_percent']==100 and int(f['size'])==996
hash_output=run(['sha1sum','build/GEDE01/main.dol'])
assert hash_output.split()[0]=='ea24b6af954876ce072562ff39cdb4c81d32be1f'
run(['python3','tools/legal_audit.py'])

def elf(path):
    b=path.read_bytes()
    shoff=struct.unpack_from('>I',b,32)[0]
    entsize,num,strings=struct.unpack_from('>HHH',b,46)
    sections=[struct.unpack_from('>10I',b,shoff+i*entsize) for i in range(num)]
    def data(s):return b[s[4]:s[4]+s[5]]
    def cstr(b,o):return b[o:b.index(b'\0',o)].decode()
    names=data(sections[strings]); named={cstr(names,s[0]):s for s in sections}
    st=named['.symtab']; strings=data(sections[st[6]])
    symbols=[struct.unpack_from('>IIIBBH',b,i) for i in range(st[4],st[4]+st[5],st[9])]
    rel=named['.rela.text']; rels=[]
    for i in range(rel[4],rel[4]+rel[5],rel[9]):
        offset,info,addend=struct.unpack_from('>IIi',b,i)
        rels.append({'offset':offset,'type':info&255,'target':cstr(strings,symbols[info>>8][0]),'addend':addend})
    text=data(named['.text'])
    return {'path':str(path.relative_to(ROOT.parent)),'text_size':len(text),'text_sha256':hashlib.sha256(text).hexdigest(),'relocations':rels},text
left,lbytes=elf(ROOT/'build/GEDE01/obj/game/game_fn_801E504C.o')
right,rbytes=elf(ROOT/'build/GEDE01/src/game/game_fn_801E504C.o')
result={'left':left,'right':right,'text_bytes_equal':lbytes==rbytes,'relocation_tuples_equal':left['relocations']==right['relocations']}
(REPORT/'byte-relocation-verification.json').write_text(json.dumps(result,indent=2)+'\n')
print('byte/relocation equality:',result['text_bytes_equal'],result['relocation_tuples_equal'],flush=True)
assert result['text_bytes_equal'] and result['relocation_tuples_equal']
