typedef signed int s32;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct SIWork {
    u8 pad[0x1B0];
    u32 inputBufferValid[4];
    u32 inputBuffer[4][2];
} SIWork;

extern SIWork Packet_80640B68;
extern u32 Type_802FCA34[4];
extern volatile u32 __SIRegs[64] : 0xCC006400;
extern volatile u32 __SIStatus : 0xCC006438;

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32 enabled);

s32 SIGetResponseRaw(s32 chan)
{
    register SIWork *work = &Packet_80640B68;
    register s32 channel = chan;
    u32 enabled = OSDisableInterrupts();
    volatile u8 stack[8];
    register u32 status = __SIStatus;

    status >>= (3 - channel) * 8;
    if ((status & 8) && !(Type_802FCA34[channel] & 0x80)) {
        Type_802FCA34[channel] = 8;
    }
    OSRestoreInterrupts(enabled);

    if (status & 0x20) {
        work->inputBuffer[channel][0] = __SIRegs[channel * 3 + 1];
        work->inputBuffer[channel][1] = __SIRegs[channel * 3 + 2];
        work->inputBufferValid[channel] = 1;
        return 1;
    }
    return 0;
}
