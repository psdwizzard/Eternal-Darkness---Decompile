/* GXSetDither: configure dithering in the blend-mode register. */
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

void fn_8022A924(u8 enable)
{
    gx->blendMode = (gx->blendMode & ~(1UL << 2)) | ((u32)enable << 2);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = gx->blendMode;
    gx->bpSentNot = 0;
}
