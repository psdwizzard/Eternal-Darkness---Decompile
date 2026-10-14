/* Flush the cached texture state register to the graphics FIFO. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 vNumNot;
    u16 bpSentNot;
    u8 state[0x120];
    u32 texFlush;
} GXData;

typedef union {
    u8 u8;
    u32 u32;
} PPCWGPipe;

extern GXData *gx;
volatile PPCWGPipe GXWGFifo : 0xCC008000;

void __GXFlushTextureState(void) {
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = gx->texFlush;
    gx->bpSentNot = 0;
}
