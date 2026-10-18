/* GXSetArray: set the CP array base and stride, and cache indexed matrix arrays. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x88];
    u32 arrayBase[4];
    u32 arrayStride[4];
} GXData;
extern GXData *gx;

#define GX_WRITE_U8(v) (*(volatile u8 *)0xCC008000 = (u8)(v))
#define GX_WRITE_U32(v) (*(volatile u32 *)0xCC008000 = (u32)(v))

void GXSetArray(int attr, const void *base, u8 stride)
{
    int array;
    long index;
    u32 physicalBase;
    u32 arrayStride;

    if (attr == 25) {
        attr = 10;
    }
    array = attr - 9;
    physicalBase = (u32)base & 0x3FFFFFFF;
    GX_WRITE_U8(8);
    GX_WRITE_U8(array | 0xA0);
    GX_WRITE_U32(physicalBase);
    index = array - 12;
    if (index >= 0 && index < 4) {
        gx->arrayBase[index] = physicalBase;
    }

    GX_WRITE_U8(8);
    GX_WRITE_U8(array | 0xB0);
    arrayStride = stride;
    GX_WRITE_U32(arrayStride);
    index = array - 12;
    if (index >= 0 && index < 4) {
        gx->arrayStride[index] = arrayStride;
    }
}
