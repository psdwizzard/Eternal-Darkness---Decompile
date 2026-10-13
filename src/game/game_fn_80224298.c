typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;

typedef struct {
    void *base;
    void *top;
    u32 size;
    u32 hiWatermark;
    u32 loWatermark;
    void *rdPtr;
    void *wrPtr;
    s32 count;
    u8 bind_cpu;
    u8 bind_gp;
    u8 wrap;
} GXFifoObj;

extern volatile u16 *__cpReg;
extern volatile u32 *__piReg;
extern GXFifoObj *lbl_8064DB90; /* CPUFifo */
extern GXFifoObj *lbl_8064DB94; /* GPFifo */

/* GXGetFifoPtrs: refresh active FIFO state and return its read/write pointers. */
void fn_80224298(GXFifoObj *fifo, void **readPtr, void **writePtr)
{
    if (fifo == lbl_8064DB90) {
        fifo->wrPtr = (void *)((__piReg[5] & ~0x04000000) + 0x80000000);
    }
    if (fifo == lbl_8064DB94) {
        u32 readAddress = __cpReg[29] << 16;
        readAddress |= __cpReg[28];
        fifo->rdPtr = (void *)(readAddress + 0x80000000);
        {
            u32 count = __cpReg[25] << 16;
            count |= __cpReg[24];
            fifo->count = count;
        }
    } else {
        fifo->count = (u8 *)fifo->wrPtr - (u8 *)fifo->rdPtr;
        if (fifo->count < 0) {
            fifo->count += fifo->size;
        }
    }
    *readPtr = fifo->rdPtr;
    *writePtr = fifo->wrPtr;
}
