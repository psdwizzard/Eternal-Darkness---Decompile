typedef unsigned short u16;
typedef unsigned int u32;

extern u16 lbl_8064D494;
extern u32 lbl_8064D498;
extern u32 lbl_8064D518;

extern u32 fn_801CE204(void);
extern void fn_801C4B5C(void*, u32);
extern void fn_80209AD4(void);
extern void fn_8021B8CC(u32);
extern u32 fn_8021B894(void);

void fn_801CE190(void* argument)
{
    u32 saved;

    fn_801C4B5C(argument, fn_801CE204());
    lbl_8064D518 = 0;
    saved = lbl_8064D498;
    fn_80209AD4();
    fn_8021B8CC((u32)lbl_8064D494 | 0xBABE0000);
    while (fn_8021B894() != 0) {
    }
    fn_8021B8CC(saved);
    while (fn_8021B894() != 0) {
    }
}
