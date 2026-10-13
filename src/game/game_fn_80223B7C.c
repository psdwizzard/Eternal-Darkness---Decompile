/* fn_80223B7C: GXCPInterruptHandler (Dolphin SDK GXFifo.c).
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
extern OSThread *lbl_8064DB98;          /* __GXCurrentThread */
extern u32 lbl_8064DBA0;                /* GXOverflowSuspendInProgress */
extern GXBreakPtCallback lbl_8064DBA4;  /* BreakPointCB */
extern u32 lbl_8064DBA8;                /* __GXOverflowCount */

extern void OSClearContext(OSContext *context);
extern void OSSetCurrentContext(OSContext *context);
int fn_8020FC0C(OSThread *thread);  /* OSResumeThread */
int fn_8020FE94(OSThread *thread);  /* OSSuspendThread */
void fn_802244AC(u8 hiWatermarkEn, u8 loWatermarkEn); /* __GXWriteFifoIntEnable */
void fn_802244F8(u8 hiWatermarkClr, u8 loWatermarkClr); /* __GXWriteFifoIntReset */

#define GET_REG_FIELD(reg, size, shift) (((reg) >> (shift)) & ((1 << (size)) - 1))
#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void fn_80223B7C(s16 interrupt, OSContext *context) {
    OSContext exceptionContext;

    gx->cpStatus = __cpReg[0];

    if (GET_REG_FIELD(gx->cpEnable, 1, 3) && GET_REG_FIELD(gx->cpStatus, 1, 1)) {
        fn_8020FC0C(lbl_8064DB98);
        lbl_8064DBA0 = 0;
        fn_802244F8(1, 1);
        fn_802244AC(1, 0);
    }

    if (GET_REG_FIELD(gx->cpEnable, 1, 2) && GET_REG_FIELD(gx->cpStatus, 1, 0)) {
        lbl_8064DBA8++;
        fn_802244AC(0, 1);
        fn_802244F8(1, 0);
        lbl_8064DBA0 = 1;
        fn_8020FE94(lbl_8064DB98);
    }

    if (GET_REG_FIELD(gx->cpEnable, 1, 5) && GET_REG_FIELD(gx->cpStatus, 1, 4)) {
        SET_REG_FIELD(gx->cpEnable, 1, 5, 0);
        __cpReg[1] = gx->cpEnable;
        if (lbl_8064DBA4 != 0) {
            OSClearContext(&exceptionContext);
            OSSetCurrentContext(&exceptionContext);
            lbl_8064DBA4();
            OSClearContext(&exceptionContext);
            OSSetCurrentContext(context);
        }
    }
}
