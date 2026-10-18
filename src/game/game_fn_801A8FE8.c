typedef signed long s32;
typedef unsigned short u16;

extern void fn_801ECF50(s32);
extern void GXSetArray(s32, void*, s32);
extern void GXBegin(s32, void*, s32);
extern void fn_801A9474(u16);
extern void fn_801A9468(u16);
extern void fn_801A9450(void);

void fn_801A8FE8(void* image, void* mask, s32 index, s32 coordinate,
                 void* palette)
{
    u16 ucoordinate;
    u16 uindex;

    fn_801ECF50(5);
    GXSetArray(9, mask, 6);
    GXSetArray(13, image, 4);
    GXBegin(0x80, palette, 4);
    ucoordinate = coordinate;
    fn_801A9474(ucoordinate);
    uindex = index;
    fn_801A9468(uindex);
    fn_801A9474(ucoordinate + 1);
    fn_801A9468(uindex + 1);
    fn_801A9474(ucoordinate + 2);
    fn_801A9468(uindex + 2);
    fn_801A9474(ucoordinate + 3);
    fn_801A9468(uindex + 3);
    fn_801A9450();
}
