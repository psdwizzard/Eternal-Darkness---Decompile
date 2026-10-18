typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef unsigned int u32;
typedef u32* Color;
typedef float f32;

#pragma use_lmw_stmw on

extern u32 lbl_8064C2A8;
extern const f32 lbl_8064DFA8;
extern const f32 lbl_8064DFAC;

extern void fn_801A8D38(int);
extern void fn_801A852C(Color, int, int, u32);
extern void fn_801F1034(void);
extern void GXBegin(s32, s32, s32);
extern void fn_80026754(s16, s16, s32);
extern void fn_80026DBC(u32);
extern void fn_80026DAC(s16, s16);
extern void fn_80026740(void);
extern void fn_801ECC4C(void);

void fn_80026DC8(s16 left, s32 top, s16 right, s32 bottom, f32 fraction,
                 u8 alpha)
{
    u32 draw_color;
    s16 x[4];
    u32 color[4] = {0xff000000, 0xffdc0000, 0xdcff0000, 0x00ff0000};
    s32 width;
    s32 clip;
    s32 count;
    s32 i;
    s16 y0;
    s16 y1;

    width = right - left;
    clip = left + (s32)(fraction * width);

    x[0] = left;
    x[1] = (s32)(left + lbl_8064DFA8 * width);
    x[2] = (s32)(left + lbl_8064DFAC * width);
    x[3] = right;

    for (i = 0; i < 4; i++) {
        color[i] |= alpha;
    }

    count = 3;
    for (i = 0; i < 4; i++) {
        if (x[i] > clip) {
            x[i] = clip;
            count = i;
            break;
        }
    }

    fn_801A8D38(9);
    draw_color = lbl_8064C2A8;
    fn_801A852C(&draw_color, -1, 0, 0);
    fn_801F1034();

    y0 = top;
    y1 = bottom;
    for (i = 0; i < count; i++) {
        GXBegin(0x80, 5, 4);
        fn_80026754(x[i], y0, -1);
        fn_80026DBC(color[i]);
        fn_80026DAC(0, 0);
        fn_80026754(x[i + 1], y0, -1);
        fn_80026DBC(color[i + 1]);
        fn_80026DAC(0, 0);
        fn_80026754(x[i + 1], y1, -1);
        fn_80026DBC(color[i + 1]);
        fn_80026DAC(0, 0);
        fn_80026754(x[i], y1, -1);
        fn_80026DBC(color[i]);
        fn_80026DAC(0, 0);
        fn_80026740();
    }

    fn_801ECC4C();
}
