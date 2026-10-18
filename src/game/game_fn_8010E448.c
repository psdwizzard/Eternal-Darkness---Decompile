typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Color { u8 r, g, b, a; } Color;
typedef struct Block52 { int data[13]; } Block52;

typedef struct Slot {
    int unk0;
    void *object;
    u8 pad8[0x1C];
    void *actor;
    u8 pad28[4];
} Slot;

typedef struct SlotTable {
    Slot pad0[6];
    Slot primary[6];
    Slot pad210[6];
    Slot secondary[6];
    Slot extra[32];
    int values[8];
} SlotTable;

typedef struct MenuText {
    u8 pad0[0xC8];
    s16 icons[0x134];
    char countFormat[0xC];
    char modeText[3][0xC];
    char footer[0xC];
} MenuText;

extern SlotTable lbl_80330D80;
extern MenuText lbl_8024B310;
extern u8 lbl_802515D0[];
extern char lbl_8064B880[3];
extern char lbl_8064B884[5];
extern char lbl_8064B88C[5];
extern char lbl_8064B894[5];
extern char lbl_8064B89C[4];
extern Color lbl_8064C2A8;
extern Color lbl_8064C2B0;
extern Color lbl_8064C2BC;
extern void *lbl_8064C4E0;
extern int lbl_8064CCC4;
extern void *lbl_8064CCC8;
extern u32 lbl_8064CCCC;
extern int lbl_8064CCD4;
extern u32 lbl_8064CCD8;
extern int lbl_8064CD7C;
extern int lbl_8064CDB0;
extern int lbl_8064CDB4;
extern int lbl_8064CDB8;
extern u32 lbl_8064CDBC;
extern const float lbl_8064FE70;
extern const float lbl_8064FE90;
extern const Color lbl_8064FED8;
extern const Color lbl_8064FEDC;
extern const float lbl_8064FEE0;

extern void fn_8010DAD0(u32);
extern void fn_8010DBE8(u8);
extern void fn_8010E3DC(void *);
extern void fn_8010F144(void);
extern void fn_8010F148(int, int, int);
extern void fn_80119224(int, u8);
extern void fn_80121114(void *, int, int, int, int, int);
extern u32 fn_801578A0(void *);
extern int fn_801578AC(void *);
extern u8 fn_80157918(void *);
extern u16 fn_80157994(void *);
extern u8 fn_80157AB8(void *);
extern int fn_8015821C(void *);
extern u16 fn_80158234(void *);
extern void fn_801A852C(Color, int, int, u32);
extern void fn_801A872C(int, int, int, int, int, int, Color);
extern void fn_801A88D0(int, int, int, int, int, int);
extern void fn_801A8974(int, int, int, int, int, int);
extern void fn_801A8D38(int);
extern void fn_801A8DE8(void *, s16, s16, s16, s16, int, int, int);
extern void fn_801A9118(int, u16, int);
extern int fn_801A9384(s16, s16, s16, s16, s16, s16, s16, s16);
extern void fn_801E3A34(Color);
extern void fn_801E3AA4(int);
extern void fn_801E5430(short, short);
extern void fn_801E56AC(float, const char *, ...);
extern void fn_801E5AD0(u8);
extern u8 *fn_801E5D08(int);
extern s16 fn_801E6350(void *);
extern s16 fn_801E6380(void *);
extern s16 fn_801E63F0(void *);
extern s16 fn_801E6420(void *);
extern u32 fn_801E7578(u32);
extern int fn_801E779C(u32, int);
extern int fn_801E79FC(void *, int);
extern int fn_801E8D24(int);
extern int fn_801E8D3C(int);
extern void fn_801ECEC8(int, int, int);
extern void fn_801ECF50(int);
extern void fn_801ED3F4(int);
extern void fn_801ED5F4(int, int, int, int, int, float);
extern void fn_801F03F0(Block52 *, int);
extern void fn_801F683C(Block52 *);
extern void GXBegin(int, int, int);

static inline Color FadeColor(Color color, u8 alpha)
{
    color.a = lbl_8064CCD4 == 0 ? alpha : 100;
    return color;
}

