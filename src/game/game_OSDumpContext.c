/* OSDumpContext (0x8020C1DC, 680 bytes): Dolphin SDK os/OSContext.c */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;
typedef double f64;

#define OS_CONTEXT_STATE_FPSAVED 0x01

typedef struct OSContext {
    u32 gpr[32];
    u32 cr;
    u32 lr;
    u32 ctr;
    u32 xer;
    f64 fpr[32];
    u32 fpscr_pad;
    u32 fpscr;
    u32 srr0;
    u32 srr1;
    u16 mode;
    u16 state;
    u32 gqr[8];
    u32 psf_pad;
    f64 psf[32];
} OSContext;

#define OS_CURRENTCONTEXT_PADDR 0x00C0
#define __OSCurrentContext (*(OSContext**)0x800000D4)
#define __OSFPUContext (*(OSContext**)0x800000D8)

extern void OSReport(const char* msg, ...);
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void OSSetCurrentContext(OSContext* context);
/* __cvt_fp2unsigned: the (u32)double conversion helper */
extern u32 fn_800F5C54(f64 x);

/* OSContext.c string pool */
extern char lbl_802FD3A8[];

static inline OSContext* OSGetCurrentContext(void) {
    return __OSCurrentContext;
}

static inline void OSClearContext(OSContext* context) {
    context->mode = 0;
    context->state = 0;
    if (context == __OSFPUContext) {
        __OSFPUContext = 0;
    }
}

void OSDumpContext(OSContext* context) {
    u32 i;
    u32* p;
    char* msg = lbl_802FD3A8;

    OSReport(msg, context);

    for (i = 0; i < 16; ++i) {
        OSReport(msg + 0x44, i, context->gpr[i], context->gpr[i], i + 16,
                 context->gpr[i + 16], context->gpr[i + 16]);
    }

    OSReport(msg + 0x74, context->lr, context->cr);
    OSReport(msg + 0xA4, context->srr0, context->srr1);

    OSReport(msg + 0xD4);
    for (i = 0; i < 4; ++i) {
        OSReport(msg + 0xE8, i, context->gqr[i], i + 4, context->gqr[i + 4]);
    }

    if (context->state & OS_CONTEXT_STATE_FPSAVED) {
        OSContext* currentContext;
        OSContext fpuContext;
        BOOL enabled;

        enabled = OSDisableInterrupts();
        currentContext = OSGetCurrentContext();
        OSClearContext(&fpuContext);
        OSSetCurrentContext(&fpuContext);

        OSReport(msg + 0x10C);
        for (i = 0; i < 32; i += 2) {
            OSReport(msg + 0x120, i, fn_800F5C54(context->fpr[i]), i + 1,
                     fn_800F5C54(context->fpr[i + 1]));
        }
        OSReport(msg + 0x13C);
        for (i = 0; i < 32; i += 2) {
            OSReport(msg + 0x150, i, fn_800F5C54(context->psf[i]), i + 1,
                     fn_800F5C54(context->psf[i + 1]));
        }

        OSClearContext(&fpuContext);
        OSSetCurrentContext(currentContext);
        OSRestoreInterrupts(enabled);
    }

    OSReport(msg + 0x170);
    for (i = 0, p = (u32*)context->gpr[1]; p && (u32)p != 0xFFFFFFFF && i++ < 16; p = (u32*)*p) {
        OSReport(msg + 0x198, p, p[0], p[1]);
    }
}
