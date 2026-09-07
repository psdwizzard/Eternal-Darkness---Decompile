typedef signed char s8;

extern s8 lbl_8064C31A;

s8 fn_801E5AD0(s8 value)
{
    s8 previous = lbl_8064C31A;
    lbl_8064C31A = value;
    return previous;
}
