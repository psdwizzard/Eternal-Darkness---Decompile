typedef struct Object Object;
typedef struct DisplaySize DisplaySize;

extern void fn_800073DC(int);
extern void fn_800243E8(void);
extern void fn_80024434(void);
extern void fn_80024468(void);
extern void *fn_8006D444(void *object);
extern void fn_8006E20C(void *);
extern void fn_800BC000(void);
extern void fn_801187F4(void);
extern void fn_8014426C(void);
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
extern void fn_801E81C0(int);
extern void fn_801EB194(int);
extern void fn_801EC9E4(void);
extern unsigned int fn_801ED3F4(unsigned int);
extern void fn_801EF530(void);
extern void fn_801EF580(DisplaySize *);
extern void *fn_801EFE84(void *);
extern unsigned long long fn_8020123C(int, int, int, int);
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
extern unsigned char lbl_8064CE1C;
extern int lbl_8064CE20;
extern int lbl_8064CE24;
extern int lbl_8064CE28;
extern int lbl_8064CE30;
extern int lbl_8064D5A8;
extern DisplaySize *lbl_8064D74C;

void fn_8011B218(void)
{
    int transitioned = 0;
    Object *handle;
    void *object;

    fn_800243E8();
    fn_801EF530();
    fn_801EF580(lbl_8064D74C);
    fn_80024434();

    switch (lbl_8064CE24) {
    case 0:
        lbl_8064CE30 = 7;
        lbl_8064CE24 = 1;
        break;
    case 1:
        if (lbl_8064D5A8 >= 200) {
            lbl_8064CE24 = 2;
            lbl_8064CE1C = 0;
            fn_801E81C0(0);
            lbl_8064CE20 = 8;
            lbl_8064CE28 = 0;
        } else {
            lbl_8064CE1C = 150;
        }
        break;
    }

    fn_801EC9E4();
    fn_801ED3F4(lbl_8064CD80);
    fn_801A8D38(5);
    if (lbl_8064CBA4 == 1) {
        fn_801A9250((short)lbl_8064CE30, 255, 0);
    } else {
        fn_801A91D4((short)lbl_8064CE30, 255, 0);
    }
    if (lbl_8064CE28 < 255) {
        if (lbl_8064CBA4 == 1) {
            fn_801A9250((short)lbl_8064CE20, lbl_8064CE28, 0);
        } else {
            fn_801A91D4((short)lbl_8064CE20, lbl_8064CE28, 0);
        }
        lbl_8064CE28 += 4;
        lbl_8064CE28 = lbl_8064CE28 < 255 ? lbl_8064CE28 : 255;
        if (lbl_8064CE28 == 255) {
            lbl_8064CE30 = lbl_8064CE20;
        }
    }

    if (lbl_8064CE24 == 2) {
        if (lbl_8064D5A8 >= 200) {
            handle = fn_80204844(fn_80201B9C(), 32);
            object = fn_8006D444(handle);
            fn_801EFE84((void *)1);
            fn_800073DC(2);
            transitioned = 1;
            fn_801EB194(1);
            fn_801EF530();
            fn_801EF580(lbl_8064D74C);
            fn_801187F4();
            if (object != 0) {
                int object_id = fn_80201B54((int *)handle);
                fn_8020123C(0x51, 0, object_id, 0);
                fn_8006E20C(object);
            }
            if (lbl_8064CE10 != 0) {
                fn_801AD404(0, 0, 16);
                fn_801AD490();
                fn_801AD528(1, 32);
                lbl_8064CE10 = 0;
            }
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
        fn_801EFE84(0);
    }
    fn_8017AF44();
    fn_800BC000();
    if (transitioned == 0) {
        fn_80155D9C(1);
    }
    fn_8020F088(lbl_806391F0);
    fn_8020EFBC(lbl_806391F0);
    fn_8020F0F8(lbl_806391F0);
}
