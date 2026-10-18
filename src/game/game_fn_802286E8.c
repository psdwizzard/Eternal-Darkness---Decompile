/* GXInitTexObjCI: initialise a color-indexed texture and select its TLUT. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXTexObj {
    u32 dummy[8];
} GXTexObj;

typedef struct __GXTexObjInt {
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
} __GXTexObjInt;

extern void GXInitTexObj(GXTexObj *obj, void *image_ptr, u16 width, u16 height,
                        u32 format, u32 wrap_s, u32 wrap_t, u8 mipmap);

void GXInitTexObjCI(GXTexObj *obj, void *image_ptr, u16 width, u16 height,
                 u32 format, u32 wrap_s, u32 wrap_t, u8 mipmap, u32 tlut_name)
{
    __GXTexObjInt *t = (__GXTexObjInt *)obj;

    GXInitTexObj(obj, image_ptr, width, height, format, wrap_s, wrap_t, mipmap);
    t->flags &= ~2;
    t->tlutName = tlut_name;
}
