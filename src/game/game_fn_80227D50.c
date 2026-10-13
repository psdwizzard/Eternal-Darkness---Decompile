/* GXSetChanAmbColor: set the ambient RGB and/or alpha of a lighting channel. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;

typedef struct GXData {
    u16 pad0;
    u16 bpSentNot;
    u8 pad4[0xA4];
    u32 ambColor[2];
} GXData;
extern GXData *gx;

typedef enum {
    GX_COLOR0, GX_COLOR1, GX_ALPHA0, GX_ALPHA1,
    GX_COLOR0A0, GX_COLOR1A1
} GXChannelID;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

typedef union GXWGPipe {
    u8 u8_data;
    u32 u32_data;
} GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

void fn_80227D50(GXChannelID chan, GXColor color)
{
    u32 reg;
    u32 index;

    switch (chan) {
    case GX_COLOR0:
        index = 0;
        reg = gx->ambColor[0] & 0xFF;
        SET_REG_FIELD(reg, 8, 8, color.b);
        SET_REG_FIELD(reg, 8, 16, color.g);
        SET_REG_FIELD(reg, 8, 24, color.r);
        break;
    case GX_COLOR1:
        index = 1;
        reg = gx->ambColor[1] & 0xFF;
        SET_REG_FIELD(reg, 8, 8, color.b);
        SET_REG_FIELD(reg, 8, 16, color.g);
        SET_REG_FIELD(reg, 8, 24, color.r);
        break;
    case GX_ALPHA0:
        index = 0;
        reg = gx->ambColor[0];
        SET_REG_FIELD(reg, 8, 0, color.a);
        break;
    case GX_ALPHA1:
        index = 1;
        reg = gx->ambColor[1];
        SET_REG_FIELD(reg, 8, 0, color.a);
        break;
    case GX_COLOR0A0:
        index = 0;
        reg = color.a;
        SET_REG_FIELD(reg, 8, 8, color.b);
        SET_REG_FIELD(reg, 8, 16, color.g);
        SET_REG_FIELD(reg, 8, 24, color.r);
        break;
    case GX_COLOR1A1:
        index = 1;
        reg = color.a;
        SET_REG_FIELD(reg, 8, 8, color.b);
        SET_REG_FIELD(reg, 8, 16, color.g);
        SET_REG_FIELD(reg, 8, 24, color.r);
        break;
    default:
        return;
    }

    GXWGFifo.u8_data = 0x10;
    GXWGFifo.u32_data = 0x100A + index;
    GXWGFifo.u32_data = reg;
    gx->bpSentNot = 1;
    gx->ambColor[index] = reg;
}
