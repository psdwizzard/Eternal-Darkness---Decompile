typedef unsigned long u32;

extern char lbl_80265DA0[], lbl_80265EBC[], lbl_80265FD8[], lbl_802660F4[];
extern char lbl_8063B374[], lbl_8063B38C[], lbl_8063B35C[], lbl_8063B3A4[];
extern u32 lbl_802FC5BC[];
extern long lbl_8064B810;
extern u32 lbl_8064D724, lbl_8064D728;

extern void fn_8015AB00(int);
extern void fn_801EC67C(void);
extern void fn_801EC7F4(void*, void*);
extern void fn_801FE56C(void);
extern void fn_801ECD74(void*);
extern void fn_801ECF50(int);
extern void fn_801F2DB0(int);

void fn_801F3D20(void)
{
    u32 value;

    fn_8015AB00(2);
    fn_801EC67C();
    fn_801EC7F4(lbl_80265DA0, lbl_8063B374);
    fn_801EC7F4(lbl_80265EBC, lbl_8063B38C);
    fn_801EC7F4(lbl_80265FD8, lbl_8063B35C);
    fn_801EC7F4(lbl_802660F4, lbl_8063B3A4);
    fn_801FE56C();
    value = lbl_802FC5BC[3];
    fn_801ECD74(&value);
    if (lbl_8064B810 != 0) {
        fn_801ECF50(2);
        lbl_8064D724 = 0;
        lbl_8064D728 = 0;
        fn_801F2DB0(3);
        fn_801F2DB0(2);
    }
}
