typedef signed short s16;

extern int lbl_8064D590;
extern void fn_80144C40(void);

void fn_801E70FC(s16 amount)
{
    lbl_8064D590 += amount;
    if (lbl_8064D590 < 0) {
        lbl_8064D590 = 3;
    } else if (lbl_8064D590 > 3) {
        lbl_8064D590 = 0;
    }
    fn_80144C40();
}
