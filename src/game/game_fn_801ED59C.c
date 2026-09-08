extern int lbl_8064D62C;
extern void fn_8022A7D4(unsigned char);

int fn_801ED59C(int value, int force)
{
    int old = lbl_8064D62C;
    if (old != value || force != 0) {
        fn_8022A7D4((unsigned char)value);
        lbl_8064D62C = value;
    }
    return old;
}
