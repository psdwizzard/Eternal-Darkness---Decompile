"""Assignment-only scalar-replacement probes; restores the accepted TU/registration."""
from pathlib import Path
import subprocess, json, re, difflib, itertools, sys
src = Path('src/game/game_fn_801D76A8.c')
saved_source = src.read_text()
base = subprocess.check_output(['git','show','fe7d01583e5621ec4242a18bf7e66e5556831c3b:eternal-darkness-decomp/src/game/game_fn_801D76A8.c'],text=True)
cfg = Path('configure.py')
saved_registration = cfg.read_text()
cfgbase = subprocess.check_output(['git','show','fe7d01583e5621ec4242a18bf7e66e5556831c3b:eternal-darkness-decomp/configure.py'],text=True)
aid = 'c010e819-de0c-4571-9ff6-e1b5de78aa5d'
log = Path(f'reports/GEDE01/experiments-{aid}.json')
records = json.loads(log.read_text())
variants = []
types = {'result':'int', 'effect':'void*', 'count':'u8'}
types['kind'] = 'int'
phase = sys.argv[1] if len(sys.argv) > 1 else '1'
groups = [('result',),('effect',),('count',),('result','effect'),('result','count'),('effect','count')] if phase == '1' else [('result','effect','kind'),('result','kind'),('result','kind','effect','count'),('count','effect','kind','result')]
for members in groups:
    s = base
    decl = '    struct { ' + ' '.join(types[m]+' '+m+';' for m in members) + ' } state;'
    for i,m in enumerate(members):
        s = s.replace('    '+types[m]+' '+m+';\n', (decl+'\n') if i == 0 else '')
    split=s.index('    effect =')
    s=s[:split]+re.sub(r'\b('+'|'.join(members)+r')\b',r'state.\1',s[split:])
    variants.append(('aggregate-'+'-'.join(members),s))
if phase == '2':
    for name, decl in [('bitfield-count', 'struct { unsigned int count:8; } counts;'), ('word-union-count', 'union { u8 count; u32 storage; } counts;')]:
        s=base.replace('    int result;', '    struct { int result; } state;').replace('    u8 count;', '    '+decl)
        split=s.index('    effect =')
        s=s[:split]+re.sub(r'\bresult\b', 'state.result', re.sub(r'\bcount\b','counts.count',s[split:]))
        variants.append((name,s))
if phase == '3':
    variants = [('u8-setter-baseline', base.replace('fn_801A7670(void*, int)', 'fn_801A7670(void*, u8)'))]
    for members in [('result',), ('result', 'effect')]:
        s=base
        decl='    struct { '+' '.join(types[m]+' '+m+';' for m in members)+' } state;'
        for i,m in enumerate(members):
            s=s.replace('    '+types[m]+' '+m+';\n', (decl+'\n') if i == 0 else '')
        split=s.index('    effect =')
        s=s[:split]+re.sub(r'\b('+'|'.join(members)+r')\b',r'state.\1',s[split:])
        variants.append(('u8-setter-'+'-'.join(members),s.replace('fn_801A7670(void*, int)', 'fn_801A7670(void*, u8)')))
try:
    for name,s in variants:
        src.write_text(s)
        rec={'name':name,'hypothesis':'Narrow aggregate scalar replacement to preserve direct call-result staging with less register recoloring.', 'patch':''.join(difflib.unified_diff(base.splitlines(True),s.splitlines(True))), 'commands':[]}
        records.append(rec)
        def run(cmd):
            p=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
            rec['commands'].append({'argv':cmd,'exit_code':p.returncode,'output':p.stdout})
            p.check_returncode()
            return p.stdout
        run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_801D76A8.o'])
        syms=run(['build/binutils/powerpc-eabi-objdump','-t','build/GEDE01/src/game/game_fn_801D76A8.o'])
        sym=re.search(r'\.sdata2\s+00000008 (@\d+)',syms)[1]
        start=cfgbase.index('"name": "externalize_game_801D76A8_signed_bias"')
        end=cfgbase.index('"description":',start)
        cfg.write_text(cfgbase[:start]+cfgbase[start:end].replace('@26',sym)+cfgbase[end:])
        run(['python3','configure.py'])
        run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_801D76A8.externalized'])
        out=f'reports/GEDE01/objdiff-{aid}-{name}.json'
        run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_801D76A8','fn_801D76A8','-c','function_reloc_diffs=name_address','-o',out])
        d=json.loads(Path(out).read_text())
        a=next(x for x in d['left']['symbols'] if x['name']=='fn_801D76A8')
        b=next(x for x in d['right']['symbols'] if x['name']=='fn_801D76A8')
        rec.update(score=a['match_percent'],generated_size=b['size'])
        print(name,rec['score'],rec['generated_size'],flush=True)
        log.write_text(json.dumps(records,indent=2)+'\n')
finally:
    src.write_text(saved_source)
    cfg.write_text(saved_registration)
    log.write_text(json.dumps(records,indent=2)+'\n')
    subprocess.run(['python3','configure.py'],check=True)
    subprocess.run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_801D76A8.externalized'],check=True)
