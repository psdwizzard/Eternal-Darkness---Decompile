typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct OSContext OSContext;
typedef struct OSThread OSThread;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;
typedef void (*OSInterruptHandler)(s16 interrupt, OSContext *context);

extern OSInterruptHandler __OSSetInterruptHandler(s16 interrupt, OSInterruptHandler handler);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern void OSInitThreadQueue(OSThreadQueue *queue);
extern void GXTokenInterruptHandler(s16 interrupt, OSContext *context);
extern void GXFinishInterruptHandler(s16 interrupt, OSContext *context);
extern OSThreadQueue FinishQueue;
extern volatile u16 *__peReg;

void __GXPEInit(void)
{
    u32 control;

    __OSSetInterruptHandler(18, GXTokenInterruptHandler);
    __OSSetInterruptHandler(19, GXFinishInterruptHandler);
    OSInitThreadQueue(&FinishQueue);
    __OSUnmaskInterrupts(0x2000);
    __OSUnmaskInterrupts(0x1000);

    /* Acknowledge pending token and finish events, then enable both. */
    control = __peReg[5];
    control = (control & ~4) | 4;
    control = (control & ~8) | 8;
    control = (control & ~1) | 1;
    control = (control & ~2) | 2;
    __peReg[5] = (u16)control;
}
