import collections
import hashlib
import json
import subprocess
from pathlib import Path

out = Path(__file__).resolve().parent
root = out.parents[2]
commands = []
def run(args, file=None, expected=0):
    result = subprocess.run(args, cwd=root, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    commands.append({'command': args, 'exit_code': result.returncode, 'raw_output': result.stdout})
    if file:
        (out/file).write_text(result.stdout)
    (out/'verification-commands.json').write_text(json.dumps(commands, indent=2)+'\n')
    assert result.returncode == expected, result.stdout
    return result.stdout

run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_801D1F78.externalized'])
for name, extra in [('canonical-final', []), ('strict-final', ['-c','function_reloc_diffs=name_address'])]:
    run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_801D1F78','-o',str((out/(name+'.json')).relative_to(root)),'--format','json']+extra+['fn_801D1F78'])
relocations = {}
for name, branch in [('retail', 'obj'), ('candidate', 'src')]:
    raw=run(['build/binutils/powerpc-eabi-readelf','-r',f'build/GEDE01/{branch}/game/game_fn_801D1F78.o'], 'relocations-'+name+'.txt')
    entries=[]
    for line in raw.splitlines():
        fields=line.split()
        if len(fields)>=7 and fields[2].startswith('R_PPC_'):
            entries.append({'offset':fields[0], 'type':fields[2], 'target':fields[4], 'addend': ' '.join(fields[5:])})
    relocations[name]=entries
signature=lambda rows: collections.Counter((r['type'],r['target'],r['addend']) for r in rows)
relocations['targets_and_addends_equal']=signature(relocations['retail'])==signature(relocations['candidate'])
relocations['note']='Entry constant-load relocation offsets differ with instruction scheduling; compare targets/addends by identity, not raw offset.'
assert len(relocations['retail'])==len(relocations['candidate'])==12
assert relocations['targets_and_addends_equal']
(out/'relocations.json').write_text(json.dumps(relocations,indent=2)+'\n')
raw=run(['sha1sum','build/GEDE01/main.dol'], 'dol-sha1.txt')
assert raw.split()[0]=='ea24b6af954876ce072562ff39cdb4c81d32be1f'
run(['cmp','-s','build/GEDE01/main.dol','orig/GEDE01/sys/main.dol'])
run(['python3','tools/legal_audit.py'], 'legal-audit.txt')
run(['rg','-n',r'#pragma|\b(__asm|asm)\b','src/game/game_fn_801D1F78.c'], 'source-audit.txt', expected=1)
run(['.tools/bin/ninja','-t','commands','build/GEDE01/src/game/game_fn_801D1F78.o'], 'compiler-command.txt')
source=root/'src/game/game_fn_801D1F78.c'
accepted=subprocess.check_output(['git','show','04406695020be4fff635886ca9b72736fa330c6a:eternal-darkness-decomp/src/game/game_fn_801D1F78.c'],cwd=root)
assert source.read_bytes()==accepted
summary={'source_sha256':hashlib.sha256(source.read_bytes()).hexdigest(), 'source_equals_accepted_base':True, 'registration':'NonMatching; GC/1.3; -use_lmw_stmw on', 'dol_note':'NonMatching retains retail assembly in linked DOL; DOL verification does not establish a C match.'}
for name in ['canonical-final','strict-final']:
    d=json.loads((out/(name+'.json')).read_text())
    symbols={side:next(s for s in d[side]['symbols'] if s['name']=='fn_801D1F78') for side in ['left','right']}
    summary[name]={side:{'size':s['size'],'match_percent':s.get('match_percent'),'instruction_count':len([i for i in s['instructions'] if i.get('instruction')])} for side,s in symbols.items()}
    if name=='canonical-final':
        streams={side:[i['instruction'] for i in s['instructions'] if i.get('instruction')] for side,s in symbols.items()}
        differences=[{'offset':a.get('address','0'),'retail':a['formatted'],'candidate':b['formatted']} for a,b in zip(streams['left'],streams['right']) if a['formatted']!=b['formatted']]
        summary['same_offset_instruction_differences']=differences
        assert all(int(x['offset'])<88 for x in differences)
(out/'measurements.json').write_text(json.dumps(summary,indent=2)+'\n')
print(json.dumps(summary,indent=2))
