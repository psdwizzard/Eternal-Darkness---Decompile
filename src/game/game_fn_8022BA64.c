/* GXSetClipMode: write the XF clipping control register. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 vNumNot;
    u16 bpSentNot;
} GXData;

extern GXData *gx;

typedef union {
    u8 u8;
    u32 u32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

void fn_8022BA64(int mode)
{
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = 0x1005;
    GXWGFifo.u32 = mode;
    gx->bpSentNot = 1;
}
