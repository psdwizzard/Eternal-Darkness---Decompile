/* GXSetTexCopyDst: configure the format and tile stride of an EFB copy. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x1F8];
    u32 cpTexStride;
    u32 cpTex;
    u8 copyIsDepth;
} GXData;

extern GXData *gx;
extern void fn_802283AC(int format, u16 width, u16 height,
                        u32 *tilesX, u32 *tilesY, u32 *planes);

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void fn_80226FA4(u16 width, u16 height, int format, u8 mipmap)
{
    u32 tilesX;
    u32 tilesY;
    u32 planes;
    u32 reg;
    u32 copyFormat = format & 0xF;

    gx->copyIsDepth = 0;
    if (format == 0x13) {
        copyFormat = 0xB;
    }
    switch (format) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 0x26:
        SET_REG_FIELD(gx->cpTex, 2, 15, 3);
        break;
    default:
        SET_REG_FIELD(gx->cpTex, 2, 15, 2);
        break;
    }
    gx->copyIsDepth = (format & 0x10) == 0x10;
    SET_REG_FIELD(gx->cpTex, 1, 3, (copyFormat & 8) >> 3);
    copyFormat &= 7;
    fn_802283AC(format, width, height, &tilesX, &tilesY, &planes);
    gx->cpTexStride = 0;
    SET_REG_FIELD(gx->cpTexStride, 10, 0, tilesX * planes);
    SET_REG_FIELD(gx->cpTexStride, 8, 24, 0x4D);
    SET_REG_FIELD(gx->cpTex, 1, 9, mipmap);
    SET_REG_FIELD(gx->cpTex, 3, 4, copyFormat);
}
