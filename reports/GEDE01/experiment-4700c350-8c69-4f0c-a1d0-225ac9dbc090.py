"""Bounded GC/1.3 source-shape experiments for fn_8019B4D4 only.
Run from eternal-darkness-decomp. Restores the input TU after each batch.
"""
import hashlib
import json
from pathlib import Path
import subprocess
import sys

SOURCE = Path('src/game/game_fn_8019B4D4.c')
PREFIX = Path('reports/GEDE01') / 'trials-4700c350-8c69-4f0c-a1d0-225ac9dbc090'
original = SOURCE.read_text()
base = subprocess.check_output(['git', 'show', '10fdcd7986777cd8ec6ecd6fb156ba9d46241a87:eternal-darkness-decomp/src/game/game_fn_8019B4D4.c'], text=True)
if sys.argv[1] in ['scale', 'texture', 'inline_setup', 'global_struct']:
    base = base.replace('if (config[0x16] != 0)', 'if ((u8)((s8*)config)[0x16] != 0)')
variants = []
if sys.argv[1] == 'float':
    params = ['void*', 'int', 'u8', 'int', 'void*']
    args = ['entry + 0x20', '4', 'config[1]', '0', 'default_texture']
    for pos in range(5):
        p = params.copy(); p.insert(pos, 'float')
        a = args.copy(); a.insert(pos, 'lbl_80650BF8')
        variants.append((f'float_position_{pos}', [
            ('extern void fn_801805E0(void*, int, u8, int, void*, float);',
             'extern void fn_801805E0(' + ', '.join(p) + ');'),
            ('fn_801805E0(entry + 0x20, 4, config[1], 0, default_texture,\n                lbl_80650BF8);', 'fn_801805E0(' + ', '.join(a) + ');')]))
elif sys.argv[1] == 'field':
    for typ in ['s8', 'u8', 'char']:
        for read in ['field', 'cast']:
            variants.append((f'typed_{typ}_{read}', [
                ('typedef struct SixBytes {', f'typedef struct ConfigPrefix {{\n    u8 pad[0x16];\n    {typ} count;\n}} ConfigPrefix;\n\ntypedef struct SixBytes {{'),
                ('if (config[0x16] != 0)', 'if (((ConfigPrefix*)config)->count != 0)'),
                ('((s8*)config)[0x16]', '((ConfigPrefix*)config)->count' if read == 'field' else '(s8)((ConfigPrefix*)config)->count')]))
elif sys.argv[1] == 'locals':
    for typ in ['u8','s8','int','unsigned int']:
        for expr in ['count','(s8)count']:
            variants.append((f'local_{typ}_{expr}', [
                ('    Texture* default_texture;', f'    Texture* default_texture;\n    {typ} count;'),
                ('    if (config[0x16] != 0)', '    count = config[0x16];\n    if (count != 0)'),
                ('((s8*)config)[0x16]', expr)]))
elif sys.argv[1] == 'address':
    for expr in ['&entry[0x20]', '(void*)((u32)entry + 0x20)', '&((Entry*)entry)->data', '((Entry*)entry)->data', 'entry + (u8)0x20']:
        variants.append((expr, [('typedef struct SixBytes {','typedef struct Entry { u8 pad[0x20]; u8 data[0x20]; } Entry;\n\ntypedef struct SixBytes {'), ('fn_801805E0(entry + 0x20,', 'fn_801805E0('+expr+',')]))
    for typ in ['u8','s8','u16','s16','u32']:
        variants.append(('count_parameter_'+typ,[('fn_801805E0(void*, int, u8, int, void*, float)', 'fn_801805E0(void*, '+typ+', u8, int, void*, float)')]))
