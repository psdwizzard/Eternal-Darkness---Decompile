typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef struct Color { u8 r, g, b, a; } Color;

typedef struct Point {
    s16 x;
    s16 y;
} Point;

/* Per-layout slot positions at 0x8023A3C0 (0x1C bytes each). */
typedef struct SlotLayout {
    Point slot[7];
} SlotLayout;

typedef struct NamePair {
    char *top;
    char *bottom;
} NamePair;

/* Menu data block at 0x8024CE40. */
typedef struct MenuData {
    u8 textures[0x310];        /* 0x000 */
    u8 textureList[0xC78];     /* 0x310 */
    NamePair slotNames[16];    /* 0xF88 */
} MenuData;

extern SlotLayout lbl_8023A3C0[];
extern MenuData lbl_8024CE40;
extern Color lbl_8064B8D8;
extern char lbl_8064B95C[4];
extern char lbl_8064B960[4];
extern Color lbl_8064C2B0;
extern unsigned int lbl_8064CD4C;
extern void *lbl_8064CD80;
extern const float lbl_8064FF78;
extern const float lbl_8064FF7C;
extern Color lbl_8064FF80;

extern void fn_801A852C(Color, int, int, u32);
extern void fn_801A9118(u16, u16, int);
extern void fn_801A90BC(void *, void *);
extern void fn_801E3AA4(int);
extern void fn_801E3A34(Color);
extern void fn_801E5AD0(int);
extern void fn_801E5430(s16, s16);
extern void fn_801E56AC(float, const char *, ...);
extern void fn_801ED3F4(void *);
extern void fn_801ED5F4(int, int, int, int, int, float);

