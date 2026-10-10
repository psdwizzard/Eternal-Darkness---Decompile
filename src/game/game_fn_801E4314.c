typedef signed short s16;
typedef unsigned int u32;

typedef struct Color {
    u32 value;
} Color;

extern const float lbl_80651278;
extern const Color lbl_80651270;
extern const Color lbl_80651274;
extern int lbl_8064D570;
extern int lbl_8064D580;
extern int lbl_806333C8[];
extern int lbl_8064C31C;
extern int lbl_8064C320;

extern void fn_801ECF50(int);
extern void fn_801ED3F4(int);
extern void fn_801A852C(Color, int, int, u32);
extern void fn_80226AB4(int, int, int);
extern void fn_801E4198(s16, s16, s16);
extern void fn_801E4188(void);
extern void fn_801E46E8(s16, s16);
extern void fn_801E46F8(int);

/* NonMatching (99.39%): instruction stream and schedule match retail; only
 * register assignment differs. Retail colours sx/sw/sy/sh as r30/r29/r28/r27
 * (ours sx r29, sw r27, sy r30, sh r28) and swaps left_x/top_y (r20/r19). */
void fn_801E4314(int x, int y, int width, int height, float scale, int dark)
{
    int raw_depth;
    s16 depth;
    s16 sh;
    s16 sy;
    s16 sw;
    s16 sx;
    int half_w;
    int half_h;
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
    s16 cx;
    s16 cy;
    int left_x;
    int top_y;
    s16 right_x;
    s16 bottom_y;
    Color color;
    Color dark_color;
    Color light_color;
    Color* color_copy;

    raw_depth = lbl_80651278 * scale;
    depth = raw_depth;
    sh = height;
    sy = y;
    sw = width;
    sx = x;
    half_w = sw >> 1;
    half_h = sh >> 1;
    cx = half_w + sx;
    cy = half_h + sy;
    left = (half_w + depth) * 512 / 17;
    top = (half_h + depth) * 512 / 17;
    right = (17 - (half_h + depth)) * 512 / 17;
    bottom = (17 - (half_w + depth)) * 512 / 17;

    if (dark) {
        dark_color = lbl_80651270;
        color_copy = &dark_color;
    } else {
        light_color = lbl_80651274;
        color_copy = &light_color;
    }
    color = *color_copy;
    left_x = x - raw_depth;
    top_y = y - raw_depth;

    fn_801ECF50(9);
    fn_801ED3F4(lbl_8064D570);
    fn_801A852C(color, 0, 0, 0x80000000);
    lbl_8064C31C = -1;
    lbl_8064C320 = -1;
    fn_80226AB4(0x80, 5, 0x10);

    /* the offsets are kept as ints across the setup calls and narrowed in place */
    left_x = (s16)left_x;
    fn_801E4198(left_x, cy, -1); fn_801E46F8(0); fn_801E46E8(30, right);
    top_y = (s16)top_y;
    fn_801E4198(left_x, top_y, -1); fn_801E46F8(0); fn_801E46E8(30, 481);
    fn_801E4198(cx, top_y, -1); fn_801E46F8(0); fn_801E46E8(left, 481);
    fn_801E4198(cx, cy, -1); fn_801E46F8(0); fn_801E46E8(left, right);
    fn_801E4198(cx, cy, -1); fn_801E46F8(0); fn_801E46E8(top, bottom);
    fn_801E4198(cx, top_y, -1); fn_801E46F8(0); fn_801E46E8(30, bottom);

    right_x = sw + depth + sx;
    fn_801E4198(right_x, top_y, -1); fn_801E46F8(0); fn_801E46E8(30, 481);
    fn_801E4198(right_x, cy, -1); fn_801E46F8(0); fn_801E46E8(top, 481);
    bottom_y = sy + depth + sh;
    fn_801E4198(cx, bottom_y, -1); fn_801E46F8(0); fn_801E46E8(left, 481);
    fn_801E4198(cx, cy, -1); fn_801E46F8(0); fn_801E46E8(left, right);
    fn_801E4198(right_x, cy, -1); fn_801E46F8(0); fn_801E46E8(30, right);
    fn_801E4198(right_x, bottom_y, -1); fn_801E46F8(0); fn_801E46E8(30, 481);
    fn_801E4198(left_x, bottom_y, -1); fn_801E46F8(0); fn_801E46E8(30, 481);
    fn_801E4198(left_x, cy, -1); fn_801E46F8(0); fn_801E46E8(top, 481);
    fn_801E4198(cx, cy, -1); fn_801E46F8(0); fn_801E46E8(top, bottom);
    fn_801E4198(cx, bottom_y, -1); fn_801E46F8(0); fn_801E46E8(30, bottom);

    fn_801E4188();
    fn_801ED3F4(lbl_806333C8[lbl_8064D580]);
}
