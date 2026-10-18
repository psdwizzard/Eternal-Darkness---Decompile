/* Install the command processor interrupt handler and reset FIFO state. */
typedef short s16;
typedef unsigned long u32;
typedef struct OSContext OSContext;
typedef struct OSThread OSThread;
typedef struct __GXFifoObj __GXFifoObj;
typedef void (*OSInterruptHandler)(s16 interrupt, OSContext *context);

extern OSInterruptHandler __OSSetInterruptHandler(s16 interrupt, OSInterruptHandler handler);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern OSThread *OSGetCurrentThread(void);
extern void GXCPInterruptHandler(s16 interrupt, OSContext *context);

extern OSThread *__GXCurrentThread;   /* __GXCurrentThread */
extern u32 GXOverflowSuspendInProgress;        /* GXOverflowSuspendInProgress */
extern __GXFifoObj *CPUFifo; /* CPUFifo */
extern __GXFifoObj *GPFifo; /* GPFifo */

void __GXFifoInit(void) {
    __OSSetInterruptHandler(17, GXCPInterruptHandler);
    __OSUnmaskInterrupts(0x4000);
    __GXCurrentThread = OSGetCurrentThread();
    GXOverflowSuspendInProgress = 0;
    CPUFifo = 0;
    GPFifo = 0;
}
