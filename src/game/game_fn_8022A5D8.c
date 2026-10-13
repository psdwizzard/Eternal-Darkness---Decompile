/* GXSetBlendMode: configure blending, subtraction, and logic operations. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
    u8 pad4[0x1D0 - 4];
    u32 blendMode;
} GXData;
extern GXData *gx;

typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define SET_FIELD(reg, width, shift, value) \
    ((reg) = ((reg) & ~(((1UL << (width)) - 1) << (shift))) | ((u32)(value) << (shift)))

void fn_8022A5D8(int type, int srcFactor, int dstFactor, int logicOp)
{
    SET_FIELD(gx->blendMode, 1, 0, type == 1 || type == 3);
    SET_FIELD(gx->blendMode, 1, 11, type == 3);
    SET_FIELD(gx->blendMode, 1, 1, type == 2);
    SET_FIELD(gx->blendMode, 4, 12, logicOp);
    SET_FIELD(gx->blendMode, 3, 8, srcFactor);
    SET_FIELD(gx->blendMode, 3, 5, dstFactor);
    SET_FIELD(gx->blendMode, 8, 24, 0x41);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = gx->blendMode;
    gx->bpSentNot = 0;
}
