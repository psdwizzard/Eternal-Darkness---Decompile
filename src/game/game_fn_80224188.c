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
extern GXFifoObj *CPUFifo;
extern GXFifoObj *GPFifo;
void __GXSaveCPUFifoAux(GXFifoObj *fifo);

void GXGetFifoStatus(void *fifoArg, u8 *overflow, u8 *underflow,
                 u32 *count, u8 *cpu, u8 *gp, u8 *wrap)
{
    GXFifoObj *fifo = (GXFifoObj *)fifoArg;
    *underflow = 0;
    *overflow = 0;
    *count = 0;
    *wrap = 0;
    if (fifo == GPFifo) {
        u32 temp = __cpReg[29] << 16;
        temp |= __cpReg[28];
        fifo->rdPtr = (void *)(temp + 0x80000000);
        {
            u32 temp2 = __cpReg[25] << 16;
            temp2 |= __cpReg[24];
            fifo->count = temp2;
        }
    }
    if (fifo == CPUFifo) {
        __GXSaveCPUFifoAux(fifo);
        *wrap = (__piReg[5] >> 26) & 1;
    }
    *overflow = fifo->count > fifo->hiWatermark;
    *underflow = fifo->count < fifo->loWatermark;
    *count = fifo->count;
    *cpu = CPUFifo == fifo;
    *gp = GPFifo == fifo;
}
