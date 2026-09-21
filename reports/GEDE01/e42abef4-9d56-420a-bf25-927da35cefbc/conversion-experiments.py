from experiment import *
import itertools
# Recover the best experiment by applying its exact recorded patch to base in memory.
text=base.replace('extern void fn_8015DAB0(char*, int, u32);','extern void fn_8015DAB0(void*);').replace('fn_8015DAB0(label, mode, initialValue);','fn_8015DAB0(label);').replace('void fn_801EFA68(DisplayConfig* config, int mode)','void fn_801EFA68(DisplayConfig* config)')
text=text.replace('    u16 height;\n    u16 width;', '    u16 height;\n    u16 width;\n    u32 framebufferSize;').replace('    state->field_0 = lbl_802662C0;', '    framebufferSize = ((u16)((width + 15) & ~15) * height) << 1;\n    state->field_0 = lbl_802662C0;').replace('((((width + 15) & ~15) * height) << 1)','framebufferSize')
start=text.index('    widthValue.words.high = ')
end=text.index('    fn_8022B94C',start)
lines=text[start:end].splitlines(True)
# Assignment order is meaningful to MWCC's scheduling; test all orders without changing arithmetic.
for order in itertools.permutations(range(4)):
 if order==(0,1,2,3): continue
 run('conversion-order-'+''.join(map(str,order)),text[:start]+''.join(lines[i] for i in order)+text[end:])
