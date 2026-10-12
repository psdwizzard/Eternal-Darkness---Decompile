typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed long s32;
typedef float Matrix34[3][4];

typedef union Color {
    u32 word;
    struct { u8 r, g, b, a; } channel;
} Color;

typedef struct MapEntry {
    short x0, y0, x1, y1;
    signed char region;
    u8 layer;
    u8 icon;
    u8 padding;
} MapEntry;

typedef struct Entry80201814 Entry80201814;
typedef struct Object8020216C Object8020216C;

extern int lbl_803003C8[];
extern int lbl_8064D184;
extern u32 lbl_8064CD80;
extern u32 lbl_8064CDE0;
extern int lbl_8064CDAC;
extern MapEntry *lbl_8064CDE4;
extern int lbl_8064CDE8;
extern int lbl_8064CDEC;
extern float lbl_8064CDF8;
extern int lbl_8064CE04;
extern int lbl_8064CE08;
extern u8 lbl_8064CE0C;
extern unsigned int *lbl_8064D158;
extern Color lbl_8064C2A8;
extern Color lbl_8064C2C0;
extern Color lbl_8024EA34[];
extern u8 lbl_802515D0[];
extern u8 lbl_8024E818[];

extern int fn_80201B44(void);
extern Entry80201814 *fn_80201814(int);
extern unsigned int fn_8020216C(Object8020216C *);
extern unsigned int fn_801ED3F4(unsigned int);
extern void fn_801A8EDC(void *);
extern void fn_801A852C(u32 *, int, u16, u32);
extern void fn_801A8F08(s32, s32, s32, s32, s32, s32, void *);
extern void fn_8022A044(int, int, int, int, int);
extern void fn_8022A7D4(int);
extern void fn_801A90BC(void *, void *);
extern int fn_801E79FC(unsigned int *, unsigned int);
extern int fn_801199A0(int);
extern void fn_801ED5F4(int, int, short, float *, Matrix34, float);
extern void fn_801A8660(s32, s32, s32, s32, s32, const u32 *);
extern void fn_801A8D38(s32);
extern void fn_80119224(int, u8);

extern const float lbl_8064FFD0; /* 66.0 */
extern const float lbl_8064FFD4; /* 62.0 */
extern const float lbl_8064FFD8; /* 34.0 */
extern const float lbl_8064FFDC; /* 30.0 */
extern const float lbl_8064FFE0; /* 72.0 */
extern const float lbl_8064FFE4; /* 21.0 */
extern const float lbl_8064FFE8; /* 40.0 */
extern const float lbl_8064FFEC; /* -11.0 */
extern const float lbl_8064FFF0; /* 49.0 */
extern const float lbl_8064FFF4; /* 87.0 */
extern const float lbl_8064FFF8; /* 17.0 */
extern const float lbl_8064FFFC; /* 55.0 */
extern const float lbl_80650000; /* 70.0 */
extern const float lbl_80650004; /* 38.0 */
extern const float lbl_80650008; /* 138.0 */
extern const float lbl_8065000C; /* 106.0 */
extern const float lbl_80650010; /* 20.0 */
extern const float lbl_80650014; /* 3.0 */
extern const float lbl_80650018; /* 2.0 */
extern const float lbl_8064FFBC; /* 1.0 */

