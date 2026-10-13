typedef unsigned int u32;
typedef unsigned short u16;

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

extern void OSClearContext(OSContext *context);

/* OSInitContext: prepare the register state for a new execution context. */
void fn_8020C120(register OSContext *context, u32 pc, u32 stackPointer)
{
    context->srr0 = pc;
    context->gpr[1] = stackPointer;
    /* ASM: li/ori/stw preserve the OS initializer's r11 MSR construction;
     * MWCC materializes this unsigned constant with lis/addi instead. */
    asm {
        li r11, 0
        ori r11, r11, 0x9032
        stw r11, 0x19c(context)
    }
    context->cr = 0;
    context->xer = 0;
    /* ASM: stw captures the ABI's r2 and r13 small-data bases, which C
     * cannot access as register values. */
    asm {
        stw r2, 8(context)
        stw r13, 0x34(context)
    }
    context->gpr[3] = 0;
    context->gpr[4] = 0;
    context->gpr[5] = 0;
    context->gpr[6] = 0;
    context->gpr[7] = 0;
    context->gpr[8] = 0;
    context->gpr[9] = 0;
    context->gpr[10] = 0;
    context->gpr[11] = 0;
    context->gpr[12] = 0;
    context->gpr[14] = 0;
    context->gpr[15] = 0;
    context->gpr[16] = 0;
    context->gpr[17] = 0;
    context->gpr[18] = 0;
    context->gpr[19] = 0;
    context->gpr[20] = 0;
    context->gpr[21] = 0;
    context->gpr[22] = 0;
    context->gpr[23] = 0;
    context->gpr[24] = 0;
    context->gpr[25] = 0;
    context->gpr[26] = 0;
    context->gpr[27] = 0;
    context->gpr[28] = 0;
    context->gpr[29] = 0;
    context->gpr[30] = 0;
    context->gpr[31] = 0;
    context->gqr[0] = 0;
    context->gqr[1] = 0;
    context->gqr[2] = 0;
    context->gqr[3] = 0;
    context->gqr[4] = 0;
    context->gqr[5] = 0;
    context->gqr[6] = 0;
    context->gqr[7] = 0;
    /* ASM: lis/addi/mtctr/bctr preserve the caller's LR for the tail
     * transfer; MWCC emits a stack frame for a C call and rejects a direct
     * external b in an inline assembly statement. */
    asm {
        lis r12, OSClearContext@ha
        addi r12, r12, OSClearContext@l
        mtctr r12
        bctr
    }
}
