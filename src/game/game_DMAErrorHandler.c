/* Dolphin SDK cache machine-check handler. */
typedef unsigned short OSError;
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
    unsigned short mode;
    unsigned short state;
    u32 gqr[8];
    u32 psf_pad;
    double psf[32];
} OSContext;

extern u32 PPCMfhid2(void);
extern void PPCMthid2(u32 value);
extern void PPCHalt(void);
extern void OSReport(const char* format, ...);
extern void OSDumpContext(OSContext* context);

/* OSCache.c diagnostic string pool at retail address 0x802FD178. */
extern char lbl_802FD178[];

void DMAErrorHandler(OSError error, register OSContext* incomingContext, ...) {
    register u32 hid2;
    register char* messages;
    register OSContext* context;
    register u32 dmaErrors;
    register u32 hid2Value;
    register u32 reportedHid2;
    register char* reportFormat;
    u32 srr1;

    /* ASM: or copies the context without MWCC's addi-zero substitution. */
    asm { or context, incomingContext, incomingContext }
    messages = lbl_802FD178;
    hid2Value = PPCMfhid2();
    /* ASM: or retains the retail register copy; C emits addi with zero. */
    asm { or hid2, hid2Value, hid2Value }

    OSReport(messages + 0x2C);
    srr1 = context->srr1;
    /* ASM: or and addi preserve the HID2 copy and format-address ordering;
     * C substitutes addi-zero and schedules the varargs setup differently. */
    asm {
        or reportedHid2, hid2, hid2
        addi reportFormat, messages, 0x44
    }
    OSReport(reportFormat, reportedHid2, srr1);
    /* ASM: rlwinm preserves the separate mask and unsigned compare;
     * MWCC otherwise folds the C mask test into rlwinm. */
    asm { rlwinm dmaErrors, hid2, 0, 8, 11 }
    if (dmaErrors == 0) {
        goto notDMA;
    }
    dmaErrors = context->srr1;
    /* ASM: rlwinm keeps the SRR1 mask separate from the C comparison,
     * which MWCC otherwise combines into a recording mask instruction. */
    asm { rlwinm dmaErrors, dmaErrors, 0, 10, 10 }
    if (dmaErrors == 0) {
notDMA:
        OSReport(messages + 0x60);
        OSDumpContext(context);
        PPCHalt();
    }
    OSReport(messages + 0x90);
    OSReport(messages + 0xCC);
    /* ASM: rlwinm prevents MWCC from merging the mask and comparison. */
    asm { rlwinm dmaErrors, hid2, 0, 8, 8 }
    if (dmaErrors != 0) {
        OSReport(messages + 0x104);
    }
    /* ASM: rlwinm prevents MWCC from merging the mask and comparison. */
    asm { rlwinm dmaErrors, hid2, 0, 9, 9 }
    if (dmaErrors != 0) {
        OSReport(messages + 0x144);
    }
    /* ASM: rlwinm prevents MWCC from merging the mask and comparison. */
    asm { rlwinm dmaErrors, hid2, 0, 10, 10 }
    if (dmaErrors != 0) {
        OSReport(messages + 0x170);
    }
    /* ASM: rlwinm prevents MWCC from merging the mask and comparison. */
    asm { rlwinm dmaErrors, hid2, 0, 11, 11 }
    if (dmaErrors != 0) {
        OSReport(messages + 0x190);
    }
    PPCMthid2(hid2);
}
