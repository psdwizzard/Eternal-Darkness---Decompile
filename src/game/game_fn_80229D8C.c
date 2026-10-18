/* Set a TEV color register from an 8-bit RGBA color (GXSetTevColor). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
} GXData;
extern GXData *gx;

typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;

typedef union GXWGPipe { u8 u8; u32 u32; float f32; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define GX_WRITE_U8(v) (GXWGFifo.u8 = (u8)(v))
#define GX_WRITE_U32(v) (GXWGFifo.u32 = (u32)(v))
#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void GXSetTevColor(int id, GXColor color)
{
    u32 regRA;
    u32 regBG;

    regRA = 0;
    SET_REG_FIELD(regRA, 11, 0, color.r);
    SET_REG_FIELD(regRA, 11, 12, color.a);
    SET_REG_FIELD(regRA, 8, 24, 0xE0 + id * 2);

    regBG = 0;
    SET_REG_FIELD(regBG, 11, 0, color.b);
    SET_REG_FIELD(regBG, 11, 12, color.g);
    SET_REG_FIELD(regBG, 8, 24, 0xE1 + id * 2);

    GX_WRITE_U8(0x61);
    GX_WRITE_U32(regRA);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(regBG);
    /* The BG register is written three times to work around a hardware latch bug. */
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(regBG);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(regBG);
    gx->bpSentNot = 0;
}
