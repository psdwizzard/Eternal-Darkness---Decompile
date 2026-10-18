typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);

volatile u16 __DSPRegs[] : 0xCC005000;

/* ARStartDMA */
void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length)
{
    BOOL enabled = OSDisableInterrupts();

    __DSPRegs[0x10] = (u16) (__DSPRegs[0x10] & ~0x3FF) | (u16) (mainmem_addr >> 16);
    __DSPRegs[0x11] = (u16) (__DSPRegs[0x11] & ~0xFFE0) | (u16) (mainmem_addr & 0xFFFF);
    __DSPRegs[0x12] = (u16) (__DSPRegs[0x12] & ~0x3FF) | (u16) (aram_addr >> 16);
    __DSPRegs[0x13] = (u16) (__DSPRegs[0x13] & ~0xFFE0) | (u16) (aram_addr & 0xFFFF);
    __DSPRegs[0x14] = (u16) ((__DSPRegs[0x14] & ~0x8000) | (type << 15));
    __DSPRegs[0x14] = (u16) (__DSPRegs[0x14] & ~0x3FF) | (u16) (length >> 16);
    __DSPRegs[0x15] = (u16) (__DSPRegs[0x15] & ~0xFFE0) | (u16) (length & 0xFFFF);

    OSRestoreInterrupts(enabled);
}
