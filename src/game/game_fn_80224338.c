typedef unsigned short u16;
typedef unsigned long u32;
typedef int BOOL;

typedef struct {
    unsigned char pad0[8];
    u32 cpEnable;
} GXData;

extern GXData *gx;
extern volatile u16 *__cpReg;
extern void *__GXCurrentBP; /* BreakPt */

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void __GXFifoReadDisable(void); /* __GXFifoReadDisable */
void __GXFifoReadEnable(void); /* __GXFifoReadEnable */

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

#define GX_PHY_ADDR(a) ((u32)(a) & 0x3FFFFFFF)

/* GXEnableBreakPt: arm the CP FIFO breakpoint at the given address. */
void GXEnableBreakPt(void *breakPt)
{
    BOOL enabled = OSDisableInterrupts();

    __GXFifoReadDisable();
    __cpReg[30] = (u16)GX_PHY_ADDR(breakPt);
    __cpReg[31] = (u16)(GX_PHY_ADDR(breakPt) >> 16);
    SET_REG_FIELD(gx->cpEnable, 1, 1, 1);
    SET_REG_FIELD(gx->cpEnable, 1, 5, 1);
    __cpReg[1] = gx->cpEnable;
    __GXCurrentBP = breakPt;
    __GXFifoReadEnable();
    OSRestoreInterrupts(enabled);
}
