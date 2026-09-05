typedef unsigned long u32;

extern const char lbl_80251640[];
extern void* fn_801FEA8C(u32, u32, const char*, u32);

#pragma peephole off
#pragma scheduling off
void fn_801A9488(u32 size)
{
    fn_801FEA8C(size, 1, lbl_80251640, 77);
}
#pragma peephole reset
#pragma scheduling reset
