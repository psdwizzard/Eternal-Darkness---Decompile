typedef unsigned int u32;
typedef unsigned char u8;

typedef struct TRKState {
    u32 gpr[32];
    u32 lr, ctr, xer, msr, dar, dsisr;
    u32 reserved;
    u8 inputActivated;
    u8 padding[3];
    u8 *inputPending;
} TRKState;

extern TRKState gTRKState;
extern unsigned char gTRKExceptionStatus_8024A864[];

extern void TRKInterruptHandlerEnableInterrupts(void);
extern void TRKRestoreExtended1Block(void);

/* MetroTRK: hand control back to the target program. The retail routine is a
 * hand-written asm function: it saves the TRK's own GPRs and special registers
 * into gTRKState, masks MSR[EE,RI], and either re-enters the interrupt handler
 * (input pending) or restores the target CPU state and returns with rfi.
 * The final target-register restore and rfi remain unresolved here. */
void TRKSwapAndGo(void)
{
    register int value;

    /* ASM: lis/ori/stmw r0/mfmsr/mflr/mfctr - stores all 32 GPRs (stmw from
     * r0) and reads MSR/LR/CTR; C has no access to these registers */
    asm {
        lis r3, gTRKState@h
        ori r3, r3, gTRKState@l
        stmw r0, 0x0(r3)
        mfmsr r0
        stw r0, 0x8c(r3)
        mflr r0
        stw r0, 0x80(r3)
        mfctr r0
    }
    /* ASM: stw/mfxer/mfdsisr - saves CTR/XER/DSISR special purpose
     * registers, which C cannot read */
    asm {
        stw r0, 0x84(r3)
        mfxer r0
        stw r0, 0x88(r3)
        mfdsisr r0
        stw r0, 0x94(r3)
    }

    /* ASM: mfdar reads the data-access exception address register. */
    asm { mfdar value }
    gTRKState.dar = value;
    /* ASM: mfmsr reads the machine state for interrupt masking. */
    asm { mfmsr value }
    /* Retail complements the sign-extended immediate 0x8002. */
    value &= 0x7FFD;
    /* ASM: mtmsr updates the privileged machine-state register. */
    asm { mtmsr value }

    if ((int)*gTRKState.inputPending == 0) {
        gTRKExceptionStatus_8024A864[0xC] = 0;
        TRKRestoreExtended1Block();
    } else {
        gTRKState.inputActivated = 1;
        TRKInterruptHandlerEnableInterrupts();
    }
}

