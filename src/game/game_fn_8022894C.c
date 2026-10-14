/* GXGetTexObjFmt: retrieve the texture object's format. */
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

u32 fn_8022894C(const GXTexObjInt *obj)
{
    return obj->fmt;
}
