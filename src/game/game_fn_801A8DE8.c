typedef signed short s16;
typedef signed long s32;
typedef unsigned short u16;

extern void fn_801ECF50(s32);
extern void GXSetArray(s32, void*, s32);
extern void GXBegin(s32, void*, s32);
extern void fn_801A9454(s16, s16, s16);
extern void fn_801A9468(u16);
extern void fn_801A9450(void);

void fn_801A8DE8(void* image, s32 x0, s32 y0, s32 x1, s32 y1,
                 s32 depth, s32 index, void* palette)
{
    s16 sdepth;
    s16 sy0;
    u16 uindex;
    s16 sx1;
    s16 sx0;
    s16 sy1;

    fn_801ECF50(6);
    GXSetArray(13, image, 4);
    GXBegin(0x80, palette, 4);

    sx0 = x0;
    sy0 = y0;
    sdepth = depth;
    fn_801A9454(sx0, sy0, sdepth);
    uindex = index;
    fn_801A9468(uindex);
    sx1 = x1;
    fn_801A9454(sx1, sy0, sdepth);
    fn_801A9468(uindex + 1);
    sy1 = y1;
    fn_801A9454(sx1, sy1, sdepth);
    fn_801A9468(uindex + 2);
    fn_801A9454(sx0, sy1, sdepth);
    fn_801A9468(uindex + 3);
    fn_801A9450();
}
