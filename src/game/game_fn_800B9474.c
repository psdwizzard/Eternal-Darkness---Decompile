extern int lbl_8064CA04;
extern int lbl_8064CA00;
extern unsigned char lbl_803003AC[];
extern void fn_800B035C(void);
extern int fn_800B002C(void);
extern void fn_8015AC94(int, int);
extern void fn_801AD490(void);
extern void fn_80025A78(int);
extern void fn_800B936C(void);
extern void fn_800AFBA8(void *);
extern void fn_800B93F0(void);

void fn_800B9474(int mask)
{
    int action = lbl_8064CA04;
    if (action != 0 && (mask & action) != 0 && --lbl_8064CA00 <= 0) {
        switch (action) {
        case 1:
            fn_800B035C();
            break;
        case 0x40:
            fn_800B002C();
            break;
        case 0x10:
            fn_800B035C();
            fn_8015AC94(2, 0);
            break;
        case 0x20:
            fn_800B002C();
            fn_8015AC94(2, 0);
            break;
        case 2:
            fn_801AD490();
            fn_80025A78(2);
            break;
        case 4:
            fn_800B936C();
            break;
        case 8:
            fn_800AFBA8(lbl_803003AC);
            fn_800B93F0();
            break;
        }
        lbl_8064CA04 = 0;
        lbl_8064CA00 = 0;
    }
}
