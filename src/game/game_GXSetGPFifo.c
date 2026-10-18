/* GXSetGPFifo (Dolphin SDK GXFifo.c).
 * Points the graphics processor's command FIFO at the given FIFO object:
 * programs the CP FIFO registers with its bounds, watermarks and pointers,
 * then links or unlinks it from the CPU FIFO depending on whether the two
 * are the same object. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;
typedef int BOOL;

typedef struct {
    u8 *base;
    u8 *top;
    u32 size;
    u32 hiWatermark;
    u32 loWatermark;
    void *rdPtr;
    void *wrPtr;
    s32 count;
    u8 bind_cpu;
    u8 bind_gp;
    u8 wrap;
} __GXFifoObj;

extern volatile u16 *__cpReg;
extern __GXFifoObj *CPUFifo; /* CPUFifo */
extern __GXFifoObj *GPFifo; /* GPFifo */
extern u8 CPGPLinked;           /* CPGPLinked */

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void __GXFifoReadEnable(void); /* __GXFifoReadEnable */
void __GXFifoReadDisable(void); /* __GXFifoReadDisable */
void __GXFifoLink(u8 enable); /* __GXFifoLink */
void __GXWriteFifoIntEnable(u8 hiWatermarkEn, u8 loWatermarkEn); /* __GXWriteFifoIntEnable */
void __GXWriteFifoIntReset(u8 underflowEn, u8 overflowEn); /* __GXWriteFifoIntReset */

#define GX_PHY_ADDR(a) ((u32)(a) & 0x3FFFFFFF)

void GXSetGPFifo(__GXFifoObj *fifo) {
    BOOL enabled = OSDisableInterrupts();

    __GXFifoReadDisable();
    __GXWriteFifoIntEnable(0, 0);
    GPFifo = fifo;

    __cpReg[16] = (u16)GX_PHY_ADDR(fifo->base);
    __cpReg[18] = (u16)GX_PHY_ADDR(fifo->top);
    __cpReg[24] = (u16)fifo->count;
    __cpReg[26] = (u16)GX_PHY_ADDR(fifo->wrPtr);
    __cpReg[28] = (u16)GX_PHY_ADDR(fifo->rdPtr);
    __cpReg[20] = (u16)fifo->hiWatermark;
    __cpReg[22] = (u16)fifo->loWatermark;
    __cpReg[17] = (u16)(GX_PHY_ADDR(fifo->base) >> 16);
    __cpReg[19] = (u16)(GX_PHY_ADDR(fifo->top) >> 16);
    __cpReg[25] = (u16)(fifo->count >> 16);
    __cpReg[27] = (u16)(GX_PHY_ADDR(fifo->wrPtr) >> 16);
    __cpReg[29] = (u16)(GX_PHY_ADDR(fifo->rdPtr) >> 16);
    __cpReg[21] = (u16)(fifo->hiWatermark >> 16);
    __cpReg[23] = (u16)(fifo->loWatermark >> 16);

    __sync();

    if (CPUFifo == GPFifo) {
        CPGPLinked = 1;
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    } else {
        CPGPLinked = 0;
        __GXWriteFifoIntEnable(0, 0);
        __GXFifoLink(0);
    }
    __GXWriteFifoIntReset(1, 1);
    __GXFifoReadEnable();
    OSRestoreInterrupts(enabled);
}
