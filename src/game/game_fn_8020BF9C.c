typedef unsigned long u32;
typedef unsigned short u16;

typedef struct OSContext {
    u32 gpr[32];
    u32 cr, lr, ctr, xer;
    double fpr[32];
    u32 fpscr_pad, fpscr;
    u32 srr0, srr1;
    u16 mode, state;
    u32 gqr[8];
} OSContext;

/* Save the calling context, with a nonzero result for a later restore. */
int fn_8020BF9C(register OSContext *context) {
    register u32 value;

    /* ASM: stmw saves the live nonvolatile GPRs, inaccessible from C. */
    asm {
        stmw r13, 0x34(context)
    }
    /* ASM: mfspr reads GQR1; C cannot access quantization registers. */
    asm { mfspr value, 913 }
    context->gqr[1] = value;
    /* ASM: mfspr reads GQR2; C cannot access quantization registers. */
    asm { mfspr value, 914 }
    context->gqr[2] = value;
    /* ASM: mfspr reads GQR3; C cannot access quantization registers. */
    asm { mfspr value, 915 }
    context->gqr[3] = value;
    /* ASM: mfspr reads GQR4; C cannot access quantization registers. */
    asm { mfspr value, 916 }
    context->gqr[4] = value;
    /* ASM: mfspr reads GQR5; C cannot access quantization registers. */
    asm { mfspr value, 917 }
    context->gqr[5] = value;
    /* ASM: mfspr reads GQR6; C cannot access quantization registers. */
    asm { mfspr value, 918 }
    context->gqr[6] = value;
    /* ASM: mfspr reads GQR7; C cannot access quantization registers. */
    asm { mfspr value, 919 }
    context->gqr[7] = value;
    /* ASM: mfcr reads the condition register, inaccessible from C. */
    asm { mfcr value }
    context->cr = value;
    /* ASM: mflr reads the caller's return address, inaccessible from C. */
    asm { mflr value }
    context->lr = value;
    context->srr0 = value;
    /* ASM: mfmsr reads the machine state register, inaccessible from C. */
    asm { mfmsr value }
    context->srr1 = value;
    /* ASM: mfctr reads the count register, inaccessible from C. */
    asm { mfctr value }
    context->ctr = value;
    /* ASM: mfxer reads the fixed-point exception register, inaccessible from C. */
    asm { mfxer value }
    context->xer = value;
    /* ASM: stw saves the live stack and small-data pointers; C cannot
     * directly name the architectural r1 and r2 values. */
    asm {
        stw r1, 4(context)
        stw r2, 8(context)
    }
    context->gpr[3] = 1;
    return 0;
}
