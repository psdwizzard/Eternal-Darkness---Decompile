/* Select the CPU command FIFO and link it to the graphics FIFO when shared. */
typedef unsigned char u8;
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

extern volatile u32 *__piReg;
extern __GXFifoObj *CPUFifo; /* CPUFifo */
extern __GXFifoObj *GPFifo; /* GPFifo */
extern u8 CPGPLinked; /* CPGPLinked */

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void __GXFifoLink(u8 enable); /* __GXFifoLink */
void __GXWriteFifoIntEnable(u8 hiWatermarkEn, u8 loWatermarkEn);
void __GXWriteFifoIntReset(u8 underflowEn, u8 overflowEn);

void GXSetCPUFifo(__GXFifoObj *fifo) {
    u32 reg;
    BOOL enabled = OSDisableInterrupts();

    CPUFifo = fifo;
    if (fifo == GPFifo) {
        __piReg[3] = (u32)fifo->base & 0x3FFFFFFF;
        __piReg[4] = (u32)fifo->top & 0x3FFFFFFF;
        reg = (u32)fifo->wrPtr & 0x3FFFFFE0;
        reg &= ~(1 << 26);
        __piReg[5] = reg;
        CPGPLinked = 1;
        __GXWriteFifoIntReset(1, 1);
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    } else {
        if (CPGPLinked) {
            __GXFifoLink(0);
            CPGPLinked = 0;
        }
        __GXWriteFifoIntEnable(0, 0);
        __piReg[3] = (u32)fifo->base & 0x3FFFFFFF;
        __piReg[4] = (u32)fifo->top & 0x3FFFFFFF;
        reg = (u32)fifo->wrPtr & 0x3FFFFFE0;
        reg &= ~(1 << 26);
        __piReg[5] = reg;
    }
    __sync();
    OSRestoreInterrupts(enabled);
}
