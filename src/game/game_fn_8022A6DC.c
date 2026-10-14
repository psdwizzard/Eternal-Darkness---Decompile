/* GXSetColorUpdate: enable or disable color buffer writes. */
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

void fn_8022A6DC(u8 updateEnable)
{
    gx->blendMode = (gx->blendMode & ~(1UL << 3)) | ((u32)updateEnable << 3);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = gx->blendMode;
    gx->bpSentNot = 0;
}
