/* GXGetTexObjWidth: retrieve the texture width stored as width minus one. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXTexObjInt {
    u32 mode0;
    u32 mode1;
    u32 image0;
    u32 image3;
    void *userData;
    u32 fmt;
    u32 tlutName;
    u16 loadCnt;
    u8 loadFmt;
    u8 flags;
} GXTexObjInt;

u16 fn_8022892C(const GXTexObjInt *obj)
{
    return (obj->image0 & 0x3FF) + 1;
}
