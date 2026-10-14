/* GXGetTexObj: retrieve the image and parameters of a texture object. */
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

void fn_802288C4(void *obj, void **image, u16 *width, u16 *height,
                 u32 *format, u32 *wrap_s, u32 *wrap_t, u8 *mipmap)
{
    GXTexObjInt *t = (GXTexObjInt *)obj;

    *image = (void *)((t->image3 & 0x1FFFFF) << 5);
    *width = (t->image0 & 0x3FF) + 1;
    *height = ((t->image0 >> 10) & 0x3FF) + 1;
    *format = t->fmt;
    *wrap_s = t->mode0 & 3;
    *wrap_t = (t->mode0 >> 2) & 3;
    *mipmap = (t->flags & 1) == 1;
}