void fn_8010E448(u8 alpha)
{
    MenuText *text = &lbl_8024B310;
    SlotTable *table = &lbl_80330D80;
    Slot *primary;
    Slot *secondary;
    int i;
    int mode;
    int left;
    int right;
    int top;
    int bottom;
    void *actor;
    int icon;
    int kind;
    int count;
    int diff;
    int *values = table->values;
    int *stats;
    int current;
    int selected;
    Slot *slot;
    void **object;
    Slot *other;
    int n;
    int j;
    Block52 copy;
    Block52 source;
    Block52 overlayCopy;
    Block52 overlaySource;

    diff = 0;
    mode = lbl_8064CCD4;
    current = fn_801E8D24(values[1]) * 2 + fn_801E8D24(table->values[0]);
    fn_80119224(1, alpha);
    if (fn_801E79FC(lbl_8064C4E0, 0x259) != 0) {
        fn_801A852C(lbl_8064C2A8, 0, 0x16, 0x80000000);
        fn_801A9118(0x14, 0x4C, 5);
    }
    if (fn_801E79FC(lbl_8064C4E0, 0x25B) != 0) {
        fn_801A852C(lbl_8064C2A8, 0, 0x17, 0x80000000);
        fn_801A9118(0x14, 0x50, 5);
    }
    if (lbl_8064CCD8 >= 0x10 && lbl_8064CCD8 <= 0x100) {
        mode = 1;
    }
    fn_8010DBE8(alpha);
    fn_801F683C(&source);
    copy = source;
    fn_801F03F0(&copy, 0);

    for (n = 0, slot = table->extra; n < 32; n++, slot++) {
        if (slot->object != 0) {
            fn_8010E3DC(slot->object);
        }
    }
    secondary = table->secondary;
    primary = table->primary;
    for (j = 0, slot = secondary, other = primary; j < 6; j++, slot++, other++) {
        if (j == current) {
            if (mode >= 6 || mode < 3) {
                if (slot->object != 0) {
                    fn_8010E3DC(slot->object);
                }
                if (other->object != 0) {
                    fn_8010E3DC(other->object);
                }
            }
        } else {
            if (slot->object != 0) {
                fn_8010E3DC(slot->object);
            }
            if (other->object != 0) {
                fn_8010E3DC(other->object);
            }
        }
    }
    fn_801ED3F4(lbl_8064CD7C);
    fn_801A8D38(6);
    if ((lbl_8064CCC4 > 0 || lbl_8064CCD8 != 0) && mode != 2) {
        fn_8010DAD0(lbl_8064CCD8);
    }

    switch (mode) {
    case 2: {
        s16 row;

        stats = table->values;
        row = fn_801E8D24(stats[4]) * 0x60 + 0xA5;
        fn_801A88D0((s16)(fn_801E8D24(stats[3]) * 0x5A + 0x165), row, 0x52, 0x56, -0x7697, 3);
        diff = fn_801E8D3C(stats[4]);
        diff -= fn_801E8D3C(values[1]);
        fn_8010DAD0(lbl_8064CCCC);
    }
    case 1:
    case 3:
    case 4:
    case 5:
        if (lbl_8064CCD8 >= 0x10 && lbl_8064CCD8 <= 0x100) {
            if (lbl_8064CCD4 == 1) {
                fn_801A8974(0x116, ((s16 *)((u8 *)text + 0xC8))[fn_801E779C(lbl_8064CCD8 >> 4, 0)], 0x46, 0x20, -0x7698, 3);
            } else {
                fn_801A872C(0x116, text->icons[fn_801E779C(lbl_8064CCD8 >> 4, 0)], 0x46, 0x20, -0x7698, 3, lbl_8064C2BC);
            }
        } else {
            if (lbl_8064CCD4 == 1) {
                stats = table->values;
                fn_801A8974(0x116, text->icons[fn_801E8D24(stats[2])], 0x46, 0x20, -0x7698, 3);
            } else {
                stats = table->values;
                fn_801A872C(0x116, text->icons[fn_801E8D24(stats[2])], 0x46, 0x20, -0x7698, 3, lbl_8064C2BC);
            }
        }
    case 0:
        if (lbl_8064CCC4 > 0 && lbl_8064CCD8 == 0) {
            selected = fn_801E8D24(values[1]) - diff;
            left = 0;
            right = 0;
            top = 0;
            bottom = 0;
            if (lbl_8064CCC8 != 0) {
                left = fn_801E6380(lbl_8064CCC8) + 6;
                right = fn_801E6380(lbl_8064CCC8) + (fn_801E6420(lbl_8064CCC8) + 6);
                top = fn_801E6350(lbl_8064CCC8) + 6;
                bottom = fn_801E6350(lbl_8064CCC8) + (fn_801E63F0(lbl_8064CCC8) + 6);
            }
            if (selected >= 0 && selected < 3) {
                if (lbl_8064CCD4 == 0) {
                    fn_801A8974((s16)(fn_801E8D24(table->values[0]) * 0x5A + 0x165), (s16)(selected * 0x60 + 0xA5), 0x52, 0x56, -0x7698, 3);
                } else {
                    fn_801A872C((s16)(fn_801E8D24(table->values[0]) * 0x5A + 0x165), (s16)(selected * 0x60 + 0xA5), 0x52, 0x56, -0x7698, 3, lbl_8064C2BC);
                }
            }

            for (i = 0; i < 6; i++, primary++, secondary++) {
                actor = primary->actor;
                if (actor != 0) {
                    icon = 0;
                    kind = fn_80157AB8(actor);
                    if (fn_80158234(actor) != 0 || fn_8015821C(actor) == 0x18 || fn_8015821C(actor) == 0x3A ||
                        fn_8015821C(actor) == 0xDA || fn_8015821C(actor) == 0x3B || fn_8015821C(actor) == 0x96 ||
                        fn_8015821C(actor) == 0xF1) {
                        s16 x = (i & 1) * 0x5A + 0x1B3;
                        s16 y = (i >> 1) * 0x60 + 0xE1;
                        if (fn_801A9384(x - 0x14, y, x, y + 0x14, top, left, bottom, right) == 0) {
                            int count = fn_80157994(actor);
                            if (secondary->actor != 0) {
                                count += fn_80157994(secondary->actor);
                            }
                            fn_801E3AA4(0);
                            fn_801E3A34(lbl_8064C2B0);
                            fn_801E5AD0(0x72);
                            fn_801E5430(x, y);
                            fn_801E56AC(lbl_8064FE90, lbl_8064B880, count);
                        }
                    }
                    if (kind != 0) {
                        int row;
                        int offset;
                        int flags;
                        s8 color;

                        fn_801E3AA4(0);
                        fn_801E3A34(lbl_8064C2A8);
                        fn_801E5AD0(0x63);
                        switch (kind) {
                        case 1:
                            flags = 0x20;
                            color = 0x63;
                            break;
                        case 2:
                            flags = 8;
                            color = 0x62;
                            break;
                        case 3:
                            flags = 0x10;
                            color = 0x67;
                            break;
                        case 4:
                            flags = 0x40;
                            color = 0x6D;
                            break;
                        }
                        fn_801ED5F4(1, flags | 0x402, 1, 0, 0, lbl_8064FE70);
                        offset = (i & 1) * 0x5A;
                        row = (i >> 1) * 0x60 + 0xA7;
                        fn_801E5430(offset + 0x174, row);
                        fn_801E56AC(lbl_8064FE90, text->countFormat, color, kind + 0x1A);
                        fn_801E5430(offset + 0x1A6, row);
                        fn_801E56AC(lbl_8064FE90, lbl_8064B884, fn_80157918(actor) + 0x16);
                        fn_801ED5F4(0, 2, 1, 0, 0, lbl_8064FE70);
                        fn_801A8D38(6);
                    }
                    if ((int)fn_801E7578(fn_801578A0(actor) > 1) != 0) {
                        switch (fn_801578AC(actor)) {
                        case 1:
                            icon = 7;
                            break;
                        case 2:
                        case 0x80:
                            icon = 8;
                            break;
                        case 4:
                            icon = 9;
                            break;
                        case 8:
                            icon = 0xA;
                            break;
                        case 0x10:
                            icon = 0xB;
                            break;
                        case 0x20:
                            icon = 0x10;
                            break;
                        case 0x40:
                            icon = 0x11;
                            break;
                        }
                        if (icon != 0) {
                            s16 x = (i & 1) * 0x5A + 0x16A;
                            s16 y = (i >> 1) * 0x60 + 0xDC;

                            fn_801ED3F4(lbl_8064CD7C);
                            fn_801A852C(lbl_8064C2A8, 0, icon, 0x80000000);
                            fn_801A8DE8(lbl_802515D0, x, y, x + 0x18, y + 0x18, -1, 0, 5);
                        }
                    }
                }
            }

            switch (mode) {
            case 3:
            case 4:
            case 5:
                fn_801A852C(lbl_8064FED8, 0, -1, 0x80000000);
                fn_801ECF50(4);
                fn_801ECEC8(1, 7, 1);
                GXBegin(0x80, 5, 4);
                fn_8010F148(-0x6A, 0, -0x7698);
                fn_8010F148(0x2EA, 0, -0x7698);
                fn_8010F148(0x2EA, 0x1E0, -0x7698);
                fn_8010F148(-0x6A, 0x1E0, -0x7698);
                fn_8010F144();
                fn_801F683C(&overlaySource);
                overlayCopy = overlaySource;
                fn_801F03F0(&overlayCopy, 0);
                fn_801ECEC8(1, 3, 1);
                object = &table->secondary[current].object;
                if (*object != 0) {
                    fn_80121114(*object, 0, 30000, 0, 0, 1);
                    fn_80121114(*object, 0, 30000, 1, 0, 1);
                }
                object = &table->primary[current].object;
                if (*object != 0) {
                    fn_80121114(*object, 0, 30000, 0, 0, 1);
                    fn_80121114(*object, 0, 30000, 1, 0, 1);
                }
                fn_801ED3F4(lbl_8064CD7C);
                fn_801A8D38(6);
                break;
            }
        }
        break;
    }

    fn_801E3AA4(0);
    fn_801E5AD0(0x63);
    fn_801E3A34(FadeColor(lbl_8064FEDC, alpha));

    switch (mode) {
    case 2:
        count = fn_801E8D3C(table->values[4]);
        if (count != 0) {
            fn_801E5430(0x225, 0xF5);
            fn_801E56AC(lbl_8064FE70, lbl_8064B88C);
        }
        if ((count + 3) * 2 <= lbl_8064CCC4) {
            fn_801E5430(0x225, 0x132);
            fn_801E56AC(lbl_8064FE70, lbl_8064B894);
        }
        break;
    case 0:
    case 1:
    case 3:
    case 4:
    case 5:
        count = fn_801E8D3C(values[1]);
        if (count != 0) {
            fn_801E5430(0x225, 0x109);
            fn_801E56AC(lbl_8064FE70, lbl_8064B88C, 7);
        }
        if ((count + 3) * 2 < lbl_8064CCC4) {
            fn_801E5430(0x225, 0x132);
            fn_801E56AC(lbl_8064FE70, lbl_8064B894, 8);
        }
        break;
    }

    if (lbl_8064CCD8 != 0 && !(lbl_8064CCD8 & 0x200)) {
        u8 *text = fn_801E5D08(lbl_8064CDB4);
        if (text != 0) {
            text[3] = 0;
        }
        text = fn_801E5D08(lbl_8064CDB0);
        if (text != 0) {
            text[3] = 0;
        }
    }

    if (lbl_8064CDBC != 0) {
        fn_801E3AA4(0);
        fn_801E5430(10, 10);
        fn_801E56AC(lbl_8064FEE0, lbl_8064B89C);
        switch (lbl_8064CDB8) {
        case 0:
            fn_801E56AC(lbl_8064FE70, text->modeText[0]);
            break;
        case 1:
            fn_801E56AC(lbl_8064FE70, text->modeText[1]);
            break;
        case 2:
            fn_801E56AC(lbl_8064FE70, text->modeText[2]);
            break;
        }
        fn_801E56AC(lbl_8064FE90, text->footer);
    }
}
