typedef unsigned long u32;
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
} OSContext;

void OSSetCurrentContext(register OSContext *context) {
    register volatile u32 *lowMemory = (volatile u32 *)0x80000000;
    register u32 physicalContext;
    register u32 msr;

    /* Publish both cached and physical addresses of the current context. */
    lowMemory[0xD4 / 4] = (u32)context;
    physicalContext = (u32)context & 0x3FFFFFFF;
    lowMemory[0xC0 / 4] = physicalContext;
    physicalContext = lowMemory[0xD8 / 4];
    /* Only the context that owns the FPU may restore it as enabled. */
    if ((long)physicalContext == (long)context) {
        context->srr1 |= 0x2000;
        /* ASM: mfmsr reads the machine state register, which C cannot access. */
        asm { mfmsr msr }
        msr |= 2;
        /* ASM: mtmsr writes the machine state register, which C cannot access. */
        asm { mtmsr msr }
        return;
    }

    context->srr1 &= ~0x2000;
    /* ASM: mfmsr reads the machine state register, which C cannot access. */
    asm { mfmsr msr }
    msr &= ~0x2000;
    msr |= 2;
    /* ASM: mtmsr writes the machine state register, which C cannot access. */
    asm { mtmsr msr }
    /* ASM: isync synchronizes instruction execution after disabling the FPU;
     * C has no instruction synchronization operation. */
    asm { isync }
}
