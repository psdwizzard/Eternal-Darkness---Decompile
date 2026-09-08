typedef signed long s32;

extern s32 lbl_8064D6F4;
extern void fn_801F10BC(s32, s32, s32);
extern void fn_8022806C(s32, s32, s32, s32, s32, s32, s32);
extern void fn_801ED434(s32);

void fn_801F1034(void)
{
    if (lbl_8064D6F4 != 1) {
        fn_801F10BC(0, 0, 0);
        lbl_8064D6F4 = 1;
        fn_8022806C(4, 1, 1, 1, 0, 0, 2);
        fn_8022806C(5, 0, 1, 1, 0, 0, 2);
        fn_801ED434(1);
    }
}
