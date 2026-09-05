extern int lbl_8064D040;
extern void fn_801443F4(void);

void fn_80144430(int mask, int enabled)
{
    int flags;
    if (!enabled)
        flags = lbl_8064D040 & ~mask;
    else
        flags = lbl_8064D040 | mask;
    lbl_8064D040 = flags;
    if (flags != 0)
        fn_801443F4();
}
