/* Initialize the FIFO bounds, default watermarks and read/write pointers. */
typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;

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

void GXInitFifoLimits(__GXFifoObj *fifo, u32 hiWatermark, u32 loWatermark);
void GXInitFifoPtrs(__GXFifoObj *fifo, void *readPtr, void *writePtr);

void GXInitFifoBase(__GXFifoObj *fifo, void *base, u32 size) {
    __GXFifoObj *realFifo = fifo;

    realFifo->base = base;
    realFifo->top = (u8 *)((u32)base + size - 4);
    realFifo->size = size;
    fifo->count = 0;
    GXInitFifoLimits(fifo, size - 0x4000, (size / 2) & ~0x1F);
    GXInitFifoPtrs(fifo, base, base);
}
