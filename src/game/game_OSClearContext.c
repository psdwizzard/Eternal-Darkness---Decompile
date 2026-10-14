typedef unsigned short u16;
typedef unsigned int u32;
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
    u32 psf_pad;
    f64 psf[32];
} OSContext;

void OSClearContext(register OSContext* context) {
    register OSContext** lowMemory = (OSContext**)0x80000000;
    register OSContext* fpuContext;

    context->mode = 0;
    context->state = 0;
    fpuContext = lowMemory[0xD8 / 4];
    /* ASM: cmplw, bne preserve the branch to the shared return; MWCC
     * folds the equivalent C conditional into a conditional return. */
    asm {
        cmplw context, fpuContext
        bne done
    }
    lowMemory[0xD8 / 4] = 0;
    /* ASM: done labels the shared return targeted by bne above. */
    asm {
    done:
    }
}
