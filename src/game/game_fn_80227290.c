/* GXSetCopyClear: set the color and depth used when clearing the EFB. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;

typedef struct GXData {
    u16 vNumNot;
    u16 bpSentNot;
} GXData;
extern GXData *gx;

typedef union {
    u8 u8;
    u32 u32;
} PPCWGPipe;
volatile PPCWGPipe GXWGFifo : 0xCC008000;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))
#define GX_WRITE_RAS_REG(v) \
    do { GXWGFifo.u8 = 0x61; GXWGFifo.u32 = (v); } while (0)

void fn_80227290(GXColor color, u32 depth)
{
    u32 reg;

    reg = 0;
    SET_REG_FIELD(reg, 8, 0, color.r);
    SET_REG_FIELD(reg, 8, 8, color.a);
    SET_REG_FIELD(reg, 8, 24, 0x4F);
    GX_WRITE_RAS_REG(reg);

    reg = 0;
    SET_REG_FIELD(reg, 8, 0, color.b);
    SET_REG_FIELD(reg, 8, 8, color.g);
    SET_REG_FIELD(reg, 8, 24, 0x50);
    GX_WRITE_RAS_REG(reg);

    reg = 0;
    SET_REG_FIELD(reg, 24, 0, depth);
    SET_REG_FIELD(reg, 8, 24, 0x51);
    GX_WRITE_RAS_REG(reg);
    gx->bpSentNot = 0;
}
