typedef unsigned short u16;
typedef unsigned int u32;

volatile u16 DSPRegisters[] : 0xCC005000;

/* Return the CPU-to-DSP mailbox's full flag. */
u32 DSPCheckMailToDSP(void)
{
    return (DSPRegisters[0] >> 15) & 1;
}
