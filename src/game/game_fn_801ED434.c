extern int lbl_8064D638;
extern void GXSetNumChans(unsigned char);

void fn_801ED434(int value)
{
    if (value != lbl_8064D638) {
        lbl_8064D638 = value;
        GXSetNumChans(value);
    }
}
