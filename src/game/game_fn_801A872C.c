typedef signed short s16;
typedef signed long s32;
typedef unsigned long u32;

extern void fn_801A852C(u32*, s32, s32, u32);
extern void fn_801ECF50(u32);
extern void fn_80226AB4(u32, u32, u32);
extern void fn_801A9454(s16, s16, s16);
extern void fn_801A9450(void);

void fn_801A872C(s32 x, s32 y, s32 width, s32 height, s32 depth,
                 s32 inset, const u32* color)
{
    s16 sdepth;
    s16 sy;
    s32 top;
    s16 sinset;
    s16 sx;
    s32 bottomInset;
    s32 rightInset;
    s32 left;
    s16 right;
    s16 bottom;
    u32 copy;

    left = (s16)x;
    right = left + width;
    top = (s16)y;
    bottom = top + height;
    copy = *color;
    fn_801A852C(&copy, 0, -1, 0x80000000);
    fn_801ECF50(4);
    fn_80226AB4(0x80, 5, 0x10);
    sx = x;
    sy = y;
    sdepth = depth;
    fn_801A9454(sx, sy, sdepth);
    fn_801A9454(right, sy, sdepth);
    sinset = inset;
    top += sinset;
    fn_801A9454(right, top, sdepth);
    fn_801A9454(sx, top, sdepth);
    rightInset = right - sinset;
    fn_801A9454(rightInset, top, sdepth);
    fn_801A9454(right, top, sdepth);
    bottomInset = bottom - sinset;
    fn_801A9454(right, bottomInset, sdepth);
    fn_801A9454(rightInset, bottomInset, sdepth);
    fn_801A9454(sx, bottomInset, sdepth);
    fn_801A9454(right, bottomInset, sdepth);
    fn_801A9454(right, bottom, sdepth);
    fn_801A9454(sx, bottom, sdepth);
    fn_801A9454(sx, top, sdepth);
    left += sinset;
    fn_801A9454(left, top, sdepth);
    fn_801A9454(left, bottomInset, sdepth);
    fn_801A9454(sx, bottomInset, sdepth);
    fn_801A9450();
}
