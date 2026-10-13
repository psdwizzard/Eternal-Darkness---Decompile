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

typedef void (*OSExceptionHandler)(u8 exception, OSContext *context);
extern void OSDefaultExceptionHandler(u8 exception, OSContext *context);

/* The vector runs with address translation disabled. The C return below is
 * unreachable after rfi; retaining the exception number as the result keeps
 * the handler\'s first argument live in r3 through dispatch. */
u32 OSExceptionVector(register u32 value, register OSContext *context,
                       register u32 savedR5) {
    register OSContext *currentContext;
    register u32 savedMSR;

    /* ASM: mtsprg preserves the interrupted r4 in a special-purpose register. */
    asm { mtsprg 0, context }
    currentContext = *(OSContext *volatile *)0xC0;
    currentContext->gpr[3] = value;
    /* ASM: mfsprg reads the interrupted r4; C cannot access SPRG0. */
    asm { mfsprg value, 0 }
    currentContext->gpr[4] = value;
    currentContext->gpr[5] = savedR5;
    value = currentContext->state;
    value |= 2;
    currentContext->state = value;
    /* ASM: mfcr reads the interrupted condition register. */
    asm { mfcr value }
    currentContext->cr = value;
    /* ASM: mflr reads the interrupted link register. */
    asm { mflr value }
    currentContext->lr = value;
    /* ASM: mfctr reads the interrupted count register. */
    asm { mfctr value }
    currentContext->ctr = value;
    /* ASM: mfxer reads the fixed-point exception register. */
    asm { mfxer value }
    currentContext->xer = value;
    /* ASM: mfsrr0 reads the interrupted instruction address. */
    asm { mfsrr0 value }
    currentContext->srr0 = value;
    /* ASM: mfsrr1 reads the interrupted machine state. */
    asm { mfsrr1 value }
    currentContext->srr1 = value;
    savedMSR = value;
    /* ASM: nop reserves the debugger's patchable vector instruction. */
    asm { nop }
    /* ASM: mfmsr reads the current machine state, inaccessible to C. */
    asm { mfmsr value }
    value |= 0x30;
    /* ASM: mtsrr1 sets the machine state used by the exception return. */
    asm { mtsrr1 value }
    /* ASM: addi (li) reserves the exception-number instruction patched at
     * installation. A C constant assignment can be folded into the lookup. */
    asm { addi value, r0, 0 }
    currentContext = *(OSContext *volatile *)0xD4;
    if ((savedMSR &= 2) == 0) {
        savedMSR = (u32)OSDefaultExceptionHandler;
        /* ASM: mtsrr0 and rfi enter the handler with the saved machine state. */
        asm {
            mtsrr0 savedMSR
            rfi
        }
    }
    {
        savedMSR = (u8)value << 2;
        savedMSR = *(volatile u32 *)(savedMSR + 0x3000);
        /* ASM: mtsrr0 and rfi enter the selected exception handler. */
        asm {
            mtsrr0 savedMSR
            rfi
        }
    }
    /* Both dispatch paths leave this vector via rfi. */
    return value;
}
