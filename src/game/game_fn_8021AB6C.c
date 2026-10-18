typedef short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct OSContext {
    u32 gpr[32];
    u32 cr;
    u32 lr;
    u32 ctr;
    u32 xer;
    double fpr[32];
    u32 fpscr_pad;
    u32 fpscr;
    u32 srr0;
    u32 srr1;
    u16 mode;
    u16 state;
    u32 gqr[8];
    u32 psf_pad;
    double psf[32];
} OSContext;

typedef void (*ARCallback)(void);
extern ARCallback __AR_Callback;
extern void OSClearContext(OSContext* context);
extern void OSSetCurrentContext(OSContext* context);

volatile u16 __DSPRegs[] : 0xCC005000;

/* Acknowledge ARAM DMA completion and run its callback in a temporary context. */
void __ARHandler(s16 interrupt, OSContext* context)
{
    OSContext exceptionContext;
    u16 control;

    control = __DSPRegs[5];
    control = (control & ~0x88) | 0x20;
    __DSPRegs[5] = control;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    if (__AR_Callback != 0) {
        __AR_Callback();
    }
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}
