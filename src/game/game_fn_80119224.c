typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Color { u8 r, g, b, a; } Color;

extern char lbl_8024E388[];
extern int lbl_8064B994;
extern Color lbl_8064C2A8;
extern int lbl_8064CBA4;
extern int lbl_8064CD7C;
extern int lbl_8064CD80;
extern s8 lbl_8064CD95;
extern u32 lbl_8064CDB0;
extern const Color lbl_8064FFA4;
extern const Color lbl_8064FFA8;
extern const Color lbl_8064FFAC;

extern unsigned int fn_800FBFB0(void);
extern void fn_801A852C(Color, int, int, u32);
extern void fn_801A90BC(void *image, void *mask);
extern void fn_801A9118(int, u16, int);
extern void fn_801ED3F4(int);

static inline Color WithAlpha(Color color, u8 alpha)
{
    color.a = alpha;
    return color;
}

void fn_80119224(int mode, u8 alpha)
{
    char *data;
    short labelIcon;
    short textIcon;
    short headerIcon;
    int base;
    u16 index;

    base = 0;
    data = lbl_8024E388;
    lbl_8064B994 = mode;
    if (mode == 2 || mode == 0) {
        base = 7;
    }

    if (lbl_8064CD95 == -30 && (int)fn_800FBFB0() % 100 > 97) {
        lbl_8064CD95 = 5;
    }

    fn_801ED3F4(lbl_8064CD7C);
    if (lbl_8064CBA4 == 1) {
        fn_801A90BC(data +0x42C, data +0x234);
    } else {
        fn_801A90BC(data +0x42C, data +0x3C);
    }

    fn_801A852C(lbl_8064C2A8, 0, 2, 0x80000000);
    fn_801A9118(0x14, (base + 5) * 4, 5);
    fn_801A852C(lbl_8064C2A8, 0, 1, 0x80000000);
    fn_801A9118(0x14, (base + 6) * 4, 5);

    switch (mode) {
    case 0:
        labelIcon = 0x20;
        textIcon = 0x32;
        headerIcon = 0x1B;
        fn_801ED3F4(lbl_8064CD80);
        break;
    case 1:
        labelIcon = 0xD;
        textIcon = 0x13;
        headerIcon = 0xC;
        break;
    case 2:
        labelIcon = 1;
        textIcon = 0x33;
        headerIcon = 0;
        fn_801ED3F4(lbl_8064CD80);
        break;
    case 3:
        labelIcon = 7;
        textIcon = 0x34;
        headerIcon = 4;
        fn_801ED3F4(lbl_8064CD80);
        break;
    case 4:
        labelIcon = 0x2E;
        textIcon = 0x35;
        headerIcon = 0x2C;
        fn_801ED3F4(lbl_8064CD80);
        break;
    }

    if (mode != 2) {
        fn_801A852C(lbl_8064C2A8, 0, headerIcon, 0x80000000);
        fn_801A9118(0x14, 0x1C, 5);
    }

    fn_801A852C(WithAlpha(lbl_8064FFA4, alpha), 0, labelIcon, 0x80000000);
    fn_801A9118(0x14, (base + 9) * 4, 5);

    if (lbl_8064CDB0 == 0) {
        fn_801A852C(WithAlpha(lbl_8064FFA8, alpha), 0, textIcon, 0x80000000);
        fn_801A9118(0x14, (base + 11) * 4, 5);
    }

    fn_801ED3F4(lbl_8064CD7C);
    fn_801A852C(lbl_8064FFAC, 5, 0, 0x80000000);
    fn_801A9118(0x14, (base + 8) * 4, 5);
    fn_801A852C(lbl_8064C2A8, 0, 3, 0x80000000);
    fn_801A9118(0x14, (base + 10) * 4, 5);

    if (lbl_8064CD95 <= 0) {
        fn_801A852C(lbl_8064C2A8, 0, 4, 0x80000000);
        index = mode * 4;
        fn_801A9118(index, index, 5);
    }

    if (lbl_8064CD95 > -30) {
        lbl_8064CD95--;
    }
}
