typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef u32* Color;
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

typedef struct EffectData {
    char resource[0x50];
    /* Three groups of five; flat arrays permit base + variant * 5 traversal. */
    ParticlePoint point[15];
    s16 delay[15];
    u8 pad_AA[2];
    s16 age[15];
    u8 pad_CA[2];
    u32 color[3];
} EffectData;

extern const ColorValues lbl_80238C28;
extern const EdgeValues lbl_80238C40;
extern EffectData lbl_8023DEB0;
extern u32 lbl_8064C2A8;
extern void* lbl_8064CD7C;
extern s32 lbl_8064D5A8;
extern u8 lbl_8064C6E8;
extern const u32 lbl_8064DF88;
extern const u32 lbl_8064DF8C;
extern const f32 lbl_8064DF90;
extern const f32 lbl_8064DF94;
extern const f32 lbl_8064DF98;
extern const f32 lbl_8064DF9C;

extern void fn_801F1034(void);
extern void fn_801A852C(Color, int, int, u32);
extern void fn_801A85D4(u32*, s32, s32, u32);
extern void fn_801ECF50(s32);
extern void fn_801A8D38(int);
extern void GXBegin(s32, s32, s32);
extern void GXSetArray(s32, void*, s32);
extern void fn_80026740(void);
extern void fn_80026754(s32, s32, s32);
extern void fn_80026DAC(s32, s32);
extern void fn_80026DBC(u32);
extern unsigned int rand(void);
#define rand() ((int)rand())
extern s32 fn_801ED3F4(void*);
extern void fn_801A8F08(s32, s32, s32, s32, s32, s32, void*);

