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
extern void fn_8021A730(AIDMACallback callback);
extern AIDMACallback lbl_8064DADC;
extern void *lbl_8064DAE0;

volatile u16 DSPRegisters[] : 0xCC005000;

/* Handle the audio DMA interrupt, running the callback in a clean context. */
void fn_8021A6A0(s16 interrupt, OSContext *context)
{
    OSContext exceptionContext;
    u16 status;

    status = DSPRegisters[5];
    DSPRegisters[5] = (status & ~0xA0) | 8;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);

    if (lbl_8064DADC != 0) {
        if (lbl_8064DAE0 != 0) {
            fn_8021A730(lbl_8064DADC);
        } else {
            lbl_8064DADC();
        }
    }

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}
