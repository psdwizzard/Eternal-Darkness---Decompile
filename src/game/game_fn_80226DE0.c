/* GXSetDispCopySrc: select the source rectangle for a display copy. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x1E0];
    u32 cpDispSrc;
    u32 cpDispSize;
} GXData;

extern GXData *gx;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void GXSetDispCopySrc(u16 left, u16 top, u16 width, u16 height)
{
    gx->cpDispSrc = 0;
    SET_REG_FIELD(gx->cpDispSrc, 10, 0, left);
    SET_REG_FIELD(gx->cpDispSrc, 10, 10, top);
    SET_REG_FIELD(gx->cpDispSrc, 8, 24, 0x49);
    gx->cpDispSize = 0;
    SET_REG_FIELD(gx->cpDispSize, 10, 0, width - 1);
    SET_REG_FIELD(gx->cpDispSize, 10, 10, height - 1);
    SET_REG_FIELD(gx->cpDispSize, 8, 24, 0x4A);
}
