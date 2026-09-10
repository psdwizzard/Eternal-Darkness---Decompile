extern int lbl_802FC8C0[];
extern volatile int lbl_8064D860;
extern volatile int lbl_8064D864;

void fn_8020034C(int value)
{
    int count;

    if ((count = value - 6) < 0) {
        count += 24;
    }

    lbl_8064D864 = 0;
    lbl_8064D860 = 0;
    while (count != 0) {
        int index = lbl_8064D864;
        int current = lbl_8064D860;
        int limit = lbl_802FC8C0[index];
        current += 18000;
        lbl_8064D860 = current;
        if (current >= limit) {
            lbl_8064D860 = 0;
            lbl_8064D864 = (index + 1) % 8;
        }
        count--;
    }
}