/* Draw the map layers, room overlays, and selected-room corner markers. */
void fn_80119F98(u8 alpha)
{
    int entryOffset;
    int reveal;
    unsigned int index;
    int selected;
    int layer;
    int depth;
    s32 entryDepth;
    int opacity;
    int draw;
    float x0, y0, x1, y1;
    Color color;

    reveal = 1;
    if (!(fn_8020216C((Object8020216C *)fn_80201814(fn_80201B44())) & 0x40000)
        && lbl_803003C8[0] != 8) {
        reveal = 0;
    }
    selected = lbl_8064D184;
    if (selected >= 400 && selected <= 411) {
        selected -= 164;
    }

    fn_801ED3F4(lbl_8064CD80);
    fn_801A8EDC(lbl_802515D0);
    {
        u32 copy = lbl_8064C2A8.word;
        fn_801A852C(&copy, 0, 0, 0x80000000);
    }
    fn_801A8F08(144, 0, 575, 479, -30360, 0, (void *)5);
    fn_8022A044(7, 0, 0, 5, 0);
    fn_8022A7D4(0);
    fn_801A90BC(lbl_802515D0, lbl_8024E818);

    if (lbl_8064CDE0 != 0 && lbl_8064CDAC != 0) {
        depth = -2810;
        fn_801ED3F4(lbl_8064CDE0);
        fn_801A8EDC(lbl_802515D0);
        /* Re-read the table after rendering calls; keep the byte offset across them. */
        for (layer = 0; layer < 7; layer++) {
            for (index = 0, entryOffset = 0; index < 351; index++, entryOffset += sizeof(MapEntry)) {
                if (layer == ((MapEntry *)((u8 *)lbl_8064CDE4 + entryOffset))->layer
                    && lbl_8064CDEC == ((MapEntry *)((u8 *)lbl_8064CDE4 + entryOffset))->region) {
                    color = lbl_8024EA34[((MapEntry *)((u8 *)lbl_8064CDE4 + entryOffset))->layer];
                    entryDepth = depth;
                    opacity = 255;
                    draw = 0;
                    if (lbl_8064CDE8 == ((MapEntry *)((u8 *)lbl_8064CDE4 + entryOffset))->layer) {
                        entryDepth += 2457;
                    } else {
                        opacity = 40;
                        color.channel.r >>= 1;
                        color.channel.g >>= 1;
                        color.channel.b >>= 1;
                    }
                    if (fn_801E79FC(lbl_8064D158, index) != 0) {
                        u32 copy;
                        color.channel.a = opacity;
                        copy = color.word;
                        fn_801A852C(&copy, 5, ((MapEntry *)((u8 *)lbl_8064CDE4 + entryOffset))->icon, 0x80000000);
                        draw = 1;
                    } else if (reveal && index != 323 && index != 324) {
                        u32 copy;
                        color.channel.a = opacity;
                        copy = color.word;
                        fn_801A852C(&copy, 5, ((MapEntry *)((u8 *)lbl_8064CDE4 + entryOffset))->icon, 0x80000000);
                        draw = 1;
                    }
                    if (draw) {
                        x0 = lbl_8064CDF8 * (((MapEntry *)((u8 *)lbl_8064CDE4 + entryOffset))->x0 - lbl_8064CE08 - 361) + 360.0f;
                        y0 = lbl_8064CDF8 * (((MapEntry *)((u8 *)lbl_8064CDE4 + entryOffset))->y0 - lbl_8064CE04 - 241) + 240.0f;
                        x1 = lbl_8064CDF8 * (((MapEntry *)((u8 *)lbl_8064CDE4 + entryOffset))->x1 - lbl_8064CE08 - 360) + 360.0f;
                        y1 = lbl_8064CDF8 * (((MapEntry *)((u8 *)lbl_8064CDE4 + entryOffset))->y1 - lbl_8064CE04 - 240) + 240.0f;
                        fn_801A8F08((int)x0, (int)y0, (int)x1, (int)y1, entryDepth, 0, (void *)5);
                        /* These rooms use a smaller overlay within their map rectangle. */
                        if (fn_801199A0(index)) {
                            switch (index) {
                            case 201:
                                x1 = x0 + lbl_8064FFD0 * lbl_8064CDF8;
                                y1 = y0 + lbl_8064FFD4 * lbl_8064CDF8;
                                x0 += lbl_8064FFD8 * lbl_8064CDF8;
                                y0 += lbl_8064FFDC * lbl_8064CDF8;
                                break;
                            case 204:
                                x1 = x0 + lbl_8064FFE0 * lbl_8064CDF8;
                                y1 = y0 + lbl_8064FFE4 * lbl_8064CDF8;
                                x0 += lbl_8064FFE8 * lbl_8064CDF8;
                                y0 += lbl_8064FFEC * lbl_8064CDF8;
                                break;
                            case 207:
                                x1 = x0 + lbl_8064FFF0 * lbl_8064CDF8;
                                y1 = y0 + lbl_8064FFF4 * lbl_8064CDF8;
                                x0 += lbl_8064FFF8 * lbl_8064CDF8;
                                y0 += lbl_8064FFFC * lbl_8064CDF8;
                                break;
                            case 199:
                                x1 = x0 + lbl_80650000 * lbl_8064CDF8;
                                y1 = y0 + lbl_80650000 * lbl_8064CDF8;
                                x0 += lbl_80650004 * lbl_8064CDF8;
                                y0 += lbl_80650004 * lbl_8064CDF8;
                                break;
                            case 213:
                                x1 = x0 + lbl_80650008 * lbl_8064CDF8;
                                y1 = y0 + lbl_80650000 * lbl_8064CDF8;
                                x0 += lbl_8065000C * lbl_8064CDF8;
                                y0 += lbl_80650004 * lbl_8064CDF8;
                                break;
                            }
                            fn_801ED3F4(lbl_8064CD80);
                            color.channel.r = 10;
                            color.channel.g = 10;
                            color.channel.b = 10;
                            if (lbl_8064CDE8 == ((MapEntry *)((u8 *)lbl_8064CDE4 + entryOffset))->layer) {
                                color.channel.a = alpha;
                            }
                            {
                                u32 copy = color.word;
                                fn_801A852C(&copy, 5, 58, 0x80000000);
                            }
                            fn_801A8F08((int)x0, (int)y0, (int)x1, (int)y1, entryDepth, 0, (void *)5);
                            fn_801ED3F4(lbl_8064CDE0);
                        }
                        depth--;
                    }
                }
            }
        }
    }

    fn_801ED3F4(lbl_8064CD80);
    fn_801A90BC(lbl_802515D0, lbl_8024E818);
    if (selected >= 0 && lbl_8064CDEC >= 0
        && lbl_8064CDE8 == lbl_8064CDE4[selected].layer && lbl_8064CE0C) {
        /* Two perpendicular strokes mark each corner of the selected room. */
        int left;
        int top;
        int right;
        int thickness;
        int bottom;
        int length;

        length = lbl_80650010 * lbl_8064CDF8;
        thickness = lbl_80650014 * lbl_8064CDF8;
        left = lbl_8064CDF8 * (lbl_8064CDE4[selected].x0 - 368 - lbl_8064CE08) + 360.0f;
        top = lbl_8064CDF8 * (lbl_8064CDE4[selected].y0 - 248 - lbl_8064CE04) + 240.0f;
        right = lbl_8064CDF8 * (lbl_8064CDE4[selected].x1 - 352 - lbl_8064CE08) + 360.0f;
        bottom = lbl_8064CDF8 * (lbl_8064CDE4[selected].y1 - 232 - lbl_8064CE04) + 240.0f;

        fn_801ED5F4(1, 0x502, 1, 0, 0, lbl_80650018);
        {
            u32 copy = lbl_8064C2C0.word;
            fn_801A8660(left, top, (short)thickness, (short)length, -2, &copy);
        }
        {
            u32 copy = lbl_8064C2C0.word;
            fn_801A8660(left, top, (short)length, (short)thickness, -2, &copy);
        }
        {
            u32 copy = lbl_8064C2C0.word;
            fn_801A8660(right, top, -(short)thickness, (short)length, -2, &copy);
        }
        {
            u32 copy = lbl_8064C2C0.word;
            fn_801A8660(right, top, -(short)length, (short)thickness, -2, &copy);
        }
        {
            u32 copy = lbl_8064C2C0.word;
            fn_801A8660(right, bottom, -(short)thickness, -(short)length, -2, &copy);
        }
        {
            u32 copy = lbl_8064C2C0.word;
            fn_801A8660(right, bottom, -(short)length, -(short)thickness, -2, &copy);
        }
        {
            u32 copy = lbl_8064C2C0.word;
            fn_801A8660(left, bottom, (short)thickness, -(short)length, -2, &copy);
        }
        {
            u32 copy = lbl_8064C2C0.word;
            fn_801A8660(left, bottom, (short)length, -(short)thickness, -2, &copy);
        }
        fn_801ED5F4(0, 2, 1, 0, 0, lbl_8064FFBC);
    }
    fn_801A8D38(6);
    fn_80119224(2, alpha);
}
