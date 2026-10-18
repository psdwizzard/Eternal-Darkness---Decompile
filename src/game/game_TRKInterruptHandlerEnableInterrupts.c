typedef unsigned int u32;
typedef struct TRKState {
    u32 gpr[32];
    u32 lr;
    u32 ctr;
    u32 xer;
    u32 msr;
    u32 dar;
    u32 dsisr;
} TRKState;

extern TRKState gTRKState;
extern void TRKPostInterruptEvent(void);

/* Partial context restore. The XER/DSISR/DAR loads stay in C to fit the
 * inline-asm budget, which costs an extra mr and non-r0 temporaries. */
void TRKInterruptHandlerEnableInterrupts(void)
{
    register TRKState *state;
    register u32 value;

    /* ASM: lis/ori/lwz establishes the fixed r2 context base and loads MSR
     * into r0; C cannot select these architectural scratch registers. */
    asm {
        lis r2, gTRKState@h
        ori r2, r2, gTRKState@l
        lwz r0, 0x8c(r2)
    }
    __sync();
    /* ASM: mtmsr restores the machine state, which C cannot write. */
    asm { mtmsr r0 }
    __sync();
    /* ASM: lwz loads the saved LR into r0, which C cannot explicitly select. */
    asm { lwz r0, 0x80(r2) }
    /* ASM: mtlr restores the link register, which C cannot assign. */
    asm { mtlr r0 }
    /* ASM: lwz reads the saved CTR into r0, which C cannot explicitly select. */
    asm { lwz r0, 0x84(r2) }
    /* ASM: mtctr restores the count register, which C cannot assign. */
    asm { mtctr r0 }
    /* ASM: mr reads the fixed r2 context base, which is not C-visible. */
    asm { mr state, r2 }
    value = state->xer;
    /* ASM: mtxer restores XER, which C cannot assign. */
    asm { mtxer value }
    value = state->dsisr;
    /* ASM: mtdsisr restores DSISR, which C cannot assign. */
    asm { mtdsisr value }
    value = state->dar;
    /* ASM: mtdar restores DAR, which C cannot assign. */
    asm { mtdar value }
    /* ASM: lmw/lwz restores r3-r31, r0, r1 and r2; these fixed architectural
     * registers cannot be assigned in C. The r1 load (lwz r1,4(r2)) is an
     * opword because naming r1 makes MWCC emit a stack frame. */
    asm {
        lmw r3, 0xc(r2)
        lwz r0, 0(r2)
        opword 0x80220004
        lwz r2, 8(r2)
    }
    /* ASM: b transfers control while preserving the restored link register;
     * an ordinary C call would overwrite it and create a stack frame. */
    asm { b TRKPostInterruptEvent }
}
