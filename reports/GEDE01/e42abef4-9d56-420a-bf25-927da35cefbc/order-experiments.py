from experiment import *
one=base.replace('extern void fn_8015DAB0(char*, int, u32);','extern void fn_8015DAB0(void*);').replace('fn_8015DAB0(label, mode, initialValue);','fn_8015DAB0(label);').replace('void fn_801EFA68(DisplayConfig* config, int mode)','void fn_801EFA68(DisplayConfig* config)')
two=one.replace('(((width + 15) & ~15) * height)','((u16)((width + 15) & ~15) * height)')
run('width-first',two.replace('    height = lbl_8064C38C->height;\n    width = lbl_8064C38C->width;', '    width = lbl_8064C38C->width;\n    height = lbl_8064C38C->height;'))
run('width-aligned-local',two.replace('width = lbl_8064C38C->width;', 'width = (lbl_8064C38C->width + 15) & ~15;').replace('(u16)((width + 15) & ~15)', 'width'))
run('width-aligned-first',two.replace('    height = lbl_8064C38C->height;\n    width = lbl_8064C38C->width;', '    width = (lbl_8064C38C->width + 15) & ~15;\n    height = lbl_8064C38C->height;').replace('(u16)((width + 15) & ~15)', 'width'))
run('height-product',two.replace('    state->field_0 = lbl_802662C0;', '    width = (width + 15) & ~15;\n    state->field_0 = lbl_802662C0;').replace('(u16)((width + 15) & ~15)', 'width'))
run('low-word-first',two.replace('    widthValue.words.high = 0x43300000;\n    widthValue.words.low = lbl_8064C38C->width;\n    heightValue.words.high = 0x43300000;\n    heightValue.words.low = lbl_8064C38C->height;', '    widthValue.words.low = lbl_8064C38C->width;\n    widthValue.words.high = 0x43300000;\n    heightValue.words.low = lbl_8064C38C->height;\n    heightValue.words.high = 0x43300000;'))
