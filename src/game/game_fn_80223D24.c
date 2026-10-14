/* fn_80223D24 (GXInitFifoPtrs, Dolphin SDK GXFifo.c).
 * Sets a FIFO's read and write pointers and recomputes how many bytes lie
 * between them, wrapping around the FIFO size when the write pointer is
 * behind the read pointer. Interrupts are disabled while the FIFO is updated. */

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

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);

void fn_80223D24(__GXFifoObj *fifo, void *readPtr, void *writePtr) {
    __GXFifoObj *realFifo = fifo;
    BOOL enabled = OSDisableInterrupts();

    realFifo->rdPtr = readPtr;
    realFifo->wrPtr = writePtr;
    realFifo->count = (u8 *)writePtr - (u8 *)readPtr;
    if (realFifo->count < 0) {
        realFifo->count += realFifo->size;
    }
    OSRestoreInterrupts(enabled);
}
