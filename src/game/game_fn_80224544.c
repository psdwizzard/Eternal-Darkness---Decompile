/* __GXCleanGPFifo (__GXCleanGPFifo, Dolphin SDK GXFifo.c).
 * Resets the GP FIFO's read and write pointers back to its base: first a
 * scratch copy of the FIFO is bound so the hardware drains nothing stale,
 * then the real FIFO is reset and rebound. */

typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;
typedef int BOOL;

/* Matches the definition used by GXSetGPFifo (game_GXSetGPFifo.c). */
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

/* The public GXFifoObj is 0x80 bytes of storage backing the private fields. */
typedef struct {
    u8 data[0x80];
} GXFifoStorage;

typedef union {
    __GXFifoObj fifo;
    GXFifoStorage storage;
} GXFifoBuffer;

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void GXSetGPFifo(__GXFifoObj *fifo);
void GXSetCPUFifo(__GXFifoObj *fifo);
GXFifoBuffer *GXGetGPFifo(void); /* GXGetGPFifo */
GXFifoBuffer *GXGetCPUFifo(void); /* GXGetCPUFifo */

static inline void *GXGetFifoBase(GXFifoBuffer *fifo) {
    __GXFifoObj *realFifo = &fifo->fifo;

    return realFifo->base;
}

static inline void GXInitFifoPtrs(GXFifoBuffer *fifo, void *readPtr, void *writePtr) {
    __GXFifoObj *realFifo = &fifo->fifo;
    BOOL enabled = OSDisableInterrupts();

    realFifo->rdPtr = readPtr;
    realFifo->wrPtr = writePtr;
    realFifo->count = (u8 *)writePtr - (u8 *)readPtr;
    if (realFifo->count < 0) {
        realFifo->count += realFifo->size;
    }
    OSRestoreInterrupts(enabled);
}

void __GXCleanGPFifo(void) {
    GXFifoBuffer *gpFifo = GXGetGPFifo();
    GXFifoBuffer *cpuFifo = GXGetCPUFifo();
    void *base = GXGetFifoBase(gpFifo);
    GXFifoBuffer dummyFifo;

    dummyFifo = *gpFifo;
    GXInitFifoPtrs(&dummyFifo, base, base);
    GXSetGPFifo(&dummyFifo.fifo);
    if (cpuFifo == gpFifo) {
        GXSetCPUFifo(&dummyFifo.fifo);
    }

    GXInitFifoPtrs(gpFifo, base, base);
    GXSetGPFifo(&gpFifo->fifo);
    if (cpuFifo == gpFifo) {
        GXSetCPUFifo(&cpuFifo->fifo);
    }
}
