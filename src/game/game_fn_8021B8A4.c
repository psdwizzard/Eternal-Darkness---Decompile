typedef unsigned short u16;
typedef unsigned int u32;

volatile u16 DSPRegisters[] : 0xCC005000;

/* Return the DSP-to-CPU mailbox's full flag. */
u32 fn_8021B8A4(void)
{
    return (DSPRegisters[2] >> 15) & 1;
}