void fn_80026768(EffectState* state)
{
    EffectData* data = &lbl_8023DEB0;
    ColorValues colors;
    EdgeValues edge;
    u32 packed[6];
    u8 alpha;
    u8 depth_alpha;
    u32 packed_alpha;
    s32 left;
    s16 quad_left;
    s16 quad_right;
    s16 quad_depth;
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;
    s32 bottom;
    s32 particle_origin;
    s32 particle_y_origin;
    s32 texture;
    s32 depth;
    s32 variant;
    s32 i;
    ParticlePoint* point;
    s16* age;
    s16* delay;
    s32 limit;
    u32 draw_color;
    u32 particle_color;
    u32* particle_colors;

    if (state == 0) {
        return;
    }
    if ((alpha = state->alpha) == 0) {
        return;
    }

    if (state->mode != 0) {
        alpha = (u8)(lbl_8064DF90 * alpha);
    }

    /* Narrow once before copying the color and edge tables. */
    packed_alpha = alpha;
    colors = lbl_80238C28;
    edge = lbl_80238C40;

    depth_alpha = state->mode != 0 ? state->alpha >> 2 : state->alpha;
    texture = state->mode != 0 ? -1 : -30360;
    depth = depth_alpha | 0xFFFF0A00;
    variant = state->variant;
    packed[0] = packed_alpha | 0x0A0A0A00;
    packed[1] = packed_alpha | 0x0A0A0A00;
    packed[2] = depth;
    packed[3] = depth;
    packed[4] = colors.words[variant * 2] | packed_alpha;
    packed[5] = colors.words[variant * 2 + 1] | packed_alpha;

    x0 = (s32)(lbl_8064DF98 * state->y);
    x1 = (s32)(lbl_8064DF98 * state->x);
    left = state->left + 6;
    /* Keep both fused operations: sharing a rounded product changes the edges. */
    particle_origin =
        (s32)(__fmadds(lbl_8064DF98, state->scale, lbl_8064DF94) + state->top);
    if (x0 < x1) {
        s32 swap = x0;
        x0 = x1;
        x1 = swap;
    }
    y0 = (s32)(lbl_8064DF9C + (61 - x0) * state->scale);
    y1 = (s32)(lbl_8064DF9C + (61 - x1) * state->scale);
    bottom = (s32)__fmadds(lbl_8064DF98, state->scale, lbl_8064DF9C);
    edge.half[1] = y0;
    edge.half[2] = y0;
    edge.half[3] = y1;
    edge.half[4] = y1;
    edge.half[5] = bottom;

    fn_801F1034();
    draw_color = lbl_8064C2A8;
    fn_801A852C(&draw_color, -1, 0, 0);
    fn_801ECF50(9);

    quad_left = left;
    quad_right = quad_left + 19;
    quad_depth = texture;
    for (i = 0; i < 6; i += 2) {
        s16 top = (s16)(state->top + edge.half[i]);
        s16 bot = (s16)(state->top + edge.half[i + 1]);
        u32 top_color = packed[i];
        u32 bottom_color = packed[i + 1];
        GXBegin(0x80, 5, 4);
        fn_80026754(quad_left, top, quad_depth);
        fn_80026DBC(top_color);
        fn_80026DAC(0, 0);
        fn_80026754(quad_right, top, quad_depth);
        fn_80026DBC(top_color);
        fn_80026DAC(0, 0);
        fn_80026754(quad_right, bot, quad_depth);
        fn_80026DBC(bottom_color);
        fn_80026DAC(0, 0);
        fn_80026754(quad_left, bot, quad_depth);
        fn_80026DBC(bottom_color);
        fn_80026DAC(0, 0);
        fn_80026740();
    }

    GXSetArray(13, data->resource, 4);
    particle_colors = data->color;
    ((u8*)&particle_colors[variant])[3] = state->alpha;
    particle_color = particle_colors[variant];
    /* Retail snapshots this origin before setting the particle color. */
    particle_y_origin = (s16)(state->top + edge.half[4]);
    age = data->age;
    age += variant * 5;
    fn_801A852C(&particle_color, 0, 9, 0x80000000);
    point = data->point;
    delay = data->delay;
    point += variant * 5;
    delay += variant * 5;
    limit = particle_origin - particle_y_origin;
    for (i = 0; i < 5; i++, point++, delay++, age++) {
        if (*age == 1) {
            lbl_8064C6E8++;
            if (lbl_8064C6E8 >= 20) {
                lbl_8064C6E8 = 0;
            }
        }
        if (*age >= 24) {
            point->y = limit + (rand() & 0x1F);
            point->x = (rand() & 7) + 2;
            *delay = (rand() & 3) + 5;
            *age = 0;
        }
        if (point->y <= limit) {
            fn_801A8F08((s16)(point->x + left),
                        (s16)(point->y + particle_y_origin),
                        (s16)(point->x + (*delay + left)),
                        (s16)(point->y + (*delay + particle_y_origin)),
                        texture, (u16)((*age >> 3) * 4), (void*)5);
        }
        if (point->y <= -3) {
            (*age)++;
        } else if (lbl_8064D5A8 % (10 - *delay) == 0) {
            point->y--;
        }
    }

    GXSetArray(13, data->resource, 4);
    if (state->mode != 0) {
        u32 color = lbl_8064DF88;
        u32 copy;
        ((u8*)&color)[3] = state->alpha;
        copy = color;
        fn_801A852C(&copy, 0, 0, 0x80000000);
        fn_801A8F08(state->left, state->top, (s16)(state->left + 31),
                    (s16)(state->top + 30), -1, 0, (void*)5);
        fn_801A8F08(state->left, (s16)(state->top + edge.half[5]),
                    (s16)(state->left + 31),
                    (s16)(state->top + edge.half[5] + 30), -1, 4, (void*)5);
    } else {
        u32 color;
        u32 copy;
        fn_801ED3F4(lbl_8064CD7C);
        color = lbl_8064DF8C;
        ((u8*)&color)[3] = state->alpha;
        copy = color;
        fn_801A85D4(&copy, 14, 15, 0x80000000);
        fn_801A8F08(state->left, state->top, (s16)(state->left + 31),
                    (s16)(state->top + 30), -30360, 0, (void*)5);
        fn_801A8F08(state->left, (s16)(state->top + edge.half[5]),
                    (s16)(state->left + 31),
                    (s16)(state->top + edge.half[5] + 30), -30360, 4, (void*)5);
    }
}
