/* __OSInitAudioSystem (0x8020B468, 444 bytes): stock SDK OSAudioSystem.c. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

extern void* OSGetArenaHi(void);
extern void* memcpy(void*, const void*, unsigned long);
extern void DCFlushRange(void*, u32);
extern u32 OSGetTick(void);

extern u8 DSPInitCode[128];

#define __DSPWorkBuffer (void*)0x81000000
volatile u16 __DSPRegs[] : 0xCC005000;

void __OSInitAudioSystem(void) {
    u8 errFlag;
    u16 reg16;
    u32 start_tick;

    memcpy((u8*)OSGetArenaHi() - 128, __DSPWorkBuffer, 128);
    memcpy(__DSPWorkBuffer, DSPInitCode, 128);

    DCFlushRange(__DSPWorkBuffer, 128);

    __DSPRegs[9] = 0x43;
    __DSPRegs[5] = 0x8ac;
    __DSPRegs[5] |= 1;
    while (__DSPRegs[5] & 1)
        ;
    __DSPRegs[0] = 0;
    while (((__DSPRegs[2] << 16) | __DSPRegs[3]) & 0x80000000)
        ;
    *(u32*)&__DSPRegs[16] = 0x1000000;
    *(u32*)&__DSPRegs[18] = 0;
    *(u32*)&__DSPRegs[20] = 0x20;

    reg16 = __DSPRegs[5];
    while (!(reg16 & 0x20))
        reg16 = __DSPRegs[5];
    __DSPRegs[5] = reg16;

    start_tick = OSGetTick();
    while ((s32)(OSGetTick() - start_tick) < 0x892)
        ;

    *(u32*)&__DSPRegs[16] = 0x1000000;
    *(u32*)&__DSPRegs[18] = 0;
    *(u32*)&__DSPRegs[20] = 0x20;

    reg16 = __DSPRegs[5];
    while (!(reg16 & 0x20))
        reg16 = __DSPRegs[5];
    __DSPRegs[5] = reg16;

    __DSPRegs[5] &= ~0x800;
    while (__DSPRegs[5] & 0x400)
        ;
    __DSPRegs[5] &= ~4;

    errFlag = 0;
    reg16 = __DSPRegs[2];
    while (!(reg16 & 0x8000))
        reg16 = __DSPRegs[2];
    if (((reg16 << 16) | __DSPRegs[3]) != 0x4348) {
        errFlag = 1;
    }

    __DSPRegs[5] |= 4;
    __DSPRegs[5] = 0x8ac;
    __DSPRegs[5] |= 1;
    while (__DSPRegs[5] & 1)
        ;

    memcpy(__DSPWorkBuffer, (u8*)OSGetArenaHi() - 128, 128);
}
