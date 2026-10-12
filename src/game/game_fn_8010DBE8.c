typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef float f32;
typedef struct Color { u8 r, g, b, a; } Color;

typedef struct EffectState {
    u8 pad_00[4];
    f32 x;
    f32 y;
    f32 scale_x;
    f32 scale_y;
    s32 mode;
    u8 pad_18[4];
    s32 variant;
    s16 left;
    s16 top;
    s16 duration;
    u8 pad_26[4];
    u8 alpha;
    u8 pad_2B;
} EffectState;

extern u8 lbl_802515D0[];
extern void *lbl_8064C4E0;
extern int lbl_8064C4E8;
extern u32 lbl_8064CCD8;
extern int lbl_8064CD7C;
extern const f32 lbl_8064FE9C;
extern const Color lbl_8064FEA4;
extern const Color lbl_8064FEA8;
extern const Color lbl_8064FEAC;
extern const Color lbl_8064FEB0;
extern const Color lbl_8064FEB4;
extern const Color lbl_8064FEB8;
extern const Color lbl_8064FEBC;
extern const f32 lbl_8064FEC0;
extern const f32 lbl_8064FEC4;
extern const f32 lbl_8064FEC8;
extern const f32 lbl_8064FECC;
extern const f32 lbl_8064FED0;
extern const f32 lbl_8064FED4;

extern void fn_80026768(EffectState *);
extern int fn_80038308(void *, int, s16 *);
extern int fn_80038464(void *, int, s16 *);
extern void fn_801A852C(Color, int, int, u32);
extern void fn_801A8DE8(void *, s16, s16, s16, s16, int, int, int);
extern int fn_801E79FC(void *, int);
extern void fn_801ED3F4(int);
extern void *fn_80201814(void);
extern void fn_80201B44(void);

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

static inline Color WithAlpha(Color color, u8 alpha)
{
    color.a = alpha;
    return color;
}

