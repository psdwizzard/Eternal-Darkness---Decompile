typedef unsigned short u16;
typedef unsigned int u32;

volatile u16 DSPRegisters[] : 0xCC005000;

/* Read the high and low halves of the DSP-to-CPU mailbox. */
u32 fn_8021B8B4(void)
{
    u32 high = DSPRegisters[2];
    u32 low = DSPRegisters[3];

    return (high << 16) | low;
}
