typedef signed short s16;
typedef signed long s32;
typedef unsigned long u32;
typedef unsigned char u8;
typedef signed char s8;

typedef union Color {
    u32 word;
    struct {
        u8 r, g, b, a;
    } rgba;
} Color;

typedef struct RangeControl {
    int minimum, maximum, window, value;
} RangeControl;

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
extern RangeControl* lbl_8064CE68;
extern float lbl_80650040;
extern float lbl_80650044;

extern int fn_801E8D34(RangeControl*);
extern void fn_80225F4C(s32, void*, s32);
extern void fn_801ECEC8(u8, int, u8);
extern void fn_801A852C(u32*, int, int, u32);
extern void fn_801A85D4(u32*, int, int, u32);
extern void fn_801A8F08(s16, s16, s16, s16, int, int, int);
extern void fn_801ED5F4(int, int, s16, float*, float (*)[4], float);
extern void fn_801A8DE8(void*, s16, s16, s16, s16, s32, s32, s32);
extern void fn_801A8D38(int);

/* The fixed compiler settings use register-save helpers instead of the retail
 * stmw/lmw pair. The remaining body differences are the conversion-constant
 * relocation and the register used for the input color's alpha accesses. */
void fn_8011C900(register s16 input_x, register s16 input_y0,
                 register s16 input_y1, register Color* __restrict input_color,
                 u8 low, u8 high)
{
    register s16 bar_x;
    register Color* __restrict color;
    register s16 y1;
    register s16 y0;
    register s16 x;
    Color bg;
    Color fg;
    Color fg_copy;
    Color bg_copy;
    Color bar_color;

    int level;
    int fade;

    /* ASM: mr preserves the four arguments in retail order before the state
     * load; equivalent C assignments are coalesced and rescheduled by MWCC. */
    asm {
        mr x, input_x
        mr y0, input_y0
        mr y1, input_y1
        mr color, input_color
    }
    if (lbl_8064CE68 == 0) {
        return;
    }

    fg = *color;
    fg.rgba.a = high;
    bg = lbl_8064C2A8;
    if (lbl_8064CE54 != 0) {
        fg.rgba.a = 0;
    }
    fade = lbl_8064CE54 ? (u8)(lbl_8064CE54 - 5) : 0;
    bg.rgba.a -= fade;
    lbl_8064CE54 = fade;
    if (lbl_8064CE54 == 0) {
        fade = lbl_8064CE53 ? (u8)(lbl_8064CE53 - 5) : 0;
        lbl_8064CE53 = fade;
        fg.rgba.a -= fade;
        lbl_8064CE52 = lbl_8064CE53 == 0;
    }
    if (lbl_8064CE52) {
        if (lbl_8064CE50 <= low || lbl_8064CE50 >= high) {
            lbl_8064CE51 = -lbl_8064CE51;
        }
        lbl_8064CE50 += lbl_8064CE51;
        fg.rgba.a = lbl_8064CE50;
    }

    input_color->rgba.a = lbl_8064CE55 + 40;
    input_color->rgba.a *= bg.rgba.a / lbl_80650040;

    level = fn_801E8D34(lbl_8064CE68) * 237 / 127;
    bar_x = lbl_8064CE60 + 59 + level;
    fn_80225F4C(13, lbl_802515D0, 4);
    fn_801ECEC8(1, 7, 1);
    fg_copy = fg;
    fn_801A852C(&fg_copy.word, 5, x, 0x80000000);
    fn_801A8F08(lbl_8064CE60 + 51, lbl_8064CE5C, lbl_8064CE60 + 403,
                lbl_8064CE5C + 174, -0x7698, 0, 5);
    bg_copy = bg;
    fn_801A85D4(&bg_copy.word, y0, y1, 0x80000000);
    fn_801A8F08(lbl_8064CE60 + 68, lbl_8064CE5C + 13, lbl_8064CE60 + 396,
                lbl_8064CE5C + 159, -0x7698, 0, 5);
    fn_801ED5F4(1, 0x482, 2, 0, 0, lbl_80650044);
    bar_color = *color;
    fn_801A852C(&bar_color.word, -1, -1, 0x80000000);
    fn_801A8DE8(lbl_802515D0, lbl_8064CE60 + 95, lbl_8064CE5C + 72,
                bar_x + 60, lbl_8064CE5C + 100, -1, 0, 5);
    fn_801ED5F4(0, 2, 1, 0, 0, lbl_80650044);
    fn_801ECEC8(1, 3, 1);
    fn_801A8D38(5);
}
