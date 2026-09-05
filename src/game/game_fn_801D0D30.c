extern int fn_80201AE4(void);
extern int fn_801D10B8(void);
extern int lbl_8064D550;

void fn_801D0D30(int value)
{
    if (value == fn_80201AE4() && fn_801D10B8() != 0) {
        lbl_8064D550 = 1;
    }
}
