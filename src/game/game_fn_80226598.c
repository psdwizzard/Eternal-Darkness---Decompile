/* GXSetDrawDone: GXSetDrawDone (Dolphin SDK GXMisc.c).
 * Writes the draw-done token (0x45000002) to the BP/RAS registers, flushes
 * the FIFO via an inlined GXFlush, then clears the DrawDone flag. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef int BOOL;

typedef union {
    u8 u8;
    u16 u16;
    u32 u32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

typedef struct {
    u8 pad0[0x4F4];
    u32 dirtyState;
} GXData;

extern GXData *gx;
extern u8 DrawDone; /* DrawDone */

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void PPCSync(void); /* PPCSync */
void __GXSetDirtyState(void); /* __GXSetDirtyState */

#define GX_WRITE_RAS_REG(reg) \
    do { \
        GXWGFifo.u8 = 0x61; \
        GXWGFifo.u32 = (reg); \
    } while (0)

/* GXFlush */
static inline void GXFlush(void) {
    if (gx->dirtyState) {
        __GXSetDirtyState();
    }
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    PPCSync();
}

void GXSetDrawDone(void) {
    BOOL enabled;
    u32 reg;

    enabled = OSDisableInterrupts();
    reg = 0x45000002;
    GX_WRITE_RAS_REG(reg);
    GXFlush();
    DrawDone = 0;
    OSRestoreInterrupts(enabled);
}
