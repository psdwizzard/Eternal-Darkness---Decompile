typedef unsigned short u16;

volatile u16 __DSPRegs[] : 0xCC005000;

/* AIStopDMA: disable audio DMA. */
void AIStopDMA(void)
{
    __DSPRegs[0x1B] &= ~0x8000;
}