void fn_8010DBE8(u8 alpha)
{
    void *object;
    s16 cur0;
    s16 max0;
    s16 cur1;
    s16 max1;
    s16 cur2;
    s16 max2;
    f32 ratio0;
    f32 ratio1;
    f32 ratio2;
    f32 level0;
    f32 level1;
    f32 level2;
    f32 scale;
    EffectState effect;

    fn_80201B44();
    object = fn_80201814();
    fn_80038308(object, 0, &cur0);
    fn_80038308(object, 2, &cur2);
    fn_80038308(object, 1, &cur1);
    fn_80038464(object, 0, &max0);
    fn_80038464(object, 2, &max2);
    fn_80038464(object, 1, &max1);
    ratio0 = (f32)cur0 / (f32)max0;
    ratio1 = (f32)cur1 / (f32)max1;
    ratio2 = (f32)cur2 / (f32)max2;
    level0 = MIN(1.0f, MAX(ratio0, 0.0f));
    level1 = MIN(1.0f, MAX(ratio1, 0.0f));
    level2 = MIN(1.0f, MAX(ratio2, 0.0f));
    fn_801ED3F4(lbl_8064CD7C);
    fn_801A852C(WithAlpha(lbl_8064FEA4, alpha), 5, 0x14, 0x80000000);

    if (lbl_8064CCD8 & 2) {
        int y;
        s16 top;
        s16 bottom;
        int pos;

        scale = (f32)max0 / lbl_8064FE9C;
        y = lbl_8064FEC0 - lbl_8064FEC4 * scale;
        top = y;
        pos = (f32)top + lbl_8064FEC8 * scale;
        fn_801A8DE8(lbl_802515D0, 0x97, y - 0x26, 0xBF, top, -0x7698, 0, 5);
        fn_801A852C(WithAlpha(lbl_8064FEA8, alpha), 5, 5, 0x80000000);
        bottom = pos;
        fn_801A8DE8(lbl_802515D0, 0x97, top, 0xBF, bottom, -0x7698, 0, 5);
        fn_801A852C(WithAlpha(lbl_8064FEAC, alpha), 5, 0x15, 0x80000000);
        fn_801A8DE8(lbl_802515D0, 0x97, bottom, 0xBF, pos + 0x25, -0x7698, 0, 5);
    }
    if (lbl_8064CCD8 & 1) {
        int y;
        int pos;
        s16 top;
        s16 bottom;

        scale = (f32)max2 / lbl_8064FE9C;
        y = lbl_8064FECC - lbl_8064FEC4 * scale;
        top = y;
        pos = (f32)top + lbl_8064FEC8 * scale;
        fn_801A8DE8(lbl_802515D0, 0xE9, y - 0x26, 0x10F, top, -0x7698, 0, 5);
        fn_801A852C(WithAlpha(lbl_8064FEB0, alpha), 5, 5, 0x80000000);
        bottom = pos;
        fn_801A8DE8(lbl_802515D0, 0xE9, top, 0x10F, bottom, -0x7698, 0, 5);
        fn_801A852C(WithAlpha(lbl_8064FEB4, alpha), 5, 0x15, 0x80000000);
        fn_801A8DE8(lbl_802515D0, 0xE9, bottom, 0x10F, pos + 0x25, -0x7698, 0, 5);
    }
    if (lbl_8064CCD8 & 4) {
        int y;
        int pos;
        s16 top;
        s16 bottom;

        scale = (f32)max0 / lbl_8064FE9C;
        y = lbl_8064FED0 - lbl_8064FEC4 * scale;
        top = y;
        pos = (f32)top + lbl_8064FEC8 * scale;
        fn_801A8DE8(lbl_802515D0, 0xE9, y - 0x26, 0x10F, top, -0x7698, 0, 5);
        fn_801A852C(WithAlpha(lbl_8064FEB8, alpha), 5, 5, 0x80000000);
        bottom = pos;
        fn_801A8DE8(lbl_802515D0, 0xE9, top, 0x10F, bottom, -0x7698, 0, 5);
        fn_801A852C(WithAlpha(lbl_8064FEBC, alpha), 5, 0x15, 0x80000000);
        fn_801A8DE8(lbl_802515D0, 0xE9, bottom, 0x10F, pos + 0x25, -0x7698, 0, 5);
    }

    effect.mode = 0;
    effect.alpha = 200;
    effect.duration = 500;
    if (fn_801E79FC(lbl_8064C4E0, 0x2CC) != 0) {
        fn_80038464(object, 1, &max0);
        scale = (f32)max0 / lbl_8064FE9C;
        effect.left = 0x9C;
        effect.variant = 1;
        effect.x = level1;
        effect.y = level1;
        effect.scale_y = scale;
        effect.scale_x = scale;
        effect.top = 0x3C - (int)(lbl_8064FED4 * scale);
        fn_801ED3F4(lbl_8064C4E8);
        fn_80026768(&effect);
    }
    if (fn_801E79FC(lbl_8064C4E0, 0x257) != 0) {
        fn_80038464(object, 2, &max0);
        scale = (f32)max0 / lbl_8064FE9C;
        effect.left = 0xED;
        effect.variant = 2;
        effect.x = level2;
        effect.y = level2;
        effect.scale_y = scale;
        effect.scale_x = scale;
        effect.top = 0xAB - (int)(lbl_8064FED4 * scale);
        fn_801ED3F4(lbl_8064C4E8);
        fn_80026768(&effect);
    }
    if (fn_801E79FC(lbl_8064C4E0, 0x2B6) != 0) {
        fn_80038464(object, 0, &max0);
        scale = (f32)max0 / lbl_8064FE9C;
        effect.left = 0xED;
        effect.variant = 0;
        effect.x = level0;
        effect.y = level0;
        effect.scale_y = scale;
        effect.scale_x = scale;
        effect.top = 0x15F - (int)(lbl_8064FED4 * scale);
        fn_801ED3F4(lbl_8064C4E8);
        fn_80026768(&effect);
    }
}
