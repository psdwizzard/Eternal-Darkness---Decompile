typedef unsigned char u8;

extern u8 lbl_8064D694;
extern u8 lbl_8064D695;
extern int lbl_8064D698;
extern void fn_8022A75C(u8 first, int second, u8 third);

void fn_801ECEC8(u8 first, int second, u8 third)
{
    if (lbl_8064D698 != second || lbl_8064D695 != first ||
        lbl_8064D694 != third) {
        fn_8022A75C(first, second, third);
        lbl_8064D698 = second;
        lbl_8064D695 = first;
        lbl_8064D694 = third;
    }
}
