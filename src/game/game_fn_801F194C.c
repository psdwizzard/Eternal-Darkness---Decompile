typedef signed long s32;

extern s32 lbl_802FC658[4];
extern s32 lbl_802FC668[4];

void fn_801F194C(void)
{
    s32 i;
    for (i = 0; i < 4; i++) {
        s32 delta = lbl_802FC668[i];
        lbl_802FC658[i] += delta;
        if (delta > 0) {
            if (lbl_802FC658[i] >= 24000) {
                lbl_802FC658[i] = 24000;
                lbl_802FC668[i] = -delta;
            }
        } else if (lbl_802FC658[i] <= 4000) {
            lbl_802FC658[i] = 4000;
            lbl_802FC668[i] = -delta;
        }
    }
}
