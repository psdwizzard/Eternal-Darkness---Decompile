extern unsigned char gTRKState[];
extern unsigned char gTRKExceptionStatus_8024A864[];

extern void TRKInterruptHandlerEnableInterrupts(void);
extern void TRKRestoreExtended1Block(void);

/* MetroTRK: hand control back to the target program. The retail routine is a
 * hand-written asm function: it saves the TRK's own GPRs and special registers
 * into gTRKState, masks MSR[EE,RI], and either re-enters the interrupt handler
 * (input pending) or restores the target CPU state and returns with rfi. Only
 * the register save and the pending-input decision are expressed here. */
void TRKSwapAndGo(void)
{
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
    /* ASM: stw/mfxer/mfdsisr/mfdar - saves CTR/XER/DSISR/DAR special purpose
     * registers, which C cannot read */
    asm {
        stw r0, 0x84(r3)
        mfxer r0
        stw r0, 0x88(r3)
        mfdsisr r0
        stw r0, 0x94(r3)
        mfdar r0
        stw r0, 0x90(r3)
    }

    if (**(unsigned char **)(gTRKState + 0xA0) != 0) {
        gTRKState[0x9C] = 1;
        TRKInterruptHandlerEnableInterrupts();
    } else {
        gTRKExceptionStatus_8024A864[0xC] = 0;
        TRKRestoreExtended1Block();
    }
}
