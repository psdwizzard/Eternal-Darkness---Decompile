/* GXSetTevSwapMode: select raster and texture swap tables for a TEV stage. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
    u8 reserved4[0x170 - 4];
    u32 tevAlphaEnv[16];
} GXData;

extern GXData *gx;
typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

void fn_80229F4C(int stage, int rasterSwap, int textureSwap)
{
    u32 *reg = &gx->tevAlphaEnv[stage];

    *reg = (*reg & ~3UL) | (u32)rasterSwap;
    *reg = (*reg & ~12UL) | ((u32)textureSwap << 2);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = *reg;
    gx->bpSentNot = 0;
}
