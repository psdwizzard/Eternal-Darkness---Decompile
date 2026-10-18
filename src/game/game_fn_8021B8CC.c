typedef unsigned short u16;
typedef unsigned int u32;

volatile u16 DSPRegisters[] : 0xCC005000;

/* Write the high and low halves of the CPU-to-DSP mailbox. */
void DSPSendMailToDSP(u32 message)
{
    DSPRegisters[0] = message >> 16;
    DSPRegisters[1] = message;
}
