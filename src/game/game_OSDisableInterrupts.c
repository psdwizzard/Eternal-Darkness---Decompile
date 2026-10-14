typedef unsigned long u32;

int OSDisableInterrupts(void)
{
    register u32 newState;
    register u32 oldState;

    /* ASM: mfmsr reads the machine state register, which C cannot access. */
    asm { mfmsr oldState }

    /* Clear external interrupt enable while preserving the other MSR bits. */
    newState = oldState & ~0x8000;

    /* ASM: mtmsr writes the machine state register, which C cannot access. */
    asm { mtmsr newState }

    return (oldState >> 15) & 1;
}
