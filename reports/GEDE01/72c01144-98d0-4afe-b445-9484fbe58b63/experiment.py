"""Assignment 72c01144: test inline expansion and local address-taking under canonical flags.

Run from eternal-darkness-decomp. Only the assigned TU is compiled/changed;
the original source is restored, and no alternative C files are retained.
"""
import hashlib
import json
from pathlib import Path
import subprocess

REPORT = Path('reports/GEDE01/72c01144-98d0-4afe-b445-9484fbe58b63')
SOURCE = Path('src/game/game_fn_8008A96C.c')
BASE = subprocess.check_output(['git', 'show', '920ee92c98de929345e64d1683eeb63df33f6379:eternal-darkness-decomp/src/game/game_fn_8008A96C.c'], text=True)

def helper(source, definition):
    return source.replace('/* NonMatching:', definition + '\n/* NonMatching:')

variants = {}
for order, signature, call in [
    ('destination-first', 'Vec3* dst, void* obj', '&temp, relatedPosition'),
    ('object-first', 'void* obj, Vec3* dst', 'relatedPosition, &temp'),
]:
    variants['inline-position-' + order] = helper(BASE, 'static inline void readRelatedPosition(' + signature + ')\n{\n    void* value = fn_80201BC8(obj);\n    fn_8011F114(dst, value);\n}\n').replace('fn_8011F114(&temp, fn_80201BC8(relatedPosition));', 'readRelatedPosition(' + call + ');')
variants['inline-position-output-pointer'] = helper(BASE, 'static inline void getPositionSource(void* obj, void** output)\n{\n    *output = fn_80201BC8(obj);\n}\n').replace('fn_8011F114(&temp, fn_80201BC8(relatedPosition));', 'getPositionSource(relatedPosition, &relatedPosition);\n            fn_8011F114(&temp, relatedPosition);')
variants['inline-owner-output-pointer'] = helper(BASE, 'static inline void getOwner(void* obj, void** owner, int* success)\n{\n    *owner = (void*)fn_80201B54(obj);\n    *success = 0;\n}\n').replace('owner = ((void*)fn_80201B54(object));\n    success = 0;', 'getOwner(object, &owner, &success);')
for order, signature, call in [
    ('table-first', 'void* table, int offset, int field', 'table, offset, '),
    ('offset-first', 'int offset, void* table, int field', 'offset, table, '),
]:
    variants['inline-byte-' + order] = helper(BASE, 'static inline int tableByte(' + signature + ')\n{\n    return *((u8*)table + offset + field);\n}\n').replace('*((u8*)table + offset + 0x2B)', 'tableByte(' + call + '0x2B)').replace('*((u8*)table + offset + 0x2A)', 'tableByte(' + call + '0x2A)')


# Symbol numbering may control commutative operand normalization and scheduling.
variants['offset-declared-after-table'] = BASE.replace('    int offset;\n', '').replace('    void* table;','    void* table;\n    int offset;')
variants['success-declared-before-owner'] = BASE.replace('    void* owner;\n    int success;', '    int success;\n    void* owner;')
variants['position-reuses-related-local'] = BASE.replace('fn_8011F114(&temp, fn_80201BC8(relatedPosition));', 'relatedPosition = fn_80201BC8(relatedPosition);\n            fn_8011F114(&temp, relatedPosition);')
variants['position-address-local'] = BASE.replace('        Vec3 temp;', '        Vec3 temp;\n        Vec3* destination = &temp;').replace('fn_8011F114(&temp, fn_80201BC8(relatedPosition));', 'relatedPosition = fn_80201BC8(relatedPosition);\n            fn_8011F114(destination, relatedPosition);')
variants['owner-register-local'] = BASE.replace('    void* owner;', '    register void* owner;')
variants['success-register-local'] = BASE.replace('    int success;', '    register int success;')

for local in ['object2', 'unused', 'effect', 'config', 'table']:
    variants['reuse-dead-' + local] = BASE.replace('fn_8011F114(&temp, fn_80201BC8(relatedPosition));', local + ' = fn_80201BC8(relatedPosition);\n            fn_8011F114(&temp, ' + local + ');')
