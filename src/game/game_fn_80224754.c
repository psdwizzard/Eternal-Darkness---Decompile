/* GXRestoreWriteGatherPipe: GXRestoreWriteGatherPipe (Dolphin SDK GXFifo.c).
 * Flushes the write-gather pipe, waits for it to drain, re-points it at
 * the GX FIFO and restores the CPU FIFO PI registers; if the CP and GP
 * FIFOs are linked, re-arms the FIFO watermark interrupts and the link. */

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
    u8 pad0[0x8];
    u32 cpEnable;
    u8 pad1[0x4];
    u32 cpClr;
} GXData;

extern GXData *gx;
extern volatile u16 *__cpReg;
extern volatile u32 *__piReg;
extern u32 *CPUFifo; /* CPUFifo */
extern u8 CPGPLinked;   /* CPGPLinked */

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void PPCSync(void);  /* PPCSync */
u32 PPCMfwpar(void);   /* PPCMfwpar */
void PPCMtwpar(u32 newWPAR);

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void GXRestoreWriteGatherPipe(void) {
    u32 i;
    u32 reg;
    BOOL enabled = OSDisableInterrupts();

    for (i = 0; i < 31; i++) {
        GXWGFifo.u8 = 0;
    }
    PPCSync();
    while (PPCMfwpar() & 1) {
    }
    PPCMtwpar(0x0C008000);
    __piReg[3] = CPUFifo[0] & 0x3FFFFFFF;
    __piReg[4] = CPUFifo[1] & 0x3FFFFFFF;
    reg = CPUFifo[6] & 0x3FFFFFE0;
    SET_REG_FIELD(reg, 1, 26, 0);
    __piReg[5] = reg;
    if (CPGPLinked) {
        SET_REG_FIELD(gx->cpClr, 1, 0, 1);
        SET_REG_FIELD(gx->cpClr, 1, 1, 1);
        __cpReg[2] = gx->cpClr;
        SET_REG_FIELD(gx->cpEnable, 1, 2, 1);
        SET_REG_FIELD(gx->cpEnable, 1, 3, 0);
        __cpReg[1] = gx->cpEnable;
        SET_REG_FIELD(gx->cpEnable, 1, 4, 1);
        __cpReg[1] = gx->cpEnable;
    }
    __sync();
    OSRestoreInterrupts(enabled);
}
