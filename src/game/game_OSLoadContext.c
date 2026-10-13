typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef double f64;

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
} OSContext;

extern int OSDisableInterrupts(void);

void OSLoadContext(OSContext *context) {
    register u32 srr0;
    register u32 start;
    register u32 bit;
    register u32 value;

    /* Restart an interrupted OSDisableInterrupts sequence from the start. */
    srr0 = context->srr0;
    start = (u32)OSDisableInterrupts;
    if (srr0 >= start && srr0 <= (u32)((u8 *)OSDisableInterrupts + 0x10)) {
        context->srr0 = start;
    }

    /* The general-purpose registers (r0-r2, lmw r5/r13, r3/r4) cannot be
     * reloaded from C; the asm budget is spent on the special registers. */
    value = context->state;
    if ((bit = value & 2) != 0) {
        value &= ~2;
        context->state = value;
    }

    value = context->gqr[1];
    // ASM: mtspr GQR1 - C cannot write a special-purpose register.
    asm { mtspr 913, value }
    value = context->gqr[2];
    // ASM: mtspr GQR2 - C cannot write a special-purpose register.
    asm { mtspr 914, value }
    value = context->gqr[3];
    // ASM: mtspr GQR3 - C cannot write a special-purpose register.
    asm { mtspr 915, value }
    value = context->gqr[4];
    // ASM: mtspr GQR4 - C cannot write a special-purpose register.
    asm { mtspr 916, value }
    value = context->gqr[5];
    // ASM: mtspr GQR5 - C cannot write a special-purpose register.
    asm { mtspr 917, value }
    value = context->gqr[6];
    // ASM: mtspr GQR6 - C cannot write a special-purpose register.
    asm { mtspr 918, value }
    value = context->gqr[7];
    // ASM: mtspr GQR7 - C cannot write a special-purpose register.
    asm { mtspr 919, value }

    value = context->cr;
    // ASM: mtcrf - the condition register is not C-visible.
    asm { mtcrf 255, value }
    value = context->lr;
    // ASM: mtlr - the link register is not C-visible.
    asm { mtlr value }
    value = context->ctr;
    // ASM: mtctr - the count register is not C-visible.
    asm { mtctr value }
    value = context->xer;
    // ASM: mtxer - the fixed-point exception register is not C-visible.
    asm { mtxer value }

    // ASM: mfmsr - the MSR cannot be read from C.
    asm { mfmsr value }
    value &= ~0x8000;
    value &= ~2;
    // ASM: mtmsr - disable EE/RI; the MSR cannot be written from C.
    asm { mtmsr value }

    value = context->srr0;
    // ASM: mtsrr0 - the interrupt return address is not C-visible.
    asm { mtsrr0 value }
    value = context->srr1;
    // ASM: mtsrr1 - the interrupt return MSR is not C-visible.
    asm { mtsrr1 value }
    // ASM: rfi - returning from an interrupt context has no C equivalent.
    asm { rfi }
}