variants['table-unsigned-address'] = BASE.replace('    void* table;', '    u32 table;').replace('table = fn_80072354(info->field90);', 'table = (u32)fn_80072354(info->field90);').replace('*((u8*)table + offset + 0x2B)', '*(u8*)(table + offset + 0x2B)').replace('*((u8*)table + offset + 0x2A)', '*(u8*)(table + offset + 0x2A)')
variants['table-signed-address'] = variants['table-unsigned-address'].replace('    u32 table;', '    int table;').replace('table = (u32)fn_80072354', 'table = (int)fn_80072354')
variants['table-integer-expression'] = BASE.replace('*((u8*)table + offset + 0x2B)', '*(u8*)((u32)table + (u32)offset + 0x2B)').replace('*((u8*)table + offset + 0x2A)', '*(u8*)((u32)table + (u32)offset + 0x2A)')
variants['result-branch-initialization'] = BASE.replace('    success = 0;\n', '').replace('    return success;', '    else {\n        success = 0;\n    }\n    return success;').replace('        void* relatedPosition;', '        void* relatedPosition;').replace('        Vec3 temp;', '        Vec3 temp;\n        success = 0;')

BETTER = variants['reuse-dead-effect']
variants['reuse-result-flags'] = BETTER.replace('    flags = fn_80128EE4(resource);', '    success = fn_80128EE4(resource);').replace('    success = 0;\n', '    flags = success;\n    success = 0;\n')
variants['reuse-result-mask'] = BETTER.replace('    flags = fn_80128EE4(resource);', '    success = fn_80128EE4(resource);').replace('    success = 0;\n', '    flags = success & 0x20;\n    success = 0;\n').replace('(flags & 0x20) == 0', 'flags == 0')
variants['owner-reuse-unused'] = BETTER.replace('owner = ((void*)fn_80201B54(object));', 'unused = (void*)fn_80201B54(object);\n    owner = unused;')
variants['owner-reuse-object2'] = BETTER.replace('owner = ((void*)fn_80201B54(object));', 'object2 = (void*)fn_80201B54(object);\n    owner = object2;')
variants['owner-reuse-effect'] = BETTER.replace('owner = ((void*)fn_80201B54(object));', 'effect = (void*)fn_80201B54(object);\n    owner = effect;')
variants['result-reuse-flags'] = BETTER.replace('    success = 0;', '    success = flags;\n    flags = 0;').replace('if ((flags & 0x20) == 0)', 'if ((success & 0x20) == 0)').replace('                    success = 1;', '                    flags = 1;').replace('return success;', 'return flags;')
# Reusing existing dead pointer locals for the selected byte offset can alter
# pointer-add operand selection without introducing a new runtime operation.
variants['offset-pointer'] = BETTER.replace('    int offset;', '    u8* offset;').replace('offset = (selection != 4) << 3;', 'offset = (u8*)((selection != 4) << 3);').replace('*((u8*)table + offset + 0x2B)', '*(offset + (u32)table + 0x2B)').replace('*((u8*)table + offset + 0x2A)', '*(offset + (u32)table + 0x2A)')
variants['offset-pointer-reuse-related'] = BETTER.replace('offset = (selection != 4) << 3;', 'related = (u8*)((selection != 4) << 3);').replace('*((u8*)table + offset + 0x2B)', '*((u8*)related + (u32)table + 0x2B)').replace('*((u8*)table + offset + 0x2A)', '*((u8*)related + (u32)table + 0x2A)')
variants['offset-unsigned'] = BETTER.replace('    int offset;', '    u32 offset;')

variants['result-init-declaration'] = BETTER.replace('    int success;', '    int success = 0;').replace('    success = 0;\n', '')
variants['result-init-before-owner-call'] = BETTER.replace('    success = 0;\n', '').replace('    owner =', '    success = 0;\n    owner =')
variants['result-init-before-related-call'] = BETTER.replace('    success = 0;\n', '').replace('    related =', '    success = 0;\n    related =')
variants['owner-declaration-at-call'] = BETTER.replace('    void* owner;\n', '').replace('    owner =', '    void* owner =')
variants['table-byte-array'] = BETTER.replace('    void* table;', '    u8 (*table)[1];').replace('table = fn_80072354(info->field90);', 'table = (u8 (*)[1])fn_80072354(info->field90);').replace('*((u8*)table + offset + 0x2B)', 'table[offset][0x2B]').replace('*((u8*)table + offset + 0x2A)', 'table[offset][0x2A]')
variants['table-volatile-bytes'] = BETTER.replace('*((u8*)table + offset', '*((volatile u8*)table + offset')
variants['table-volatile-integer-address'] = variants['table-integer-expression'].replace('fn_8011F114(&temp, fn_80201BC8(relatedPosition));', 'effect = fn_80201BC8(relatedPosition);\n            fn_8011F114(&temp, effect);').replace('*(u8*)', '*(volatile u8*)')
variants['table-struct-byte'] = BETTER.replace('typedef struct ObjectInfo {', 'typedef struct TableByte { u8 value; } TableByte;\n\ntypedef struct ObjectInfo {').replace('*((u8*)table + offset + 0x2B)', '((TableByte*)table)[offset + 0x2B].value').replace('*((u8*)table + offset + 0x2A)', '((TableByte*)table)[offset + 0x2A].value')

