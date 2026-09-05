extern int lbl_8064CCD4;
extern void* lbl_8064CCC8;
extern void* lbl_80331720[];
extern void fn_80144C40(void);
extern void fn_801E8B6C(void*, int);
extern void fn_801E5FB0(void*);

void fn_8010D2D4(int value)
{
    fn_80144C40();
    switch (lbl_8064CCD4) {
    case 2:
        fn_801E8B6C(lbl_80331720[3], value);
        fn_801E5FB0(lbl_8064CCC8);
        lbl_8064CCC8 = 0;
        break;
    case 3:
        break;
    case 0:
        fn_801E8B6C(lbl_80331720[0], value);
        fn_801E5FB0(lbl_8064CCC8);
        lbl_8064CCC8 = 0;
        break;
    }
}
