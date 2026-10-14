typedef unsigned long u32;

int OSRestoreInterrupts(register int enable)
{
    register u32 newState;
    register u32 oldState;

    /* ASM: cmpwi/mfmsr/beq keep the comparison before the MSR read;
     * C cannot read the MSR between a comparison and its branch.
     * r3 holds enable under the PowerPC calling convention. */
    asm {
        cmpwi r3, 0
        mfmsr oldState
        beq disabled
    }
    /* Preserve every MSR bit except external interrupt enable. */
    newState = oldState | 0x8000;
    goto restore;
disabled:
    newState = oldState & ~0x8000;
restore:
    /* ASM: mtmsr writes the machine state register, which C cannot access. */
    asm { mtmsr newState }
    return (oldState >> 15) & 1;
}
