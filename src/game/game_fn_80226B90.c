/* __GXSendFlushPrim: send a triangle strip of zero-filled vertices to
 * flush the vertex pipeline, then set the BP tracking flag. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 vNumNot;
    u16 bpSentNot;
    u16 vNum;
    u16 vLim;
} GXData;

extern GXData *gx;

typedef union {
    u8 u8;
    u16 u16;
    u32 u32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

void fn_80226B90(void)
{
    u32 bytes = gx->vNum * gx->vLim;
    u32 i;

    GXWGFifo.u8 = 0x98;
    GXWGFifo.u16 = gx->vNum;
    for (i = 0; i < bytes; i += 4) {
        GXWGFifo.u32 = 0;
    }
    gx->bpSentNot = 1;
}
