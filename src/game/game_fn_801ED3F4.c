typedef unsigned int u32;

extern u32 lbl_8064D5FC;
extern void fn_801ED118(void);

u32 fn_801ED3F4(u32 value)
{
    u32 previous = lbl_8064D5FC;

    if (value != previous) {
        lbl_8064D5FC = value;
        fn_801ED118();
    }
    return previous;
}
