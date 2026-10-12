typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef float f32;

#pragma use_lmw_stmw on

typedef struct EffectState {
    u8 pad_00[4];
    f32 x;
    f32 y;
    f32 scale;
    u8 pad_10[4];
    s32 mode;
    u8 pad_18[4];
    s32 variant;
    s16 left;
    s16 top;
    u8 pad_24[6];
    u8 alpha;
} EffectState;

typedef struct GXColor {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} GXColor;

typedef struct ParticlePoint {
    s16 x;
    s16 y;
} ParticlePoint;

typedef struct ColorValues {
    u32 words[6];
} ColorValues;

typedef union EdgeValues {
    u32 words[3];
    s16 half[6];
} EdgeValues;

static u16 effect_resource[40] = {
    0x0000, 0x0200, 0x01F0, 0x0200, 0x01F0, 0x0108, 0x0000, 0x0108,
    0x0000, 0x0100, 0x01F0, 0x0100, 0x01F0, 0x0008, 0x0000, 0x0008,
    0x0000, 0x016A, 0x0000, 0x016A, 0x0000, 0x016A, 0x0000, 0x016A,
    0x0000, 0x016A, 0x0200, 0x016A, 0x0200, 0x00C0, 0x0000, 0x00C0,
    0x0000, 0x016A, 0x0400, 0x016A, 0x0400, 0x0015, 0x0000, 0x0015,
};
static ParticlePoint particle_points[3][5] = {0};
static s16 particle_delays[3][5] = {0};
static s16 particle_ages[3][5] = {
    {12, 12, 12, 12, 12},
    {12, 12, 12, 12, 12},
    {12, 12, 12, 12, 12},
};
static GXColor particle_colors[3] = {
    {0xFF, 0x64, 0x64, 0xFF},
    {0xC8, 0xFF, 0x80, 0xFF},
    {0xAF, 0xAF, 0xFF, 0xFF},
};

extern const ColorValues lbl_80238C28;
extern const EdgeValues lbl_80238C40;
extern GXColor lbl_8064C2A8;
extern u32 lbl_8064CD7C;
extern s32 lbl_8064D5A8;
extern u8 lbl_8064C6E8;
extern const GXColor lbl_8064DF88;
extern const GXColor lbl_8064DF8C;

extern void fn_801F1034(void);
extern void fn_801A852C(GXColor*, int, u16, u32);
extern void fn_801A85D4(GXColor*, u16, u16, u32);
extern void fn_801ECF50(u32);
extern void fn_80226AB4(s32, s32, u16);
extern void fn_80225F4C(s32, void*, u8);
extern void fn_80026740(void);
extern void fn_80026754(s32, s32, s32);
extern void fn_80026DAC(u16, u16);
extern void fn_80026DBC(u32);
extern unsigned int fn_800FBFB0(void);
extern u32 fn_801ED3F4(u32);
extern void fn_801A8F08(s16, s16, s16, s16, s16, u16, s32);

static const s16 depth_near = -1;
static const s16 depth_far = -30360;

