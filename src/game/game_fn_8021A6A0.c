typedef signed short s16;
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

typedef void (*AIDMACallback)(void);

extern void OSClearContext(OSContext *context);
extern void OSSetCurrentContext(OSContext *context);
extern void __AICallbackStackSwitch(AIDMACallback callback);
extern AIDMACallback __AID_Callback;
extern void *__CallbackStack;

volatile u16 DSPRegisters[] : 0xCC005000;

/* Handle the audio DMA interrupt, running the callback in a clean context. */
void __AIDHandler(s16 interrupt, OSContext *context)
{
    OSContext exceptionContext;
    u16 status;

    status = DSPRegisters[5];
    DSPRegisters[5] = (status & ~0xA0) | 8;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);

    if (__AID_Callback != 0) {
        if (__CallbackStack != 0) {
            __AICallbackStackSwitch(__AID_Callback);
        } else {
            __AID_Callback();
        }
    }

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}
