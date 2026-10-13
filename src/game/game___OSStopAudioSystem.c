/* __OSStopAudioSystem (Dolphin SDK OSAudioSystem.c). */

typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

extern u32 OSGetTick(void);

volatile u16 __DSPRegs[32] : 0xCC005000;

void __OSStopAudioSystem(void) {
    u32 start;
    u16 reg;

    __DSPRegs[5] = 0x804;
    reg = __DSPRegs[27];
    __DSPRegs[27] = reg & ~0x8000;

    reg = __DSPRegs[5];
    while (reg & 0x400) {
        reg = __DSPRegs[5];
    }
    reg = __DSPRegs[5];
    while (reg & 0x200) {
        reg = __DSPRegs[5];
    }

    __DSPRegs[5] = 0x8ac;
    __DSPRegs[0] = 0;

    while (((__DSPRegs[2] << 16) | __DSPRegs[3]) & 0x80000000) {
    }

    start = OSGetTick();
    while ((s32)(OSGetTick() - start) < 0x2c) {
    }

    __DSPRegs[5] |= 1;
    reg = __DSPRegs[5];
    while (reg & 1) {
        reg = __DSPRegs[5];
    }
}
