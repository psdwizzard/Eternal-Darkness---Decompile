/* GXInitFifoLimits: sets the FIFO's high and low watermarks. */

typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;

/* Matches the FIFO layout used by GXSetGPFifo and GXInitFifoPtrs. */
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

void fn_80223D94(__GXFifoObj *fifo, u32 hiWatermark, u32 loWatermark) {
    fifo->hiWatermark = hiWatermark;
    fifo->loWatermark = loWatermark;
}
