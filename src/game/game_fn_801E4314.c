typedef signed short s16;
typedef unsigned int u32;

extern float lbl_80651278;
extern u32 lbl_80651270;
extern u32 lbl_80651274;
extern int lbl_8064D570;
extern int lbl_8064D580;
extern int lbl_806333C8[];
extern int lbl_8064C31C;
extern int lbl_8064C320;

extern void fn_801ECF50(int);
extern void fn_801ED3F4(int);
extern void fn_801A852C(u32*, int, int, u32);
extern void fn_80226AB4(int, int, int);
extern void fn_801E4198(s16, s16, s16);
extern void fn_801E4188(void);
extern void fn_801E46E8(s16, s16);
extern void fn_801E46F8(int);

void fn_801E4314(s16 x, s16 y, s16 width, s16 height, float scale, int dark)
{
    s16 cx = x + width / 2;
    s16 cy = y + height / 2;
    int depth = (int)(lbl_80651278 * scale);
    s16 left = (x + depth) * 512 / 17;
    s16 top = (y + depth) * 512 / 17;
    s16 right = (17 - (x + depth)) * 512 / 17;
    s16 bottom = (17 - (y + depth)) * 512 / 17;
    u32 color;
    u32 color_copy;
    s16 dx;
    s16 dy;

    if (dark) {
        color_copy = lbl_80651270;
    } else {
        color_copy = lbl_80651274;
    }
    color = color_copy;
    dx = x - depth;
    dy = y - depth;

    fn_801ECF50(9);
    fn_801ED3F4(lbl_8064D570);
    fn_801A852C(&color, 0, 0, 0x80000000);
    lbl_8064C31C = -1;
    lbl_8064C320 = -1;
    fn_80226AB4(0x80, 5, 0x10);

    fn_801E4198(dx, cy, -1); fn_801E46F8(0); fn_801E46E8(30, right);
    fn_801E4198(dx, dy, -1); fn_801E46F8(0); fn_801E46E8(30, 481);
    fn_801E4198(cx, dy, -1); fn_801E46F8(0); fn_801E46E8(left, 481);
    fn_801E4198(cx, cy, -1); fn_801E46F8(0); fn_801E46E8(left, right);
    fn_801E4198(cx, cy, -1); fn_801E46F8(0); fn_801E46E8(top, bottom);
    fn_801E4198(cx, dy, -1); fn_801E46F8(0); fn_801E46E8(30, bottom);

    dx = x + depth + width;
    fn_801E4198(dx, dy, -1); fn_801E46F8(0); fn_801E46E8(30, 481);
    fn_801E4198(dx, cy, -1); fn_801E46F8(0); fn_801E46E8(top, 481);
    dy = y + depth + height;
    fn_801E4198(cx, dy, -1); fn_801E46F8(0); fn_801E46E8(left, 481);
    fn_801E4198(cx, cy, -1); fn_801E46F8(0); fn_801E46E8(left, right);
    fn_801E4198(dx, cy, -1); fn_801E46F8(0); fn_801E46E8(30, right);
    fn_801E4198(dx, dy, -1); fn_801E46F8(0); fn_801E46E8(30, 481);
    fn_801E4198(cx, dy, -1); fn_801E46F8(0); fn_801E46E8(top, 481);
    fn_801E4198(cx, cy, -1); fn_801E46F8(0); fn_801E46E8(top, bottom);
    fn_801E4198(cx, dy, -1); fn_801E46F8(0); fn_801E46E8(30, bottom);

    fn_801E4188();
    fn_801ED3F4(lbl_806333C8[lbl_8064D580]);
}
