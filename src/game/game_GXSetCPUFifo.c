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
extern __GXFifoObj *lbl_8064DB90; /* CPUFifo */
extern __GXFifoObj *lbl_8064DB94; /* GPFifo */
extern u8 lbl_8064DB9C; /* CPGPLinked */

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void fn_80224468(u8 enable); /* __GXFifoLink */
void fn_802244AC(u8 hiWatermarkEn, u8 loWatermarkEn);
void fn_802244F8(u8 underflowEn, u8 overflowEn);

void GXSetCPUFifo(__GXFifoObj *fifo) {
    u32 reg;
    BOOL enabled = OSDisableInterrupts();

    lbl_8064DB90 = fifo;
    if (fifo == lbl_8064DB94) {
        __piReg[3] = (u32)fifo->base & 0x3FFFFFFF;
        __piReg[4] = (u32)fifo->top & 0x3FFFFFFF;
        reg = (u32)fifo->wrPtr & 0x3FFFFFE0;
        reg &= ~(1 << 26);
        __piReg[5] = reg;
        lbl_8064DB9C = 1;
        fn_802244F8(1, 1);
        fn_802244AC(1, 0);
        fn_80224468(1);
    } else {
        if (lbl_8064DB9C) {
            fn_80224468(0);
            lbl_8064DB9C = 0;
        }
        fn_802244AC(0, 0);
        __piReg[3] = (u32)fifo->base & 0x3FFFFFFF;
        __piReg[4] = (u32)fifo->top & 0x3FFFFFFF;
        reg = (u32)fifo->wrPtr & 0x3FFFFFE0;
        reg &= ~(1 << 26);
        __piReg[5] = reg;
    }
    __sync();
    OSRestoreInterrupts(enabled);
}
