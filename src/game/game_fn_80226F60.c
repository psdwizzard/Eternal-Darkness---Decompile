/* GXSetDispCopyDst: configure the destination stride of a display copy. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x1E8];
    u32 cpDispStride;
} GXData;

extern GXData *gx;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void GXSetDispCopyDst(u16 width, u16 height)
{
    u16 stride = width * 2;

    gx->cpDispStride = 0;
    SET_REG_FIELD(gx->cpDispStride, 10, 0, stride >> 5);
    SET_REG_FIELD(gx->cpDispStride, 8, 24, 0x4D);
}
