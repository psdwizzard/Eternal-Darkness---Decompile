typedef unsigned long u32;

extern char lbl_8063C068[], lbl_8063BF28[];
extern const float lbl_80651348, lbl_8065134C, lbl_80651378, lbl_8065137C;
extern u32 lbl_802FC5BC[];
extern long lbl_8064B810;
extern u32 lbl_8064D724, lbl_8064D728;

extern void fn_8022B690(void*, int);
extern void fn_8022B6CC(void*, int);
extern void fn_8022B94C(float, float, float, float, float, float);
extern void fn_8022B970(int, int, int, int);
extern void fn_8022B4B8(void*, int);
extern void fn_801ED468(int);
extern void fn_801ECEC8(int, int, int);
extern void fn_801FE56C(void);
extern void fn_801ECD74(void*);
extern void fn_801ECF50(int);
extern void fn_8022A71C(int);
extern void fn_801F2BC8(int);

void fn_801F3DE4(void)
{
    u32 value;

    fn_8022B690(lbl_8063C068, 0x1B);
    fn_8022B6CC(lbl_8063C068, 0x1B);
    fn_8022B94C(lbl_80651348, lbl_80651348, lbl_80651378,
                lbl_8065137C, lbl_80651348, lbl_8065134C);
    fn_8022B970(0, 0, 0x280, 0x1E0);
    fn_8022B4B8(lbl_8063BF28, 0);
    fn_801ED468(0x1B);
    fn_801ECEC8(1, 3, 0);
    fn_801FE56C();
    value = lbl_802FC5BC[3];
    fn_801ECD74(&value);
    if (lbl_8064B810 != 0) {
        fn_801ECF50(2);
        lbl_8064D724 = 0;
        lbl_8064D728 = 0;
        fn_8022A71C(0);
        fn_801F2BC8(3);
        fn_801F2BC8(2);
        fn_801ECEC8(1, 3, 1);
    }
}
