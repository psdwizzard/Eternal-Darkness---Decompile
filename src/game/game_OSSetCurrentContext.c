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
    u32 psf_pad;
    double psf[32];
} OSContext;

void OSSetCurrentContext(register OSContext *context) {
    register volatile u32 *lowMemory = (volatile u32 *)0x80000000;
    u32 fpuContext;

    /* Publish both cached and physical addresses of the current context. */
    lowMemory[0xD4 / 4] = (u32)context;
    /* ASM: clrlwi, stw retain the physical address in r5; MWCC assigns
     * the equivalent C mask/store temporary to r0. */
    asm {
        clrlwi r5, context, 2
        stw r5, 0xC0(lowMemory)
    }
    fpuContext = lowMemory[0xD8 / 4];
    /* Only the context that owns the FPU may restore it as enabled. */
    if ((long)fpuContext == (long)context) {
        /* ASM: lwz, ori, stw update SRR1's FP bit through r6; C assigns
         * this temporary to r0 and cannot bind it to the SDK scratch register. */
        asm {
            lwz r6, OSContext.srr1(context)
            ori r6, r6, 0x2000
            stw r6, OSContext.srr1(context)
        }
        /* ASM: mfmsr, ori, mtmsr enable recoverable interrupts through r6.
         * C cannot access MSR or bind its update temporary to r6. */
        asm {
            mfmsr r6
            ori r6, r6, 2
            mtmsr r6
        }
        return;
    }

    /* ASM: lwz, rlwinm, stw clear SRR1's FP bit through r6; C assigns
     * this temporary to r0 and cannot bind it to the SDK scratch register. */
    asm {
        lwz r6, OSContext.srr1(context)
        rlwinm r6, r6, 0, 19, 17
        stw r6, OSContext.srr1(context)
    }
    /* ASM: mfmsr, rlwinm, ori, mtmsr disable FP and enable recoverable
     * interrupts through r6. C cannot access MSR or bind its temporary to r6. */
    asm {
        mfmsr r6
        rlwinm r6, r6, 0, 19, 17
        ori r6, r6, 2
        mtmsr r6
    }
    /* Synchronize instruction execution after disabling the FPU. */
    __isync();
}
