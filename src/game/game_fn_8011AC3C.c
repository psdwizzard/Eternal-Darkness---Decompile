typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed long s32;
typedef unsigned long long u64;
typedef long long s64;

typedef struct Object Object;
typedef struct Owner Owner;
typedef struct DisplaySize DisplaySize;
typedef union Color {
    u32 value;
    struct { u8 r, g, b, a; } channel;
} Color;
typedef struct OSStopwatch {
    char *name;
    s64 total;
    unsigned long hits;
    s64 min, max, last;
    int running;
} OSStopwatch;

extern void fn_800243E8(void);
extern void fn_80024434(void);
extern void fn_80024468(void);
extern void *fn_8006D444(void *object);
extern int fn_8006E20C(Owner *owner);
extern void fn_800BC000(void);
extern void fn_801187F4(void);
extern void fn_8014426C(void);
extern int fn_80155D9C(int);
extern void fn_80156B1C(void (*removed)(Object *));
extern void fn_801571C4(void);
extern void fn_8017AF44(void);
extern void fn_801A8660(s32, s32, s32, s32, s32, const u32 *);
extern void fn_801A8D38(s32);
extern void fn_801A977C(void *, int);
extern int fn_801A98F4(int index, void *object);
extern void fn_801A99B4(void);
extern void *fn_801A9F44(int count, void **values);
extern void fn_801AD404(u8, u8, int);
extern void fn_801AD490(void);
extern void fn_801AD528(int, int);
extern int fn_801AD5FC(int, int);
extern u32 fn_801E3A34(Color *);
extern void fn_801E3AA4(int);
extern void fn_801E5430(short, short);
extern void fn_801E56AC(float scale, const char *format, ...);
extern void fn_801EB194(int);
extern void fn_801EC9E4(void);
extern void fn_801EF530(void);
extern void fn_801EF580(DisplaySize *);
extern void *fn_801EFE84(void *);
extern u64 fn_8020123C(int, int, int, int);
extern int fn_80201B54(int *object);
extern void *fn_80201B9C(void);
extern Object *fn_80204844(Object *object, int type);
extern void fn_8020EFBC(OSStopwatch *);
extern s64 fn_8020F088(OSStopwatch *);
extern void fn_8020F0F8(OSStopwatch *);

extern const volatile u32 lbl_8023A650[4];
extern OSStopwatch lbl_806391F0;
extern char lbl_8064B9A8[6];
extern void *lbl_8064C4E4;
extern int lbl_8064CE10;
extern int lbl_8064D5A8;
extern DisplaySize *lbl_8064D74C;
extern const u32 lbl_80650020;
extern const Color lbl_80650024;
extern const float lbl_80650028;

void fn_8011AC3C(void)
{
    void *values[3];
    u32 background;
    Color color;
    int transitioned = 0;
    int frame;
    Object *handle;
    Owner *owner;

    fn_800243E8();
    fn_801EF530();
    fn_801EF580(lbl_8064D74C);
    fn_80024434();
    fn_801EC9E4();
    fn_801A8D38(5);
    background = lbl_80650020;
    fn_801A8660(-106, 0, 853, 480, -1, &background);
    fn_801E3AA4(0);
    fn_801E5430(455, 31);
    color = lbl_80650024;
    fn_801E3A34(&color);
    fn_801E56AC(lbl_80650028, lbl_8064B9A8);
    frame = lbl_8064D5A8;
    if (frame == 1) {
        lbl_8064CE10 = 0;
        if (fn_801AD5FC(1, 0) != 0) {
            lbl_8064CE10 = 1;
            fn_801AD404(0, 0, 32);
            fn_801AD490();
            fn_801AD404(100, 100, 1);
        }
    }
    if (frame >= 300) {
        handle = fn_80204844(fn_80201B9C(), 32);
        owner = fn_8006D444(handle);
        fn_801EB194(1);
        fn_801EF530();
        fn_801EF580(lbl_8064D74C);
        fn_801187F4();
        transitioned = 1;
        if (owner != 0) {
            int id = fn_80201B54((int *)handle);
            fn_8020123C(0x51, 0, id, 0);
            fn_8006E20C(owner);
        }
        if (lbl_8064CE10 != 0) {
            fn_801AD404(0, 0, 16);
            fn_801AD490();
            fn_801AD528(1, 32);
            lbl_8064CE10 = 0;
        }
    }
    switch (frame) {
    case 160:
    case 66:
        fn_801A977C(lbl_8064C4E4, 33);
        break;
    case 140:
    case 46:
        values[0] = (void *)lbl_8023A650[0];
        values[1] = (void *)lbl_8023A650[1];
        values[2] = (void *)lbl_8023A650[2];
        fn_801A98F4((u16)(u32)fn_801A9F44(3, values), (void *)0x55);
        break;
    }
    fn_80156B1C(0);
    fn_801571C4();
    fn_80024468();
    fn_801EB194(1);
    fn_801EFE84(0);
    fn_8014426C();
    fn_801A99B4();
    if (!transitioned) {
        fn_80155D9C(0);
    }
    fn_8017AF44();
    fn_800BC000();
    if (!transitioned) {
        fn_80155D9C(1);
    }
    fn_8020F088(&lbl_806391F0);
    fn_8020EFBC(&lbl_806391F0);
    fn_8020F0F8(&lbl_806391F0);
}