void fn_80115D8C(u32 flags, s32 count, u8 alpha)
{
    s32 i;
    u32 layout;
    u32 slots;
    s32 idx;
    s16 x;
    s16 y;
    MenuData *menu = &lbl_8024CE40;
    s32 mode;
    NamePair *names;
    Color frameColor;
    Color slotColor;

    layout = flags & 0xF;
    slots = layout * 2 + 3;
    mode = 0x40;
    frameColor = lbl_8064FF80;
    switch ((flags >> 4) & 0xF) {
    case 0:
        mode = 0x20;
        break;
    case 1:
        mode = 8;
        break;
    case 2:
        mode = 0x10;
        break;
    }
    if (count == 0) {
        frameColor.a = alpha;
    }

    switch (layout) {
    case 0:
        fn_801A852C(frameColor, 5, 8, 0x80000000);
        fn_801A9118(0, 0x14, 5);
        fn_801A9118(0, 0x18, 5);
        fn_801A9118(0, 0x1C, 5);
        fn_801A852C(frameColor, 5, 9, 0x80000000);
        fn_801A9118(0, 0x20, 5);
        fn_801A9118(0, 0x24, 5);
        fn_801A9118(0, 0x28, 5);
        break;
    case 1:
        fn_801A852C(frameColor, 5, 8, 0x80000000);
        fn_801A9118(0, 0x140, 5);
        fn_801A9118(0, 0x144, 5);
        fn_801A9118(0, 0x148, 5);
        fn_801A9118(0, 0x14C, 5);
        fn_801A9118(0, 0x150, 5);
        fn_801A852C(frameColor, 5, 9, 0x80000000);
        fn_801A9118(0, 0x154, 5);
        fn_801A9118(0, 0x158, 5);
        fn_801A9118(0, 0x15C, 5);
        fn_801A9118(0, 0x160, 5);
        fn_801A9118(0, 0x164, 5);
        break;
    case 2:
        fn_801A852C(frameColor, 5, 8, 0x80000000);
        fn_801A9118(0, 0x168, 5);
        fn_801A9118(0, 0x16C, 5);
        fn_801A9118(0, 0x170, 5);
        fn_801A9118(0, 0x174, 5);
        fn_801A9118(0, 0x178, 5);
        fn_801A9118(0, 0x17C, 5);
        fn_801A9118(0, 0x180, 5);
        fn_801A852C(frameColor, 5, 9, 0x80000000);
        fn_801A9118(0, 0x184, 5);
        fn_801A9118(0, 0x188, 5);
        fn_801A9118(0, 0x18C, 5);
        fn_801A9118(0, 0x190, 5);
        fn_801A9118(0, 0x194, 5);
        fn_801A9118(0, 0x198, 5);
        fn_801A9118(0, 0x19C, 5);
        break;
    }

    flags >>= 4;
    for (i = 0; i < ((count < slots) ? count : slots); i++) {
        idx = flags & 0xF;
        x = lbl_8023A3C0[layout].slot[i].x;
        y = lbl_8023A3C0[layout].slot[i].y;
        slotColor = lbl_8064B8D8;
        if (i + 1 == count) {
            slotColor.a = alpha;
            frameColor.a = alpha;
        } else if (i + 2 == count && alpha <= 75) {
            slotColor.a = alpha + 180;
            frameColor.a = alpha + 180;
        }

        switch (layout) {
        case 0:
            fn_801A852C(slotColor, 5, 0xE, 0x80000000);
            fn_801A9118((idx + 1) * 4, (i + 11) * 4, 5);
            if (i + 1 != count || alpha == 0xFF) {
                fn_801ED5F4(1, mode | 0x8400, 1, 0, 0, lbl_8064FF7C);
            }
            fn_801A852C(frameColor, 0, 0xF, 0x80000000);
            fn_801A9118((idx + 1) * 4, (i + 11) * 4, 5);
            fn_801ED5F4(0, mode | 0x8400, 1, 0, 0, lbl_8064FF7C);
            break;
        case 1:
            fn_801A852C(slotColor, 5, 0xE, 0x80000000);
            fn_801A9118((idx + 1) * 4, (i + 14) * 4, 5);
            if (i + 1 != count || alpha == 0xFF) {
                fn_801ED5F4(1, mode | 0x8400, 1, 0, 0, lbl_8064FF7C);
            }
            fn_801A852C(frameColor, 0, 0xF, 0x80000000);
            fn_801A9118((idx + 1) * 4, (i + 14) * 4, 5);
            fn_801ED5F4(0, mode | 0x8400, 1, 0, 0, lbl_8064FF7C);
            break;
        case 2:
            fn_801A852C(slotColor, 5, 0xE, 0x80000000);
            fn_801A9118((idx + 1) * 4, (i + 19) * 4, 5);
            if (i + 1 != count || alpha == 0xFF) {
                fn_801ED5F4(1, mode | 0x8400, 1, 0, 0, lbl_8064FF7C);
            }
            fn_801A852C(frameColor, 0, 0xF, 0x80000000);
            fn_801A9118((idx + 1) * 4, (i + 19) * 4, 5);
            fn_801ED5F4(0, mode | 0x8400, 1, 0, 0, lbl_8064FF7C);
            break;
        }

        fn_801E3AA4(0);
        fn_801E3A34(lbl_8064C2B0);
        fn_801E5AD0(99);
        fn_801E5430(x, y);
        if (lbl_8064CD4C & (0x10000 << idx)) {
            names = &menu->slotNames[idx];
            fn_801E56AC(lbl_8064FF78, names->top);
            fn_801E5430(x, y + 20);
            fn_801E56AC(lbl_8064FF78, names->bottom);
        } else {
            fn_801E56AC(lbl_8064FF78, lbl_8064B960);
            if (idx >= 4) {
                fn_801E5430(x, y + 20);
                fn_801E56AC(lbl_8064FF78, lbl_8064B95C);
            }
        }
        fn_801ED3F4(lbl_8064CD80);
        fn_801A90BC(menu->textures, menu->textureList);
        flags >>= 4;
    }
}
