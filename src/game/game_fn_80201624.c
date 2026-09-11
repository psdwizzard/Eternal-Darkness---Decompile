extern int lbl_8064D89C;
extern int lbl_8064D8A0;

extern void *fn_80201814(int);

int fn_80201624(void)
{
    int result;

    if (lbl_8064D8A0 + 1 >= 0xFFFFFF) {
        lbl_8064D89C = 1;
        lbl_8064D8A0 = 2;
    }

    if (lbl_8064D89C != 0) {
        int found = 0;

        while (found == 0) {
            lbl_8064D8A0++;
            if (fn_80201814(lbl_8064D8A0) == 0) {
                found = 1;
                result = lbl_8064D8A0;
            }
        }
    } else {
        result = ++lbl_8064D8A0;
    }

    return result;
}