elif sys.argv[1] == 'signed_load':
    for expr in ['*(s8*)(config + 0x16)', '(int)*(s8*)(config + 0x16)', '(s16)*(s8*)(config + 0x16)', '(s8)*(s8*)(config + 0x16)', '((SignedByte*)config)[0x16].value', '((SignedConfig*)config)->count', '((SignedUnion*)config)[0x16].signed_value']:
        variants.append((expr, [('typedef struct SixBytes {','typedef struct SignedByte { s8 value; } SignedByte;\ntypedef struct SignedConfig { u8 pad[0x16]; s8 count; } SignedConfig;\ntypedef union SignedUnion { s8 signed_value; u8 unsigned_value; } SignedUnion;\n\ntypedef struct SixBytes {'), ('((s8*)config)[0x16]',expr)]))
    for typ in ['u8','s8']:
        for expr in ['*(s8*)&count','((SignedUnion*)&count)->signed_value']:
            variants.append(('local_alias_'+typ+'_'+expr,[('typedef struct SixBytes {','typedef union SignedUnion { s8 signed_value; u8 unsigned_value; } SignedUnion;\n\ntypedef struct SixBytes {'), ('    Texture* default_texture;', '    Texture* default_texture;\n    '+typ+' count;'),('    if (config[0x16] != 0)', '    count = config[0x16];\n    if ((u8)count != 0)'),('((s8*)config)[0x16]',expr)]))
elif sys.argv[1] == 'temporaries':
    import itertools
    old = '        fn_8018E230(entry, entry + 0x2B, 1, 0,\n                    ((s8*)config)[0x16], config[0x17]);'
    for order in itertools.permutations(['alpha','count','stride']):
        for expr in ['(s8)config[0x16]', '((s8*)config)[0x16]']:
            decl = {'alpha': 'u8* alpha = entry + 0x2B;', 'count': 'int count = '+expr+';', 'stride':'int stride = config[0x17];'}
            new = '\n'.join('        '+decl[k] for k in order)+'\n        fn_8018E230(entry, alpha, 1, 0, count, stride);'
            variants.append(('_'.join(order)+'_'+expr,[(old,new)]))
    old_call = '    fn_801805E0(entry + 0x20, 4, config[1], 0, default_texture,\n                lbl_80650BF8);'
    for order in itertools.permutations(['data','count','value']):
        decl = {'data': 'u8* data = entry + 0x20;', 'count': 'int count = 4;', 'value': 'u8 value = config[1];'}
        new = '    {\n'+'\n'.join('        '+decl[k] for k in order)+'\n        fn_801805E0(data, count, value, 0, default_texture, lbl_80650BF8);\n    }'
        variants.append(('setup_'+'_'.join(order),[(old_call,new)]))
elif sys.argv[1] == 'bitfield':
    for typ in ['signed char','signed int']:
        for signed_compare in [False,True]:
            replacements=[('typedef struct SixBytes {','typedef struct SignedConfig { u8 pad[0x16]; '+typ+' count : 8; } SignedConfig;\n\ntypedef struct SixBytes {'), ('((s8*)config)[0x16]','((SignedConfig*)config)->count')]
            if signed_compare:
                replacements.append(('if (config[0x16] != 0)','if ((u8)((SignedConfig*)config)->count != 0)'))
            variants.append((typ+'_unsigned_compare_'+str(signed_compare),replacements))
elif sys.argv[1] == 'conditions':
    for cond in ['(u8)((s8*)config)[0x16] != 0','(u32)config[0x16] != 0','config[0x16] > 0','!!config[0x16]','((s8*)config)[0x16] & 0xff','(u8)((s8*)config)[0x16] > 0']:
        variants.append((cond,[('config[0x16] != 0',cond)]))
elif sys.argv[1] == 'scale':
    variants.append(('double_scale',[('void*, float);','void*, double);')]))
    call = '    fn_801805E0(entry + 0x20, 4, config[1], 0, default_texture,\n                lbl_80650BF8);'
    for typ in ['float','double']:
        for where in ['before_default','after_default']:
            assignment = '    default_texture = (Texture*)(lbl_802FC5BC + 0xC);'
            load = '    scale = lbl_80650BF8;'
            replacement = load+'\n'+assignment if where == 'before_default' else assignment+'\n'+load
            variants.append((typ+'_'+where,[('    Texture* default_texture;','    Texture* default_texture;\n    '+typ+' scale;'),(assignment,replacement),(call,call.replace('lbl_80650BF8','scale'))]))
