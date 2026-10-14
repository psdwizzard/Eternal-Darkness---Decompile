/* GXSetDstAlpha: configure the destination alpha override. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
    u8 pad4[0x1D4 - 4];
    u32 dstAlpha;
} GXData;
extern GXData *gx;

typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

void fn_8022A964(u8 enable, u8 alpha)
{
    gx->dstAlpha = (gx->dstAlpha & ~0xFFUL) | (u32)alpha;
    gx->dstAlpha = (gx->dstAlpha & ~(1UL << 8)) | ((u32)enable << 8);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = gx->dstAlpha;
    gx->bpSentNot = 0;
}
