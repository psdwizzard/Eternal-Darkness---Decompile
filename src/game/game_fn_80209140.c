typedef signed int s32;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct SIWork {
    u8 pad[0x1B0];
    u32 inputBufferValid[4];
    u32 inputBuffer[4][2];
} SIWork;

extern SIWork Packet_80640B68;
extern volatile u32 __SIRegs[64] : 0xCC006400;

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32 enabled);
extern u32 SIGetStatus(s32 chan);

s32 SIGetResponse(s32 chan, void *data)
{
    register SIWork *work = &Packet_80640B68;
    u32 enabled = OSDisableInterrupts();
    s32 valid;

    if (SIGetStatus(chan) & 0x20) {
        work->inputBuffer[chan][0] = __SIRegs[chan * 3 + 1];
        work->inputBuffer[chan][1] = __SIRegs[chan * 3 + 2];
        work->inputBufferValid[chan] = 1;
    }

    valid = work->inputBufferValid[chan];
    work->inputBufferValid[chan] = 0;
    if (valid) {
        ((u32 *)data)[0] = work->inputBuffer[chan][0];
        ((u32 *)data)[1] = work->inputBuffer[chan][1];
    }
    OSRestoreInterrupts(enabled);
    return valid;
}
