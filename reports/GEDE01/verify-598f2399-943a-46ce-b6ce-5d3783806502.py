"""Verify this assignment's ELF bytes, relocation identities, and final build gates.
Run from eternal-darkness-decomp after the canonical Ninja build completes.
"""
import hashlib
import json
import struct
import subprocess
from pathlib import Path

assignment = '598f2399-943a-46ce-b6ce-5d3783806502'
reports = Path('reports/GEDE01')

def command(args):
    p = subprocess.run(args, text=True, capture_output=True)
    assert p.returncode == 0, (args, p.stdout, p.stderr)
    return {'command': args, 'returncode': p.returncode, 'stdout': p.stdout, 'stderr': p.stderr}

def elf(path):
    b = Path(path).read_bytes()
    assert b[:6] == b'\x7fELF\x01\x02'
    off = struct.unpack_from('>I', b, 32)[0]
    entsize, count, stridx = struct.unpack_from('>HHH', b, 46)
    headers = [struct.unpack_from('>10I', b, off+i*entsize) for i in range(count)]
    def data(h): return b[h[4]:h[4]+h[5]]
    def name(buf, i): return buf[i:buf.index(b'\0',i)].decode()
    names = data(headers[stridx])
    sections = {name(names,h[0]):data(h) for h in headers}
    symbols = []
    for h in headers:
        if h[1] == 2:
            strings = data(headers[h[6]])
            for o in range(h[4],h[4]+h[5],h[9]):
                n,value,size,info,other,section = struct.unpack_from('>IIIBBH',b,o)
                symbols.append({'name':name(strings,n),'value':value,'size':size,'section':name(names,headers[section][0]) if section<count else str(section)})
    relocs=[]
    for h in headers:
        if h[1]==4 and name(names,headers[h[7]][0])=='.text':
            for o in range(h[4],h[4]+h[5],h[9]):
                offset,info,addend=struct.unpack_from('>IIi',b,o)
                relocs.append({'offset':offset,'type':info&255,'addend':addend,'target':symbols[info>>8]})
    return sections,relocs

left_path='build/GEDE01/obj/game/game_fn_8018F378.o'
right_path='build/GEDE01/src/game/game_fn_8018F378.o'
l,lr=elf(left_path)
r,rr=elf(right_path)
assert l['.text']==r['.text'] and len(l['.text'])==892
assert l['.sdata2']==r['.sdata2'] and len(l['.sdata2'])==8
assert len(lr)==len(rr)==30
comparisons=[]
for a,b in zip(lr,rr):
    assert (a['offset'],a['type'],a['addend'])==(b['offset'],b['type'],b['addend'])
    x,y=a['target'],b['target']
    if x['name']!=y['name']:
        assert x['name']=='lbl_80650AD0' and y['name']=='@38'
        assert x['section']==y['section']=='.sdata2' and x['value']==y['value']==0
        identity='same local .sdata2+0 target; complete eight-byte section byte-identical'
    else:
        assert x['section']==y['section'] and x['value']==y['value']
        identity='same symbol, section, value, relocation type, and addend'
    comparisons.append({'retail':a,'generated':b,'identity':identity})
outputs=[]
for name,args in [('canonical',[]),('strict',['-c','functionRelocDiffs=all'])]:
    out=reports/(('objdiff-' if name=='strict' else 'canonical-')+assignment+'.json')
    outputs.append(command(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_8018F378','fn_8018F378',*args,'-o',str(out),'--format','json-pretty']))
    d=json.loads(out.read_text())
    symbol=next(s for s in d['left']['symbols'] if s['name']=='fn_8018F378')
    assert symbol['match_percent']==100
    assert all(i.get('diff_kind') in (None,'DIFF_NONE') for i in symbol['instructions'])
outputs.append(command(['readelf','-r',left_path]))
outputs.append(command(['readelf','-r',right_path]))
outputs.append(command(['.tools/bin/ninja','-t','commands',right_path]))
outputs.append(command(['sha1sum','build/GEDE01/main.dol']))
sha=hashlib.sha1(Path('build/GEDE01/main.dol').read_bytes()).hexdigest()
assert sha=='ea24b6af954876ce072562ff39cdb4c81d32be1f'
outputs.append(command(['python3','tools/legal_audit.py']))
result={'assignment_id':assignment,'canonical_percent':100.0,'relocation_strict_percent':100.0,'text_size':892,'text_bytes_equal':True,'text_sha256':hashlib.sha256(l['.text']).hexdigest(),'sdata2_bytes_equal':True,'sdata2_sha256':hashlib.sha256(l['.sdata2']).hexdigest(),'relocation_count_each':30,'relocation_comparisons':comparisons,'dol_sha1':sha,'commands':outputs}
(reports/('verification-'+assignment+'.json')).write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps({k:v for k,v in result.items() if k not in ('commands','relocation_comparisons')},indent=2))
