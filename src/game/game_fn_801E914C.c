typedef unsigned int u32;

extern u32 lbl_8064C360;

u32 fn_801E914C(u32 value)
{
    u32 previous = lbl_8064C360;
    lbl_8064C360 = value;
    return previous;
}
