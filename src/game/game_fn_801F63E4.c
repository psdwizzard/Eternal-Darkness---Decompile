typedef unsigned short u16;
typedef unsigned int u32;

extern u16 lbl_8064D788;
extern void* lbl_8064D790;
extern void fn_801F62D0(u32, u16, void*, u16);

void fn_801F63E4(u32 key, u16 value)
{
    fn_801F62D0(key, value, lbl_8064D790, lbl_8064D788);
}
