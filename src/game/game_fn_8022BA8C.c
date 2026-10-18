/* __GXSetMatrixIndex: send the selected matrix index register to CP and XF. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 vNumNot;
    u16 bpSentNot;
    u8 pad4[0x80 - 4];
    u32 matIdxA;
    u32 matIdxB;
} GXData;

extern GXData *gx;

typedef union {
    u8 u8;
    u32 u32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

void __GXSetMatrixIndex(int attr)
{
    u32 matrixIndex;

    if (attr < 5) {
        GXWGFifo.u8 = 8;
        GXWGFifo.u8 = 0x30;
        matrixIndex = gx->matIdxA;
        GXWGFifo.u32 = matrixIndex;
        GXWGFifo.u8 = 0x10;
        GXWGFifo.u32 = 0x1018;
        GXWGFifo.u32 = matrixIndex;
    } else {
        GXWGFifo.u8 = 8;
        GXWGFifo.u8 = 0x40;
        matrixIndex = gx->matIdxB;
        GXWGFifo.u32 = matrixIndex;
        GXWGFifo.u8 = 0x10;
        GXWGFifo.u32 = 0x1019;
        GXWGFifo.u32 = matrixIndex;
    }
    gx->bpSentNot = 1;
}
