from experiment import *
one=base.replace('extern void fn_8015DAB0(char*, int, u32);','extern void fn_8015DAB0(void*);').replace('fn_8015DAB0(label, mode, initialValue);','fn_8015DAB0(label);').replace('void fn_801EFA68(DisplayConfig* config, int mode)','void fn_801EFA68(DisplayConfig* config)')
two=one.replace('(((width + 15) & ~15) * height)','((u16)((width + 15) & ~15) * height)')
expr='(((u32)state->field_4 +\n        (((u16)((width + 15) & ~15) * height) << 1) + 31) & ~31)'
assert expr in two
for stage in ['before-stores','between-stores','after-stores']:
 for sizeexpr in ['(u16)((width + 15) & ~15) * height','height * (u16)((width + 15) & ~15)']:
  t=two.replace('    u16 height;\n    u16 width;','    u16 height;\n    u16 width;\n    u32 framebufferSize;').replace('(((u16)((width + 15) & ~15) * height) << 1)','framebufferSize')
  marker={'before-stores':'    state->field_0 = lbl_802662C0;', 'between-stores':'    state->field_4 = (void*)(((u32)arenaLo + 31) & ~31);', 'after-stores':'    OSSetArenaLo((void*)(((u32)state->field_4 +'}[stage]
  t=t.replace(marker, '    framebufferSize = ('+sizeexpr+') << 1;\n'+marker,1)
  run('layout-correct-size-'+stage+('-reversed' if sizeexpr.startswith('height') else ''),t)
# Separate pointer/size temporaries to express address arithmetic without nesting.
t=two.replace('    u16 height;\n    u16 width;', '    u16 height;\n    u16 width;\n    u32 framebufferSize;\n    void* framebuffer;')
t=t.replace('    state->field_0 = lbl_802662C0;', '    framebufferSize = ((u16)((width + 15) & ~15) * height) << 1;\n    framebuffer = (void*)(((u32)arenaLo + 31) & ~31);\n    state->field_0 = lbl_802662C0;').replace('state->field_4 = (void*)(((u32)arenaLo + 31) & ~31);','state->field_4 = framebuffer;').replace('(((u16)((width + 15) & ~15) * height) << 1)','framebufferSize')
run('layout-correct-size-pointer-locals',t)
