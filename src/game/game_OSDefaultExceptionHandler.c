typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct OSContext {
    u32 gpr[32];
    u32 cr, lr, ctr, xer;
    double fpr[32];
    u32 fpscr_pad, fpscr;
    u32 srr0, srr1;
    u16 mode, state;
    u32 gqr[8];
} OSContext;

extern void __OSUnhandledException(u8 exception, OSContext *context,
                                   u32 dsisr, u32 dar);

void OSDefaultExceptionHandler(register u8 exception, register OSContext *context) {
    register u32 value;
    register u32 dsisr;
    register u32 dar;

    /* ASM: stw and stmw save the interrupted registers, which have no C
     * values. The exception vector has already saved r3 through r5. */
    asm {
        stw r0, 0(context)
        stw r1, 4(context)
        stw r2, 8(context)
        stmw r6, 24(context)
    }
    /* ASM: mfspr and stw save GQR1 through r0. C cannot read the SPR
     * or bind its save temporary to the exception entry's scratch register. */
    asm {
        mfspr r0, 913
        stw r0, 0x1A8(context)
    }
    /* ASM: mfspr and stw save GQR2 through r0. C cannot read the SPR
     * or bind its save temporary to the exception entry's scratch register. */
    asm {
        mfspr r0, 914
        stw r0, 0x1AC(context)
    }
    /* ASM: mfspr and stw save GQR3 through r0. C cannot read the SPR
     * or bind its save temporary to the exception entry's scratch register. */
    asm {
        mfspr r0, 915
        stw r0, 0x1B0(context)
    }
    /* ASM: mfspr reads GQR4, which is inaccessible to C. */
    asm { mfspr value, 916 }
    context->gqr[4] = value;
    /* ASM: mfspr reads GQR5, which is inaccessible to C. */
    asm { mfspr value, 917 }
    context->gqr[5] = value;
    /* ASM: mfspr reads GQR6, which is inaccessible to C. */
    asm { mfspr value, 918 }
    context->gqr[6] = value;
    /* ASM: mfspr reads GQR7, which is inaccessible to C. */
    asm { mfspr value, 919 }
    context->gqr[7] = value;
    /* ASM: mfdsisr and mfdar read the processor's fault status and address,
     * which cannot be accessed by C expressions. */
    asm {
        mfdsisr dsisr
        mfdar dar
    }
    __OSUnhandledException(exception, context, dsisr, dar);
}
