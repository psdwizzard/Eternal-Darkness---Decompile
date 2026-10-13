/* fn_80226598: GXSetDrawDone (Dolphin SDK GXMisc.c).
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
extern u8 lbl_8064DBB8; /* DrawDone */

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void fn_80209AD4(void); /* PPCSync */
void fn_80226A28(void); /* __GXSetDirtyState */

#define GX_WRITE_RAS_REG(reg) \
    do { \
        GXWGFifo.u8 = 0x61; \
        GXWGFifo.u32 = (reg); \
    } while (0)

/* GXFlush */
static inline void GXFlush(void) {
    if (gx->dirtyState) {
        fn_80226A28();
    }
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    fn_80209AD4();
}

void fn_80226598(void) {
    BOOL enabled;
    u32 reg;

    enabled = OSDisableInterrupts();
    reg = 0x45000002;
    GX_WRITE_RAS_REG(reg);
    GXFlush();
    lbl_8064DBB8 = 0;
    OSRestoreInterrupts(enabled);
}
