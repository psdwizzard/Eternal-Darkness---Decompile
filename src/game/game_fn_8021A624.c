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

typedef void (*AIStreamCallback)(u32 sampleCount);

extern void OSClearContext(OSContext *context);
extern void OSSetCurrentContext(OSContext *context);
extern AIStreamCallback __AIS_Callback;

volatile u32 __AIRegs[8] : 0xCC006C00;

/* Acknowledge the stream interrupt and invoke its callback in a clean context. */
void __AISHandler(s16 interrupt, OSContext *context)
{
    OSContext exceptionContext;

    __AIRegs[0] |= 8;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);

    if (__AIS_Callback != 0) {
        __AIS_Callback(__AIRegs[2]);
    }

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}
