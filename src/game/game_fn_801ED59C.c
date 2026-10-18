extern int lbl_8064D62C;
extern void GXSetZCompLoc(unsigned char);

int fn_801ED59C(int value, int force)
{
    int old = lbl_8064D62C;
    if (old != value || force != 0) {
        GXSetZCompLoc((unsigned char)value);
        lbl_8064D62C = value;
    }
    return old;
}
