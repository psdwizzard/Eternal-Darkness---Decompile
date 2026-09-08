extern int lbl_8064D638;
extern void fn_80228020(unsigned char);

void fn_801ED434(int value)
{
    if (value != lbl_8064D638) {
        lbl_8064D638 = value;
        fn_80228020(value);
    }
}
