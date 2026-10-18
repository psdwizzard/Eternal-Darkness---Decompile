/* GXSetTexCopySrc: select the source rectangle for a texture copy. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x1F0];
    u32 cpTexSrc;
    u32 cpTexSize;
} GXData;

extern GXData *gx;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void GXSetTexCopySrc(u16 left, u16 top, u16 width, u16 height)
{
    gx->cpTexSrc = 0;
    SET_REG_FIELD(gx->cpTexSrc, 10, 0, left);
    SET_REG_FIELD(gx->cpTexSrc, 10, 10, top);
    SET_REG_FIELD(gx->cpTexSrc, 8, 24, 0x49);
    gx->cpTexSize = 0;
    SET_REG_FIELD(gx->cpTexSize, 10, 0, width - 1);
    SET_REG_FIELD(gx->cpTexSize, 10, 10, height - 1);
    SET_REG_FIELD(gx->cpTexSize, 8, 24, 0x4A);
}