elif sys.argv[1] == 'texture':
    assign = '    default_texture = (Texture*)(lbl_802FC5BC + 0xC);'
    for expr in ['&((Texture*)lbl_802FC5BC)[3]', '(Texture*)lbl_802FC5BC + 3', '(Texture*)((u32)lbl_802FC5BC + 0xC)']:
        variants.append((expr, [(assign, '    default_texture = '+expr+';')]))
    for typ in ['u8*','void*','u32*','const Texture*']:
        cast = '(Texture*)' if typ in ['void*','u8*','u32*'] else ''
        variants.append(('texture_type_'+typ, [('Texture* default_texture;',typ+' default_texture;'), ('default_texture = (Texture*)','default_texture = ('+typ+')'), ('selected_texture = *default_texture;', 'selected_texture = *('+cast+'default_texture);')]))
    variants.append(('init_in_argument',[(assign,''),('0, default_texture,\n                lbl_80650BF8','0, (default_texture = (Texture*)(lbl_802FC5BC + 0xC)),\n                lbl_80650BF8')]))
elif sys.argv[1] == 'inline_setup':
    import itertools
    old = '    fn_801805E0(entry + 0x20, 4, config[1], 0, default_texture,\n                lbl_80650BF8);'
    for order in itertools.permutations(['entry','value','texture']):
        for inner_offset in [True,False]:
            params = {'entry':'u8* entry', 'value':'u8 value', 'texture':'Texture* texture'}
            args = {'entry':'entry' if inner_offset else 'entry + 0x20', 'value':'config[1]', 'texture':'default_texture'}
            helper = 'static inline void initialize_palette('+', '.join(params[k] for k in order)+', float scale)\n{\n    fn_801805E0('+('entry + 0x20' if inner_offset else 'entry')+', 4, value, 0, texture, scale);\n}\n\n'
            variants.append(('_'.join(order)+'_offset_'+str(inner_offset), [('void fn_8019B4D4(',helper+'void fn_8019B4D4('), (old,'    initialize_palette('+', '.join(args[k] for k in order)+', lbl_80650BF8);')]))
elif sys.argv[1] == 'global_struct':
    for decl,expr in [('struct Palette { u8 pad[12]; Texture texture; }','&lbl_802FC5BC.texture'),('struct Palette { Texture textures[4]; }','&lbl_802FC5BC.textures[3]')]:
        variants.append((decl,[('extern u8 lbl_802FC5BC[];',decl+';\nextern struct Palette lbl_802FC5BC;'),('default_texture = (Texture*)(lbl_802FC5BC + 0xC);','default_texture = '+expr+';')]))
else:
    raise SystemExit('unknown batch')
results = []
try:
    for name, replacements in variants:
        source = base
        for old,new in replacements:
            assert old in source, old
            source = source.replace(old,new)
        SOURCE.write_text(source)
        build = subprocess.run(['.tools/bin/ninja','-j2','build/GEDE01/src/game/game_fn_8019B4D4.o'],text=True,capture_output=True)
        row = {'name': name, 'replacements':replacements,'source_sha256':hashlib.sha256(source.encode()).hexdigest(), 'build_returncode':build.returncode,'build_stdout':build.stdout,'build_stderr':build.stderr}
        if build.returncode == 0:
            diff = subprocess.run(['build/tools/objdiff-cli','diff','-p','.','-u','main/game/game_fn_8019B4D4','fn_8019B4D4','-o','-','--format','json'],capture_output=True,text=True,check=True)
            d = json.loads(diff.stdout)
            l,r = [next(s for s in d[k]['symbols'] if s['name']=='fn_8019B4D4') for k in ['left','right']]
            row.update(score=l.get('match_percent'),left_size=l['size'],right_size=r['size'])
            row['different_rows'] = [{'offset':hex(i*4),'left':a,'right':b} for i,(a,b) in enumerate(zip(l['instructions'],r['instructions'])) if a.get('diff_kind') not in (None,'DIFF_NONE') or a.get('instruction',{}).get('formatted') != b.get('instruction',{}).get('formatted')]
            print(name, row['score'], row['right_size'], [(x['offset'],x['left'].get('instruction',{}).get('formatted'),x['right'].get('instruction',{}).get('formatted')) for x in row['different_rows']],flush=True)
        else:
            print(name,'BUILD ERROR',build.stdout,build.stderr,flush=True)
        results.append(row)
finally:
    SOURCE.write_text(original)
    Path(str(PREFIX)+'-'+sys.argv[1]+'.json').write_text(json.dumps(results,indent=2)+'\n')
