import subprocess,json,pathlib,hashlib,struct,collections
ID='2b641f5c-55e8-47f6-8a73-b1b3757163c0'
r=pathlib.Path('reports/GEDE01')
entries=[]
def run(cmd):
    p=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    entries.append({'command':cmd,'cwd':'eternal-darkness-decomp','exit_code':p.returncode,'raw_output':p.stdout})
    (r/f'verification-{ID}.json').write_text(json.dumps(entries,indent=2)+'\n')
    print(' '.join(cmd), 'exit',p.returncode, p.stdout[-800:],flush=True)
    if p.returncode: raise SystemExit(p.returncode)
run(['python3','configure.py'])
run(['.tools/bin/ninja','-j2'])
run(['sha1sum','build/GEDE01/main.dol'])
assert hashlib.sha1(pathlib.Path('build/GEDE01/main.dol').read_bytes()).hexdigest()=='ea24b6af954876ce072562ff39cdb4c81d32be1f'
run(['python3','tools/legal_audit.py'])
for mode,args in [('canonical',[]),('relocation-strict',['-c','function_reloc_diffs=name_address'])]:
    run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_80093D20','fn_80093D20','-o',str(r/f'objdiff-{ID}-{mode}.raw.json'),'--format','json-pretty']+args)
    d=json.loads((r/f'objdiff-{ID}-{mode}.raw.json').read_text())
    for side in ['left','right']:
        s=next(s for s in d[side]['symbols'] if s['name']=='fn_80093D20')
        assert s['match_percent']==100 and int(s['size'])==588
        assert all(i.get('diff_kind','DIFF_NONE')=='DIFF_NONE' for i in s['instructions'])
# Independent ELF32 big-endian relocation audit resolves symbol-table indices to names.
def elf(path):
    data=pathlib.Path(path).read_bytes()
    assert data[:6]==b'\x7fELF\x01\x02'
    shoff=struct.unpack_from('>I',data,32)[0]
    entsize,count,shstr=struct.unpack_from('>HHH',data,46)
    sections=[struct.unpack_from('>10I',data,shoff+i*entsize) for i in range(count)]
    def section(i):
        s=sections[i];return data[s[4]:s[4]+s[5]]
    def string(tab,offset):return tab[offset:tab.index(b'\0',offset)].decode()
    names=[string(section(shstr),s[0]) for s in sections]
    symbols={}
    for i,s in enumerate(sections):
        if s[1]==2:
            symbols[i]=[]
            for off in range(0,s[5],s[9]):
                n,v,size,info,other,ndx=struct.unpack_from('>IIIBBH',section(i),off)
                symbols[i].append({'name':string(section(s[6]),n),'value':v,'size':size,'section':names[ndx] if ndx<len(names) else ndx})
    text_idx=names.index('.text')
    relocs=[]
    for i,s in enumerate(sections):
        if s[1]==4 and s[7]==text_idx:
            for off in range(0,s[5],s[9]):
                offset,info,addend=struct.unpack_from('>IIi',section(i),off)
                symbol=symbols[s[6]][info>>8]
                relocs.append({'offset':offset,'type':info&255,'target':symbol['name'],'target_value':symbol['value'],'target_section':symbol['section'],'addend':addend})
    return {'path':path,'text_size':len(section(text_idx)),'text_sha1':hashlib.sha1(section(text_idx)).hexdigest(),'relocations':relocs},section(text_idx)
a,at=elf('build/GEDE01/obj/game/game_fn_80093D20.o');b,bt=elf('build/GEDE01/src/game/game_fn_80093D20.o')
assert at==bt
assert a['relocations']==b['relocations'] and len(a['relocations'])==38
(r/f'relocations-{ID}.json').write_text(json.dumps({'command':['python3',f'reports/GEDE01/verify-{ID}.py'],'text_bytes_equal':True,'relocations_equal':True,'target':a,'candidate':b},indent=2)+'\n')
print('Independent ELF check: 588 text bytes identical; 38 relocation offsets, types, target names/values/sections and addends identical.',flush=True)
