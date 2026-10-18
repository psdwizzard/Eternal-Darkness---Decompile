typedef unsigned long u32;

volatile u32 __PIRegs[12] : 0xCC003000;
volatile u32 __EXIRegs[15] : 0xCC006800;

/* Acknowledge the requested PI and channel 2 EXI interrupts. */
void AmcEXIClearInterrupts(int piInterrupt, int exiInterrupt)
{
    if (piInterrupt) {
        __PIRegs[0] = (__PIRegs[0] & 0x1000) | 0x1000;
    }
    if (exiInterrupt) {
        __EXIRegs[10] = (__EXIRegs[10] & 0x7F5) | 8;
    }
}
