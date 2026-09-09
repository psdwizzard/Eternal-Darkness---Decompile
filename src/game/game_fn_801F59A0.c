typedef unsigned short u16;

extern void* lbl_8064D790;
extern u16 lbl_8064D788;

extern void fn_801F65D0(void);
extern void fn_801F5D40(void*, u16);

void fn_801F59A0(void)
{
    fn_801F65D0();
    fn_801F5D40(lbl_8064D790, lbl_8064D788);
}
