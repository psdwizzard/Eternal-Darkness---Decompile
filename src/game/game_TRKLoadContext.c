typedef struct TRKContext {
    unsigned int gpr[32];       /* 0x000 */
    unsigned int cr;            /* 0x080 */
    unsigned int lr;            /* 0x084 */
    unsigned int ctr;           /* 0x088 */
    unsigned int xer;           /* 0x08C */
    unsigned char pad[0x198 - 0x90];
    unsigned int srr0;          /* 0x198 */
    unsigned int srr1;          /* 0x19C */
    unsigned short mode;        /* 0x1A0 */
    unsigned short state;       /* 0x1A2 */
} TRKContext;

extern void TRKInterruptHandler(void);

/* MetroTRK: restore a saved CPU context and re-enter the exception path.
 * The retail routine is a hand-written frameless asm function that reloads
 * every GPR (including r1/r2) from the context; the context field reads and
 * flag/MSR bit handling are expressed in C. */
void TRKLoadContext(TRKContext *ctx, unsigned int exceptionId)
{
    unsigned short state;
    register unsigned int value;
    register unsigned int msr;

    /* ASM: lwz r0/r1/r2 - reloads the stack pointer and small-data base
     * from the context; C cannot assign r1/r2 */
    asm {
        lwz r0, 0x0(r3)
        lwz r1, 0x4(r3)
        lwz r2, 0x8(r3)
    }
    state = ctx->state;
    if (state & 2) {
        ctx->state = state & ~2;
        /* ASM: lmw r5 - reloads r5..r31 including volatiles; C has no
         * multiple-load of fixed registers */
        asm { lmw r5, 0x14(r3) }
    } else {
        /* ASM: lmw r13 - reloads the non-volatile GPRs r13..r31 */
        asm { lmw r13, 0x34(r3) }
    }
    value = ctx->cr;
    /* ASM: mtcrf - writes the whole condition register; C cannot */
    asm { mtcrf 255, value }
    value = ctx->lr;
    /* ASM: mtlr - writes the link register; C cannot */
    asm { mtlr value }
    value = ctx->ctr;
    /* ASM: mtctr - writes the count register; C cannot */
    asm { mtctr value }
    value = ctx->xer;
    /* ASM: mtxer - writes the fixed-point exception register; C cannot */
    asm { mtxer value }
    /* ASM: mfmsr - reads the machine state register; C cannot */
    asm { mfmsr msr }
    msr = msr & ~0x8000 & ~0x2;
    /* ASM: mtmsr/mtsprg 1 - disables EE/RI in MSR and stashes the restored
     * r2 in SPRG1; supervisor SPR writes are not expressible in C */
    asm {
        mtmsr msr
        mtsprg 1, r2
    }
    value = ctx->gpr[3];
    /* ASM: mtsprg 2 - stashes the context's r3 in SPRG2 */
    asm { mtsprg 2, value }
    value = ctx->gpr[4];
    /* ASM: mtsprg 3 - stashes the context's r4 in SPRG3 */
    asm { mtsprg 3, value }
    /* ASM: b - tail-jumps into the exception handler with the restored
     * registers live; a C call would build a frame and return */
    asm { b TRKInterruptHandler }
}
