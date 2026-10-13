/* Redirect the write-gather pipe and remember the CPU FIFO write pointer. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef int BOOL;

typedef struct {
    u8 pad0[8];
    u32 cpEnable;
} GXData;

typedef struct {
    void *base;
    void *top;
    u32 size;
    u32 hiWatermark;
    u32 loWatermark;
    void *rdPtr;
    void *wrPtr;
    long count;
    u8 bind_cpu;
    u8 bind_gp;
    u8 wrap;
} GXFifoObj;

extern GXData *gx;
extern volatile u16 *__cpReg;
extern volatile u32 *__piReg;
extern GXFifoObj *lbl_8064DB90;
extern u8 lbl_8064DB9C;

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void fn_80226378(void);
u32 fn_80209B48(void);
void PPCMtwpar(u32 newWPAR);

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

volatile u32 *fn_80224650(volatile u32 *pipeAddress)
{
    BOOL enabled = OSDisableInterrupts();
    u32 pipePtr;
    u32 previousWritePtr;

    fn_80226378();
    while (fn_80209B48() & 1) {
    }
    PPCMtwpar(0x0C008000);

    if (lbl_8064DB9C) {
        SET_REG_FIELD(gx->cpEnable, 1, 4, 0);
        __cpReg[1] = gx->cpEnable;
        SET_REG_FIELD(gx->cpEnable, 1, 2, 0);
        SET_REG_FIELD(gx->cpEnable, 1, 3, 0);
        __cpReg[1] = gx->cpEnable;
    }

    pipePtr = (u32)pipeAddress & 0x3FFFFFE0;
    SET_REG_FIELD(pipePtr, 1, 26, 0);
    previousWritePtr = __piReg[5];
    previousWritePtr &= ~0x04000000;
    lbl_8064DB90->wrPtr = (void *)(previousWritePtr + 0x80000000);
    __piReg[3] = 0;
    __piReg[4] = 0x04000000;
    __piReg[5] = pipePtr;
    __sync();
    OSRestoreInterrupts(enabled);
    return (volatile u32 *)0xCC008000;
}
