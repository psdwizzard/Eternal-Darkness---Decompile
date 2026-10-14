typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct {
    u8 pad0[8];
    u32 cpEnable;
    u32 cpStatus;
} GXData;

extern GXData *gx;
extern volatile u16 *__cpReg;

/* __GXWriteFifoIntEnable: enable the FIFO watermark interrupts. */
void fn_802244AC(u8 hiWatermarkEn, u8 loWatermarkEn)
{
    gx->cpEnable = (gx->cpEnable & ~4UL) | (hiWatermarkEn << 2);
    gx->cpEnable = (gx->cpEnable & ~8UL) | (loWatermarkEn << 3);
    __cpReg[1] = gx->cpEnable;
}
