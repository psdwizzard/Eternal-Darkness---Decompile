typedef unsigned short u16;

extern int lbl_8064D6A4;
extern int lbl_8064D6A8;
extern u16* lbl_8064D610;

int fn_801EBC1C(void)
{
    int i;

    for (i = lbl_8064D6A8; i <= lbl_8064D6A4; i++) {
        if ((lbl_8064D610[i] & 0xFF) != 0x80) {
            return 0;
        }
    }
    return 1;
}
