extern int lbl_8064D74C;
extern int lbl_8064CE38;
extern int lbl_8064CE30;
extern int lbl_8064CD80;
extern int lbl_8064CBA4;
extern int lbl_8064D5A8;
extern int lbl_8064CE34;
extern int lbl_8064CE10;
extern float lbl_8065002C;
extern unsigned char lbl_806391F0[];

extern void fn_800243E8(void);
extern void fn_801EF530(void);
extern void fn_801EF580(int);
extern void fn_80024434(void);
extern void fn_801EC9E4(void);
extern void fn_801ED3F4(int);
extern void fn_801A8D38(int);
extern void fn_801A9250(short, int, int);
extern void fn_801A91D4(short, int, int);
extern void *fn_80201B9C();
extern int fn_80204844(int, int);
extern void fn_801EFE84(int);
extern void fn_800073DC(int);
extern void fn_801EB194(int);
extern void fn_801187F4(void);
extern int fn_80201B54();
extern void fn_8020104C(int, void*, void*, int, float);
#define fn_8020104C(a,b,c,d,e) fn_8020104C((int)(a),(void*)(b),(void*)(c),(int)(d),(float)(e))
extern void fn_801AD404(int, int, int);
extern void fn_801AD490(void);
extern void fn_801AD528(int, int);
extern void fn_80156B1C(int);
extern void fn_801571C4(void);
extern void fn_80024468(void);
extern void fn_8014426C(void);
extern void fn_801A99B4(void);
extern void fn_80155D9C(int);
extern void fn_8017AF44(void);
extern void fn_800BC000(void);
extern void OSCheckStopwatch(void *);
extern void OSStopStopwatch(void *);
extern void OSResetStopwatch(void *);

void fn_8011B86C(void)
{
    int changed = 0;
    int handle;

    fn_800243E8();
    fn_801EF530();
    fn_801EF580(lbl_8064D74C);
    fn_80024434();
    lbl_8064CE30 = lbl_8064CE38;
    fn_801EC9E4();
    fn_801ED3F4(lbl_8064CD80);
    fn_801A8D38(5);
    if (lbl_8064CBA4 == 1) {
        fn_801A9250((short)lbl_8064CE30, 255, 0);
    } else {
        fn_801A91D4((short)lbl_8064CE30, 255, 0);
    }
    if (lbl_8064D5A8 == lbl_8064CE34) {
        handle = fn_80204844((int)fn_80201B9C(), 32);
        fn_801EFE84(1);
        fn_800073DC(2);
        changed = 1;
        fn_801EB194(1);
        fn_801EF530();
        fn_801EF580(lbl_8064D74C);
        fn_801187F4();
        fn_8020104C(233, 0, fn_80201B54(handle), 0, lbl_8065002C);
        if (lbl_8064CE10 != 0) {
            fn_801AD404(0, 0, 16);
            fn_801AD490();
            fn_801AD528(1, 32);
            lbl_8064CE10 = 0;
        }
    }
    fn_80156B1C(0);
    fn_801571C4();
    fn_80024468();
    fn_801EB194(1);
    fn_8014426C();
    fn_801A99B4();
    if (changed == 0) {
        fn_80155D9C(0);
    }
    fn_8017AF44();
    fn_800BC000();
    if (changed == 0) {
        fn_80155D9C(1);
        fn_801EFE84(0);
    }
    OSCheckStopwatch(lbl_806391F0);
    OSStopStopwatch(lbl_806391F0);
    OSResetStopwatch(lbl_806391F0);
}