# Keep every byte access within its declared array bound in candidate source.
variants['table-byte-array-inbounds'] = variants['table-byte-array'].replace('table[offset][0x2B]', 'table[offset + 0x2B][0]').replace('table[offset][0x2A]', 'table[offset + 0x2A][0]')
variants['table-array-view'] = variants['table-byte-array'].replace('(*table)[1]', '(*table)[0x34]').replace('(u8 (*)[1])', '(u8 (*)[0x34])').replace('table[offset][0x2B]', '(*((u8 (*)[0x34])((u8*)table + offset)))[0x2B]').replace('table[offset][0x2A]', '(*((u8 (*)[0x34])((u8*)table + offset)))[0x2A]')
variants['table-array-view-exact-record'] = variants['table-array-view'].replace('[0x34]', '[0x2C]')
variants['table-array-full-width'] = variants['table-array-view'].replace('(*((u8 (*)[0x34])((u8*)table + offset)))[0x2B]', '(*table)[offset + 0x2B]').replace('(*((u8 (*)[0x34])((u8*)table + offset)))[0x2A]', '(*table)[offset + 0x2A]')
variants['table-record-view'] = BETTER.replace('typedef struct ObjectInfo {', 'typedef struct TableRecord { u8 pad[0x2A]; u8 field2A, field2B; } TableRecord;\n\ntypedef struct ObjectInfo {').replace('*((u8*)table + offset + 0x2B)', '((TableRecord*)((u8*)table + offset))->field2B').replace('*((u8*)table + offset + 0x2A)', '((TableRecord*)((u8*)table + offset))->field2A')
# Scope the owner initialization as a declaration inside a C89 compound block.
variants['owner-nested-initializer'] = BETTER.replace('    void* owner;\n', '').replace('    owner =', '    {\n    void* owner =').replace('    return success;', '    }\n    return success;')
variants['owner-result-struct'] = BETTER.replace('    void* owner;\n    int success;', '    struct { void* owner; int success; } state;').replace('owner =', 'state.owner =').replace('success =', 'state.success =').replace('config, owner)', 'config, state.owner)').replace('return success;', 'return state.success;')
variants['owner-result-union'] = BETTER.replace('    void* owner;', '    union { void* pointer; u32 word; } owner;').replace('owner =', 'owner.pointer =').replace('config, owner)', 'config, owner.pointer)')

BEST = variants['table-array-full-width']
for ctype in ['unsigned int', 'unsigned char', 'signed char', 'short', 'unsigned short', 'long']:
    variants['success-type-' + ctype.replace(' ', '-')] = BEST.replace('    int success;', '    ' + ctype + ' success;')
for anchor in ['    ObjectInfo* info', '    void* related;', '    int flags;', '    int i;', '    int count;']:
    variants['success-before-' + anchor.strip().split()[-1].replace(';','').replace('info','info-init')] = BEST.replace('    int success;\n', '').replace(anchor, '    int success;\n' + anchor)
for anchor in ['    ObjectInfo* info', '    void* related;', '    int flags;', '    int i;', '    int count;']:
    variants['owner-before-' + anchor.strip().split()[-1].replace(';','').replace('info','info-init')] = BEST.replace('    void* owner;\n', '').replace(anchor, '    void* owner;\n' + anchor)
variants['success-enum'] = BEST.replace('    int success;', '    enum { FAILURE = 0, SUCCESS = 1 } success;').replace('success = 0;', 'success = FAILURE;').replace('success = 1;', 'success = SUCCESS;')

