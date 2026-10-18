typedef unsigned char u8;
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

void __GXSaveCPUFifoAux(GXFifoObj *fifo);

/* GXSaveCPUFifo */
void GXSaveCPUFifo(GXFifoObj *fifo)
{
    __GXSaveCPUFifoAux(fifo);
}
