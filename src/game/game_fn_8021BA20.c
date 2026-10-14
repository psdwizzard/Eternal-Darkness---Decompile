typedef unsigned short u16;
typedef unsigned int u32;

volatile u16 DSPRegisters[] : 0xCC005000;

/* Return the DSP DMA status bit. */
u32 fn_8021BA20(void)
{
    return DSPRegisters[5] & 0x200;
}