variants['success-comma-condition'] = BEST.replace('    success = 0;\n','').replace('if ((flags & 0x20) == 0)', 'if ((success = 0, flags & 0x20) == 0)')
variants['success-ternary-condition'] = BEST.replace('    success = 0;\n','').replace('if ((flags & 0x20) == 0)', 'if ((flags & 0x20) ? (success = 0, 0) : (success = 0, 1))')
variants['flags-early-return'] = BEST.replace('    if ((flags & 0x20) == 0) {', '    if ((flags & 0x20) != 0) return success;\n    {')
variants['flags-early-goto'] = BEST.replace('    if ((flags & 0x20) == 0) {', '    if ((flags & 0x20) != 0) goto done;\n    {').replace('    return success;', 'done:\n    return success;')
variants['flags-do-break'] = BEST.replace('    if ((flags & 0x20) == 0) {', '    do {').replace('        Vec3 temp;', '        Vec3 temp;\n        if (flags & 0x20) break;').replace('    }\n    return success;', '    } while (0);\n    return success;')
variants['flags-if-else'] = BEST.replace('    if ((flags & 0x20) == 0) {', '    if ((flags & 0x20) != 0) {\n    } else {')
variants['flags-unsigned-char'] = BEST.replace('    int flags;', '    unsigned char flags;')
variants['flags-unsigned-int'] = BEST.replace('    int flags;', '    unsigned int flags;')
variants['flags-bitfield'] = BEST.replace('    int flags;', '    struct { unsigned pad : 26; unsigned blocked : 1; unsigned low : 5; } flags;').replace('flags = fn_80128EE4(resource);', '*(u32*)&flags = fn_80128EE4(resource);').replace('(flags & 0x20) == 0', 'flags.blocked == 0')
variants['success-used-as-offset'] = BEST.replace('offset = (selection != 4) << 3;', 'success = (selection != 4) << 3;').replace('(*table)[offset +', '(*table)[success +')
variants['owner-stored-in-parameter'] = BEST.replace('    void* owner;\n', '').replace('owner = ((void*)fn_80201B54(object));', 'unused = (void*)fn_80201B54(object);').replace('config, owner)', 'config, unused)')

for ctype in ['int', 'u32']:
    variants['owner-scalar-' + ctype] = BEST.replace('    void* owner;', '    ' + ctype + ' owner;').replace('owner = ((void*)fn_80201B54(object));', 'owner = fn_80201B54(object);').replace('config, owner)', 'config, (void*)owner)')
variants['owner-typed-pointer'] = BEST.replace('    void* owner;', '    struct Owner* owner;').replace('owner = ((void*)fn_80201B54(object));', 'owner = (struct Owner*)fn_80201B54(object);')

def run(name, source):
    SOURCE.write_text(source)
    cmd = ['.tools/bin/ninja', '-j2', 'build/GEDE01/src/game/game_fn_8008A96C.o']
    result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    (REPORT / (name + '.log')).write_text(result.stdout)
    record = {'name': name, 'source_sha256': hashlib.sha256(source.encode()).hexdigest(), 'build_command': cmd, 'build_exit': result.returncode}
    if result.returncode == 0:
        cmd = ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/game/game_fn_8008A96C', 'fn_8008A96C', '-c', 'function_reloc_diffs=all', '-o', str(REPORT / (name + '.json')), '--format', 'json']
        subprocess.run(cmd, check=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        data = json.loads((REPORT / (name + '.json')).read_text())
        a, b = [next(s for s in data[side]['symbols'] if s['name'] == 'fn_8008A96C') for side in ['left', 'right']]
        record.update(score=a['match_percent'], target_size=a['size'], generated_size=b['size'], diff_command=cmd)
    print(record, flush=True)
    return record

if __name__ == '__main__':
    original_source = SOURCE.read_text()
    results = json.loads((REPORT / 'experiments.json').read_text()) if (REPORT / 'experiments.json').exists() else []
    try:
        for name, source in variants.items():
            if (REPORT / (name + '.log')).exists():
                continue
            results.append(run(name, source))
            (REPORT / 'experiments.json').write_text(json.dumps(results, indent=2) + '\n')
    finally:
        SOURCE.write_text(original_source)
