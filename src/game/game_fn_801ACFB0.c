extern int lbl_8064D300;
extern int lbl_8064C2D0;
extern unsigned char lbl_8060B060[];
extern int DTKRemoveTrack(void*);

void fn_801ACFB0(void)
{
    lbl_8064D300 = 1;
    lbl_8064C2D0 = -1;
    DTKRemoveTrack(lbl_8060B060);
}
