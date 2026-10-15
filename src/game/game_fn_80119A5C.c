extern int lbl_8064CE00;
extern int lbl_8064CE08;
extern int lbl_8064CDFC;
extern int lbl_8064CE04;
extern void fn_80144C40(void);

void fn_80119A5C(int unused, int event)
{
    if (event == 1) {
        if (lbl_8064CE00 < lbl_8064CE08) {
            lbl_8064CE08 -= 5;
            lbl_8064CE08 = lbl_8064CE08 > lbl_8064CE00 ? lbl_8064CE08 : lbl_8064CE00;
            fn_80144C40();
        } else if (lbl_8064CE00 > lbl_8064CE08) {
            lbl_8064CE08 += 5;
            lbl_8064CE08 = lbl_8064CE08 < lbl_8064CE00 ? lbl_8064CE08 : lbl_8064CE00;
            fn_80144C40();
        }

        if (lbl_8064CDFC < lbl_8064CE04) {
            lbl_8064CE04 -= 5;
            lbl_8064CE04 = lbl_8064CE04 > lbl_8064CDFC ? lbl_8064CE04 : lbl_8064CDFC;
            fn_80144C40();
        } else if (lbl_8064CDFC > lbl_8064CE04) {
            lbl_8064CE04 += 5;
            lbl_8064CE04 = lbl_8064CE04 < lbl_8064CDFC ? lbl_8064CE04 : lbl_8064CDFC;
            fn_80144C40();
        }
    }
}
