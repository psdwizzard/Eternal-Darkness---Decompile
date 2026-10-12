typedef unsigned int u32;

extern u32 lbl_80331748[];
extern u32 *lbl_8064C4E0;
extern int lbl_8064CD44;
extern u32 lbl_8064CD68;
extern int lbl_8064CD6C;
extern int lbl_8064CDC8;

extern int fn_801E79FC(u32 *set, u32 index);
extern void fn_80144C40(void);
extern u32 fn_80144710(u32, int, int);
extern void fn_801139D4(void);
extern int fn_801A98F4(int, void *);
extern void fn_80119568(void);
extern void fn_8010F418(void);

void fn_801155B4(void)
{
    switch (lbl_8064CD44) {
    case 16:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 25:
    case 26:
    case 27:
    case 28:
        break;
    case 17:
        if (lbl_8064CD68 <= ((lbl_80331748[lbl_8064CD6C + 26] & 15) * 2 + 3) ||
            !fn_801E79FC(lbl_8064C4E0, 0x3B)) {
            break;
        }
        lbl_80331748[lbl_8064CD6C + 2] &= ~0x02000000U;
        /* Fall through to the menu transition. */
    case 24:
    default:
        fn_80144C40();
        if (fn_80144710(0x1000, 0, 0) != 0) {
            lbl_8064CDC8 = 2;
        } else if (fn_80144710(0x1000000, 0, 0) != 0) {
            fn_801139D4();
            fn_801A98F4(0x1EF, (void *)0x32);
            fn_80119568();
        } else {
            fn_801139D4();
            fn_801A98F4(0x1EF, (void *)0x32);
            fn_8010F418();
        }
        break;
    }
}
