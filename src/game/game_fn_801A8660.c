typedef signed short s16;
typedef signed long s32;
typedef unsigned long u32;

extern void fn_801A852C(u32*, s32, s32, u32);
extern void fn_801ECF50(u32);
extern void GXBegin(u32, u32, u32);
extern void fn_801A9454(s32, s32, s32);
extern void fn_801A9450(void);

void fn_801A8660(s32 x, s32 y, s32 width, s32 height, s32 depth, const u32* color)
{
    u32 copy = *color;
    fn_801A852C(&copy, 0, -1, 0x80000000);
    fn_801ECF50(4);
    GXBegin(0x80, 5, 4);

    fn_801A9454((s16)x, (s16)y, (s16)depth);
    fn_801A9454((s16)(x + width), (s16)y, (s16)depth);
    fn_801A9454((s16)(x + width), (s16)(y + height), (s16)depth);
    fn_801A9454((s16)x, (s16)(y + height), (s16)depth);
    fn_801A9450();
}
