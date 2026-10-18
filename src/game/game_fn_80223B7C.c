/* GXCPInterruptHandler: GXCPInterruptHandler (Dolphin SDK GXFifo.c).
 * Latches the CP status register, then services the FIFO high/low
 * watermark interrupts (suspending/resuming the GX thread) and the
 * breakpoint interrupt (invoking the user breakpoint callback inside a
 * fresh exception context). */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef short s16;

typedef struct OSContext {
    u8 data[0x2C8];
} OSContext;

typedef struct OSThread OSThread;

typedef struct {
    u8 pad0[0x8];
    u32 cpEnable;
    u32 cpStatus;
} GXData;

typedef void (*GXBreakPtCallback)(void);

extern GXData *gx;
extern volatile u16 *__cpReg;
extern OSThread *__GXCurrentThread;          /* __GXCurrentThread */
extern u32 GXOverflowSuspendInProgress;                /* GXOverflowSuspendInProgress */
extern GXBreakPtCallback BreakPointCB;  /* BreakPointCB */
extern u32 __GXOverflowCount;                /* __GXOverflowCount */

extern void OSClearContext(OSContext *context);
extern void OSSetCurrentContext(OSContext *context);
int OSResumeThread(OSThread *thread);  /* OSResumeThread */
int OSSuspendThread(OSThread *thread);  /* OSSuspendThread */
void __GXWriteFifoIntEnable(u8 hiWatermarkEn, u8 loWatermarkEn); /* __GXWriteFifoIntEnable */
void __GXWriteFifoIntReset(u8 hiWatermarkClr, u8 loWatermarkClr); /* __GXWriteFifoIntReset */

#define GET_REG_FIELD(reg, size, shift) (((reg) >> (shift)) & ((1 << (size)) - 1))
#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void GXCPInterruptHandler(s16 interrupt, OSContext *context) {
    OSContext exceptionContext;

    gx->cpStatus = __cpReg[0];

    if (GET_REG_FIELD(gx->cpEnable, 1, 3) && GET_REG_FIELD(gx->cpStatus, 1, 1)) {
        OSResumeThread(__GXCurrentThread);
        GXOverflowSuspendInProgress = 0;
        __GXWriteFifoIntReset(1, 1);
        __GXWriteFifoIntEnable(1, 0);
    }

    if (GET_REG_FIELD(gx->cpEnable, 1, 2) && GET_REG_FIELD(gx->cpStatus, 1, 0)) {
        __GXOverflowCount++;
        __GXWriteFifoIntEnable(0, 1);
        __GXWriteFifoIntReset(1, 0);
        GXOverflowSuspendInProgress = 1;
        OSSuspendThread(__GXCurrentThread);
    }

    if (GET_REG_FIELD(gx->cpEnable, 1, 5) && GET_REG_FIELD(gx->cpStatus, 1, 4)) {
        SET_REG_FIELD(gx->cpEnable, 1, 5, 0);
        __cpReg[1] = gx->cpEnable;
        if (BreakPointCB != 0) {
            OSClearContext(&exceptionContext);
            OSSetCurrentContext(&exceptionContext);
            BreakPointCB();
            OSClearContext(&exceptionContext);
            OSSetCurrentContext(context);
        }
    }
}
