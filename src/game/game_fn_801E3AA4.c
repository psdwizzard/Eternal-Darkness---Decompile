typedef short s16;
typedef unsigned int u32;

extern u32 lbl_8064D584;
extern u32 lbl_8064C2A8;
extern u32 lbl_8064C31C;
extern u32 lbl_8064C320;

extern u32 fn_801E3A34(u32*);
extern void fn_801E5AD0(u32);
extern void fn_801E39A8(s16);

void fn_801E3AA4(int index)
{
    if ((u32)(s16)index < lbl_8064D584) {
        u32 color = lbl_8064C2A8;

        fn_801E3A34(&color);
        fn_801E5AD0(110);
        fn_801E39A8(index);
        lbl_8064C31C = -1;
        lbl_8064C320 = -1;
    }
}
