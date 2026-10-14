/* Install the command processor interrupt handler and reset FIFO state. */
typedef short s16;
typedef unsigned long u32;
typedef struct OSContext OSContext;
typedef struct OSThread OSThread;
typedef struct __GXFifoObj __GXFifoObj;
typedef void (*OSInterruptHandler)(s16 interrupt, OSContext *context);

extern OSInterruptHandler __OSSetInterruptHandler(s16 interrupt, OSInterruptHandler handler);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern OSThread *fn_8020F2DC(void);
extern void fn_80223B7C(s16 interrupt, OSContext *context);

extern OSThread *lbl_8064DB98;   /* __GXCurrentThread */
extern u32 lbl_8064DBA0;        /* GXOverflowSuspendInProgress */
extern __GXFifoObj *lbl_8064DB90; /* CPUFifo */
extern __GXFifoObj *lbl_8064DB94; /* GPFifo */

void __GXFifoInit(void) {
    __OSSetInterruptHandler(17, fn_80223B7C);
    __OSUnmaskInterrupts(0x4000);
    lbl_8064DB98 = fn_8020F2DC();
    lbl_8064DBA0 = 0;
    lbl_8064DB90 = 0;
    lbl_8064DB94 = 0;
}
