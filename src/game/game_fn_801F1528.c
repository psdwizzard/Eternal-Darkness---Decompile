typedef signed long s32;

extern s32 lbl_8064D18C;
extern s32 lbl_8064D750;
extern s32 lbl_8064D638;
extern void fn_801ED434(s32);
extern void fn_8022806C(s32, s32, s32, s32, s32, s32, s32);

void fn_801F1528(s32 enabled)
{
    if (lbl_8064D18C != 0x32) {
        if (enabled != 0 && lbl_8064D750 != 0) {
            if (lbl_8064D638 != 2) {
                fn_801ED434(2);
                fn_8022806C(1, 1, 0, 0, lbl_8064D750, 0, 0);
            }
        } else if (lbl_8064D638 != 1) {
            fn_801ED434(1);
            fn_8022806C(1, 0, 0, 0, 0, 0, 2);
        }
    }
}
