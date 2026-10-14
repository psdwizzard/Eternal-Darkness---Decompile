typedef unsigned long u32;

int OSRestoreInterrupts(register int enable)
{
    register u32 oldState;
    register u32 newState;

    /* ASM: mfmsr reads the machine state register, which C cannot access. */
    asm { mfmsr oldState }

    /* Restore external interrupt enable while preserving the other MSR bits. */
    if (enable) {
        newState = oldState | 0x8000;
    } else {
        newState = oldState & ~0x8000;
    }

    /* ASM: mtmsr writes the machine state register, which C cannot access. */
    asm { mtmsr newState }
    return (oldState >> 15) & 1;
}
