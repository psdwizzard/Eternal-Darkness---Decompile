typedef unsigned short u16;

volatile u16 __DSPRegs[] : 0xCC005000;

/* AIStartDMA: enable audio DMA. */
void AIStartDMA(void)
{
    __DSPRegs[0x1B] |= 0x8000;
}
