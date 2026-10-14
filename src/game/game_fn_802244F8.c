typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct {
    u8 pad0[8];
    u32 cpEnable;
    u32 cpStatus;
    u32 cpClr;
} GXData;

extern GXData *gx;
extern volatile u16 *__cpReg;

/* __GXWriteFifoIntReset: clear the FIFO watermark interrupts. */
void fn_802244F8(u8 hiWatermarkClr, u8 loWatermarkClr)
{
    gx->cpClr = (gx->cpClr & ~1UL) | hiWatermarkClr;
    gx->cpClr = (gx->cpClr & ~2UL) | (loWatermarkClr << 1);
    __cpReg[2] = gx->cpClr;
}
