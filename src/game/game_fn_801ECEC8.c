typedef unsigned char u8;

extern u8 lbl_8064D694;
extern u8 lbl_8064D695;
extern int lbl_8064D698;
extern void GXSetZMode(u8 first, int second, u8 third);

void fn_801ECEC8(u8 first, int second, u8 third)
{
    if (lbl_8064D698 != second || lbl_8064D695 != first ||
        lbl_8064D694 != third) {
        GXSetZMode(first, second, third);
        lbl_8064D698 = second;
        lbl_8064D695 = first;
        lbl_8064D694 = third;
    }
}