void fn_80026768(EffectState* state)
{
    ColorValues colors;
    EdgeValues edge;
    u32 packed[6];
    u8 alpha;
    u8 depth_alpha;
    u32 packed_alpha;
    s16 quad_left;
    s16 quad_right;
    s32 limit;
    s32 i;
    s16 quad_depth;
    s32 x0;
    s32 x1;
    s32 bottom;
    s32 y1;
    s32 y0;
    s32 particle_origin;
    s32 particle_y_origin;
    s32 left;
    s16 texture;
    s32 depth;
    s32 variant;
    ParticlePoint* point;
    s16* delay;
    GXColor draw_color;
    GXColor particle_color;

    if (state == 0) {
        return;
    }
    if ((alpha = state->alpha) == 0) {
        return;
    }

    if (state->mode != 0) {
        alpha = (u8)(0.85f * alpha);
    }


    packed_alpha = alpha;
    colors = lbl_80238C28;
    edge = lbl_80238C40;

    depth_alpha = state->mode != 0 ? state->alpha >> 2 : state->alpha;
    texture = state->mode != 0 ? depth_near : depth_far;
    depth = depth_alpha | 0xFFFF0A00;
    variant = state->variant;

    left = state->left + 6;
    particle_origin =
        (s32)(61.0f * state->scale + 29.0f + state->top);
    x0 = (s32)(61.0f * state->y);
    x1 = (s32)(61.0f * state->x);
    packed[0] = packed_alpha | 0x0A0A0A00;
    packed[1] = packed_alpha | 0x0A0A0A00;
    packed[2] = depth;
    packed[3] = depth;
    packed[4] = colors.words[variant * 2] | packed_alpha;
    packed[5] = colors.words[variant * 2 + 1] | packed_alpha;
    if (x0 < x1) {
        s32 swap = x0;
        x0 = x1;
        x1 = swap;
    }
    y0 = (s32)(30.0f + (61 - x0) * state->scale);
    y1 = (s32)(30.0f + (61 - x1) * state->scale);
    bottom = (s32)(61.0f * state->scale + 30.0f);
    edge.half[1] = y0;
    edge.half[2] = y0;
    edge.half[3] = y1;
    edge.half[4] = y1;
    edge.half[5] = bottom;

    quad_left = left;
    fn_801F1034();
    draw_color = lbl_8064C2A8;
    fn_801A852C(&draw_color, -1, 0, 0);

    fn_801ECF50(9);
    quad_right = quad_left + 19;
    quad_depth = texture;
    for (i = 0; i < 6; i += 2) {
        s16 top = (s16)(state->top + edge.half[i]);
        s16 bot = (s16)(state->top + edge.half[i + 1]);
        u32 top_color = packed[i];
        u32 bottom_color = packed[i + 1];
        fn_80226AB4(0x80, 5, 4);
        fn_80026754((s16)quad_left, top, quad_depth);
        fn_80026DBC(top_color);
        fn_80026DAC(0, 0);
        fn_80026754((s16)quad_right, top, quad_depth);
        fn_80026DBC(top_color);
        fn_80026DAC(0, 0);
        fn_80026754((s16)quad_right, bot, quad_depth);
        fn_80026DBC(bottom_color);
        fn_80026DAC(0, 0);
        fn_80026754((s16)quad_left, bot, quad_depth);
        fn_80026DBC(bottom_color);
        fn_80026DAC(0, 0);
        fn_80026740();
    }

    fn_80225F4C(13, effect_resource, 4);
    {
        s32 j;
        s16* age;
        age = particle_ages[variant];
        particle_y_origin = (s16)(edge.half[4] + state->top);
        particle_colors[variant].a = state->alpha;
        particle_color = particle_colors[variant];
        fn_801A852C(&particle_color, 0, 9, 0x80000000);
        point = particle_points[variant];
        delay = particle_delays[variant];
        for (j = 0; j < 5; j++) {
            limit = particle_origin - particle_y_origin;
            if (age[j] == 1) {
                lbl_8064C6E8++;
                if (lbl_8064C6E8 >= 20) {
                    lbl_8064C6E8 = 0;
                }
            }
            if (age[j] >= 24) {
                point[j].y = limit + (fn_800FBFB0() & 0x1F);
                point[j].x = (fn_800FBFB0() & 7) + 2;
                delay[j] = (fn_800FBFB0() & 3) + 5;
                age[j] = 0;
            }
            if (point[j].y <= limit) {
                ParticlePoint* p = &point[j];
                fn_801A8F08(p->x + left,
                            p->y + particle_y_origin,
                            p->x + delay[j] + left,
                            p->y + delay[j] + particle_y_origin,
                            texture, (age[j] >> 3) * 4, 5);
            }
            if (point[j].y <= -3) {
                age[j]++;
            } else if (lbl_8064D5A8 % (10 - delay[j]) == 0) {
                point[j].y--;
            }
        }
    }

    fn_80225F4C(13, effect_resource, 4);
    if (state->mode != 0) {
        GXColor copy;
        GXColor color = lbl_8064DF88;
        color.a = state->alpha;
        copy = color;
        fn_801A852C(&copy, 0, 0, 0x80000000);
        fn_801A8F08(state->left, state->top, state->left + 31,
                    state->top + 30, depth_near, 0, 5);
        fn_801A8F08(state->left, state->top + edge.half[5],
                    state->left + 31,
                    state->top + edge.half[5] + 30, depth_near, 4, 5);
    } else {
        GXColor copy;
        GXColor color;
        fn_801ED3F4(lbl_8064CD7C);
        color = lbl_8064DF8C;
        color.a = state->alpha;
        copy = color;
        fn_801A85D4(&copy, 14, 15, 0x80000000);
        fn_801A8F08(state->left, state->top, state->left + 31,
                    state->top + 30, depth_far, 0, 5);
        fn_801A8F08(state->left, state->top + edge.half[5],
                    state->left + 31,
                    state->top + edge.half[5] + 30, depth_far, 4, 5);
    }
}
