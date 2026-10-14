typedef unsigned int u32;

typedef struct TRKCPUStateHeader {
    u32 gpr[32];
    u32 pc;
    u32 lr;
    u32 cr;
} TRKCPUStateHeader;

extern unsigned char gTRKCPUState[];

void TRKSaveExtended1Block(void);
int InitMetroTRKCommTable(int hardware);
void TRK_main(void);

/* MetroTRK entry: preserve the integer state, disable interrupts, save the
 * extended state and select the communication hardware from the saved r5.
 * The retail stack switch and final context-return sequence remain unmatched. */
void InitMetroTRK(volatile int entryR3)
{
    register TRKCPUStateHeader *state;
    register u32 msr;
    register u32 lr;
    register u32 cr;
    register u32 zero;

    /* ASM: lis/ori/stmw snapshot all GPRs using r3 as the state base.
     * C cannot read the complete register file; entryR3 is spilled so its
     * incoming value survives the replacement of r3 with the state address. */
    asm {
        lis r3, gTRKCPUState@h
        ori r3, r3, gTRKCPUState@l
        stmw r0, 0(r3)
    }
    state = (TRKCPUStateHeader *)gTRKCPUState;
    /* ASM: stw saves the stack pointer, which C cannot directly read. */
    asm { stw r1, 4(r3) }
    state->gpr[3] = entryR3;

    /* ASM: mflr reads the link register; C cannot access the caller's LR. */
    asm { mflr lr }
    state->lr = lr;
    state->pc = lr;
    /* ASM: mfcr reads the hardware condition register, inaccessible in C. */
    asm { mfcr cr }
    state->cr = cr;

    /* ASM: mfmsr/ori/xori/mtmsr/mtsrr1 clear EE and retain the old MSR in
     * SRR1. C cannot access MSR/SRR1 and folds the ori/xori pair into rlwinm. */
    asm {
        mfmsr msr
        ori r3, msr, 0x8000
        xori r3, r3, 0x8000
        mtmsr r3
        mtsrr1 msr
    }
    TRKSaveExtended1Block();

    /* ASM: lis/ori/lmw reload the complete saved GPR file through r3;
     * C cannot restore the stack pointer and all general registers. */
    asm {
        lis r3, gTRKCPUState@h
        ori r3, r3, gTRKCPUState@l
        lmw r0, 0(r3)
    }
    zero = 0;
    /* ASM: mtspr clears IABR/DABR, privileged breakpoint registers that
     * cannot be written by a C assignment. */
    asm {
        mtspr IABR, zero
        mtspr DABR, zero
    }
    if (InitMetroTRKCommTable(((TRKCPUStateHeader *)gTRKCPUState)->gpr[5]) != 1) {
        TRK_main();
    }
}
