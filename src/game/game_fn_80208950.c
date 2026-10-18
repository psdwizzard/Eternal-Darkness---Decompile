typedef signed int s32;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct SIWork {
    u8 pad[0x1E0];
    u32 responseTime[4];
} SIWork;

extern SIWork Packet_80640B68;
extern u32 __SIRegs[64] : 0xCC006400;

extern s32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(s32 enabled);

s32 SIEnablePollingInterrupt(s32 enable)
{
    s32 interrupts;
    u32 csr;
    s32 wasEnabled;
    SIWork *work = &Packet_80640B68;
    volatile u8 stack[16];

    interrupts = OSDisableInterrupts();
    csr = __SIRegs[13];
    if (csr & 0x08000000) {
        wasEnabled = 1;
    } else {
        wasEnabled = 0;
    }

    if (enable) {
        work->responseTime[0] = 0;
        work->responseTime[1] = 0;
        work->responseTime[2] = 0;
        work->responseTime[3] = 0;
        csr |= 0x08000000;
    } else {
        csr &= ~0x08000000;
    }

    csr &= 0x7FFFFFFE;
    __SIRegs[13] = csr;
    OSRestoreInterrupts(interrupts);
    return wasEnabled;
}
