typedef struct Object Object;
typedef struct DisplaySize DisplaySize;

extern void fn_800073DC(int);
extern void fn_800243E8(void);
extern void fn_80024434(void);
extern void fn_80024468(void);
extern int fn_800AE380(unsigned short, unsigned int, void *, unsigned short,
                       unsigned short, unsigned short, unsigned char, unsigned short);
extern void fn_800AE3FC(unsigned short, unsigned int, void *, unsigned short,
                        unsigned short, unsigned short, unsigned char, unsigned short);
extern void fn_800AF2D4(void);
extern void fn_800BC000(void);
extern void fn_801187F4(void);
extern int fn_8011B864(void);
extern void fn_8014426C(void);
extern void fn_8014C23C(int, int, int);
extern int fn_80155D9C(int);
extern void fn_80156B1C(void (*removed)(Object *));
extern void fn_801571C4(void);
extern void fn_8017AF44(void);
extern void fn_801A8D38(signed long);
extern void fn_801A91D4(unsigned long, unsigned char, unsigned long);
extern void fn_801A9250(unsigned long, unsigned char, unsigned long);
extern void fn_801A99B4(void);
extern void fn_801AD404(unsigned char, unsigned char, int);
extern void fn_801AD490(void);
extern void fn_801AD528(int, int);
extern void fn_801EB194(int);
extern void fn_801EC9E4(void);
extern unsigned int fn_801ED3F4(unsigned int);
extern void fn_801EF530(void);
extern void fn_801EF580(DisplaySize *);
extern void *fn_801EFE84(void *);
extern void fn_8020104C(int, int, int, int, float);
extern int fn_80201B54(int *object);
extern void *fn_80201B9C(void);
extern Object *fn_80204844(Object *object, int type);
extern void fn_8020EFBC(void *);
extern void fn_8020F088(void *);
extern void fn_8020F0F8(void *);

extern char lbl_806391F0[];
extern signed long lbl_8064CBA4;
extern unsigned int lbl_8064CD80;
extern int lbl_8064CE10;
extern int lbl_8064CE24;
extern int lbl_8064CE28;
extern int lbl_8064CE30;
extern DisplaySize *lbl_8064D74C;
extern const float lbl_8065002C;

void fn_8011B4CC(void)
{
    int transitioned = 0;
    Object *handle;

    fn_800243E8();
    fn_801EF530();
    fn_801EF580(lbl_8064D74C);
    fn_80024434();

    switch (lbl_8064CE24) {
    case 0:
        lbl_8064CE30 = 9;
        lbl_8064CE24 = 1;
        lbl_8064CE28 = 0;
        break;
    }

    fn_801EC9E4();
    fn_801ED3F4(lbl_8064CD80);
    fn_801A8D38(5);
    if (lbl_8064CBA4 == 1) {
        fn_801A9250((short)lbl_8064CE30, lbl_8064CE28, 0);
    } else {
        fn_801A91D4((short)lbl_8064CE30, lbl_8064CE28, 0);
    }
    if (lbl_8064CE28 < 255) {
        lbl_8064CE28 += 4;
        lbl_8064CE28 = lbl_8064CE28 < 255 ? lbl_8064CE28 : 255;
    }

    if (fn_8011B864() == 0) {
        handle = fn_80204844(fn_80201B9C(), 32);
        fn_801EFE84((void *)1);
        fn_800073DC(2);
        transitioned = 1;
        fn_801EB194(1);
        fn_801EF530();
        fn_801EF580(lbl_8064D74C);
        fn_801187F4();
        fn_8020104C(0xE9, 0, fn_80201B54((int *)handle), 0, lbl_8065002C);
        fn_8014C23C(0, 0, 0);
        fn_800AF2D4();
        if (fn_800AE380(0xFFFF, 3, 0, 2, 360, 10, 0, 0) == 0) {
            fn_800AE3FC(0xFFFF, 3, 0, 2, 360, 10, 0, 0);
        }
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
    if (transitioned == 0) {
        fn_80155D9C(0);
    }
    fn_8017AF44();
    fn_800BC000();
    if (transitioned == 0) {
        fn_80155D9C(1);
        fn_801EFE84(0);
    }
    fn_8020F088(lbl_806391F0);
    fn_8020EFBC(lbl_806391F0);
    fn_8020F0F8(lbl_806391F0);
}
