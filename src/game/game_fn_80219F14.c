#include "src/game/types.h"

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

typedef void (*PADSamplingCallback)(void);

extern PADSamplingCallback lbl_8064DACC;
extern void OSClearContext(OSContext *context);
extern void OSSetCurrentContext(OSContext *context);

/* Run the PAD sampling callback in a temporary context. */
void fn_80219F14(s16 interrupt, OSContext *context)
{
    OSContext exceptionContext;

    if (lbl_8064DACC != 0) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        lbl_8064DACC();
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}
