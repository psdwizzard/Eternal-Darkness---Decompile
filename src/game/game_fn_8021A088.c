/* AIInitDMA: set the audio DMA buffer address and length. */
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);

volatile u16 __DSPRegs[] : 0xCC005000;

void fn_8021A088(void* buffer, u32 length)
{
    BOOL level = OSDisableInterrupts();

    __DSPRegs[0x18] = (__DSPRegs[0x18] & ~0x3FF) | ((u32)buffer >> 16);
    __DSPRegs[0x19] = (__DSPRegs[0x19] & ~0xFFE0) | (u16)(u32)buffer;
    __DSPRegs[0x1B] = (__DSPRegs[0x1B] & ~0x7FFF) | (u16)(length >> 5);

    OSRestoreInterrupts(level);
}
