typedef unsigned short u16;

volatile u16 __DSPRegs[] : 0xCC005000;

/* AIStartDMA: enable audio DMA. */
void fn_8021A110(void)
{
    __DSPRegs[0x1B] |= 0x8000;
}
