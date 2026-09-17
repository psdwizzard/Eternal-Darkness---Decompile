typedef signed short s16;
typedef unsigned int u32;

typedef struct Color {
    u32 value;
} Color;

extern float lbl_80651278;
extern Color lbl_80651270;
extern Color lbl_80651274;
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

/* NonMatching: honest reconstruction of all sixteen panel vertices. Retail
 * retains both the raw fctiwz result for the negative screen-space extents and
 * its signed-16-bit form for texture bounds and positive screen-space extents. */
void fn_801E4314(s16 x, s16 y, s16 width, s16 height, float scale, int dark)
{
    int raw_depth = (int)(lbl_80651278 * scale);
    s16 depth = raw_depth;
    s16 left = ((width >> 1) + depth) * 512 / 17;
    s16 top = ((height >> 1) + depth) * 512 / 17;
    s16 right = (17 - ((height >> 1) + depth)) * 512 / 17;
    s16 bottom = (17 - ((width >> 1) + depth)) * 512 / 17;
    s16 cx = x + (width >> 1);
    s16 cy = y + (height >> 1);
    Color color;
    Color dark_color;
    Color light_color;
    Color* color_copy;
    int left_x;
    int top_y;
    s16 right_x;
    s16 bottom_y;

    if (dark) {
        dark_color = lbl_80651270;
        color_copy = &dark_color;
    } else {
        light_color = lbl_80651274;
        color_copy = &light_color;
    }
    color = *color_copy;
    top_y = y - raw_depth;
    left_x = x - raw_depth;

    fn_801ECF50(9);
    fn_801ED3F4(lbl_8064D570);
    fn_801A852C(color, 0, 0, 0x80000000);
    lbl_8064C31C = -1;
    lbl_8064C320 = -1;
    fn_80226AB4(0x80, 5, 0x10);

    left_x = (s16)left_x;
    fn_801E4198(left_x, cy, -1); fn_801E46F8(0); fn_801E46E8(30, right);
    top_y = (s16)top_y;
    fn_801E4198(left_x, top_y, -1); fn_801E46F8(0); fn_801E46E8(30, 481);
    fn_801E4198(cx, top_y, -1); fn_801E46F8(0); fn_801E46E8(left, 481);
    fn_801E4198(cx, cy, -1); fn_801E46F8(0); fn_801E46E8(left, right);
    fn_801E4198(cx, cy, -1); fn_801E46F8(0); fn_801E46E8(top, bottom);
    fn_801E4198(cx, top_y, -1); fn_801E46F8(0); fn_801E46E8(30, bottom);

    right_x = x + depth + width;
    fn_801E4198(right_x, top_y, -1); fn_801E46F8(0); fn_801E46E8(30, 481);
    fn_801E4198(right_x, cy, -1); fn_801E46F8(0); fn_801E46E8(top, 481);
    bottom_y = y + depth + height;
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
