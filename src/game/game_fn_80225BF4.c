/* __GXSetVAT: flush dirty vertex attribute tables (VAT A/B/C) to the CP. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x1C];
    u32 vatA[8];
    u32 vatB[8];
    u32 vatC[8];
    u8 pad7C[0x4F2 - 0x7C];
    u8 dirtyVAT;
} GXData;
extern GXData *gx;

typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

void __GXSetVAT(void)
{
    u8 i;

    for (i = 0; i < 8; i++) {
        if (gx->dirtyVAT & (1 << (u8)i)) {
            GXWGFifo.byte = 8;
            GXWGFifo.byte = i | 0x70;
            GXWGFifo.word = gx->vatA[i];
            GXWGFifo.byte = 8;
            GXWGFifo.byte = i | 0x80;
            GXWGFifo.word = gx->vatB[i];
            GXWGFifo.byte = 8;
            GXWGFifo.byte = i | 0x90;
            GXWGFifo.word = gx->vatC[i];
        }
    }
    gx->dirtyVAT = 0;
}
