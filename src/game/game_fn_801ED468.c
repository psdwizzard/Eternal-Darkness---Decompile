extern int lbl_8064D69C;
extern void GXSetCurrentMtx(int);

void fn_801ED468(int value)
{
    if (lbl_8064D69C != value) {
        GXSetCurrentMtx(value);
    }
}
