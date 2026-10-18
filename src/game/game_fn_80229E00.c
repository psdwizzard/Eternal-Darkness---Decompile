/* GXSetTevKColor: load a constant color into the TEV register bank. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
} GXData;
extern GXData *gx;

typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define SET_FIELD(reg, width, shift, value) \
    ((reg) = ((reg) & ~(((1U << (width)) - 1) << (shift))) | ((u32)(value) << (shift)))

void GXSetTevKColor(int id, GXColor color)
{
    u32 regRA, regBG;

    regRA = 0;
    SET_FIELD(regRA, 8, 0, color.r);
    SET_FIELD(regRA, 8, 12, color.a);
    SET_FIELD(regRA, 4, 20, 8);
    SET_FIELD(regRA, 8, 24, 0xE0 + id * 2);

    regBG = 0;
    SET_FIELD(regBG, 8, 0, color.b);
    SET_FIELD(regBG, 8, 12, color.g);
    SET_FIELD(regBG, 4, 20, 8);
    SET_FIELD(regBG, 8, 24, 0xE1 + id * 2);

    GXWGFifo.byte = 0x61;
    GXWGFifo.word = regRA;
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = regBG;
    gx->bpSentNot = 0;
}
