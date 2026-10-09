typedef signed short s16;
typedef signed long s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef signed char s8;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

extern u8 lbl_802515D0[];
extern Color lbl_8064C2A8;
extern u8 lbl_8064CE50;
extern u8 lbl_8064CE51;
extern s8 lbl_8064CE52;
extern u8 lbl_8064CE53;
extern u8 lbl_8064CE54;
extern u8 lbl_8064CE55;
extern s32 lbl_8064CE5C;
extern s32 lbl_8064CE60;
extern u32 lbl_8064CE68;
extern float lbl_80650040;
extern float lbl_80650044;

extern int fn_801E8D34(u32);
extern void fn_80225F4C(s32, void*, s32);
extern void fn_801ECEC8(int, int, int);
extern void fn_801A852C(Color, int, int, u32);
extern void fn_801A85D4(Color, int, int, u32);
extern void fn_801A8F08(s16, s16, s16, s16, int, int, int);
extern void fn_801ED5F4(int, int, int, int, int, float);
extern void fn_801A8DE8(void*, s16, s16, s16, s16, s32, s32, s32);
extern void fn_801A8D38(int);

/* NonMatching (93.22%): retail saves r27-r31 with stmw/lmw, which needs
 * -use_lmw_stmw on (current flags emit _savegpr_27/_restgpr_27, +8 bytes).
 * The first fade block swaps r0/r3, and the alpha-scale float block
 * schedules the CE55 load and its stack conversion slots differently. */
void fn_8011C900(s16 x, s16 y0, s16 y1, Color* color, u8 low, u8 high)
{
    Color bg;
    Color fg;
    s16 bar_x;
    int level;
    int fade;
    float scale;

    if (lbl_8064CE68 == 0) {
        return;
    }

    fg = *color;
    fg.a = high;
    bg = lbl_8064C2A8;
    if (lbl_8064CE54 != 0) {
        fg.a = 0;
    }
    fade = lbl_8064CE54 ? (u8)(lbl_8064CE54 - 5) : 0;
    lbl_8064CE54 = fade;
    bg.a -= fade;
    if (lbl_8064CE54 == 0) {
        fade = lbl_8064CE53 ? (u8)(lbl_8064CE53 - 5) : 0;
        lbl_8064CE53 = fade;
        fg.a -= fade;
        lbl_8064CE52 = lbl_8064CE53 == 0;
    }
    if (lbl_8064CE52) {
        if (lbl_8064CE50 <= low || lbl_8064CE50 >= high) {
            lbl_8064CE51 = -lbl_8064CE51;
        }
        lbl_8064CE50 += lbl_8064CE51;
        fg.a = lbl_8064CE50;
    }

    scale = bg.a / lbl_80650040;
    color->a = lbl_8064CE55 + 40;
    color->a = scale * color->a;

    level = fn_801E8D34(lbl_8064CE68) * 237 / 127;
    bar_x = lbl_8064CE60 + 59 + level;
    fn_80225F4C(13, lbl_802515D0, 4);
    fn_801ECEC8(1, 7, 1);
    fn_801A852C(fg, 5, x, 0x80000000);
    fn_801A8F08(lbl_8064CE60 + 51, lbl_8064CE5C, lbl_8064CE60 + 403,
                lbl_8064CE5C + 174, -0x7698, 0, 5);
    fn_801A85D4(bg, y0, y1, 0x80000000);
    fn_801A8F08(lbl_8064CE60 + 68, lbl_8064CE5C + 13, lbl_8064CE60 + 396,
                lbl_8064CE5C + 159, -0x7698, 0, 5);
    fn_801ED5F4(1, 0x482, 2, 0, 0, lbl_80650044);
    fn_801A852C(*color, -1, -1, 0x80000000);
    fn_801A8DE8(lbl_802515D0, lbl_8064CE60 + 95, lbl_8064CE5C + 72,
                bar_x + 60, lbl_8064CE5C + 100, -1, 0, 5);
    fn_801ED5F4(0, 2, 1, 0, 0, lbl_80650044);
    fn_801ECEC8(1, 3, 1);
    fn_801A8D38(5);
}
