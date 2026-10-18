typedef unsigned int u32;

typedef struct SIControl {
    int chan;
    u32 poll;
    u32 inputBytes;
    void *input;
    void (*callback)(int, u32, void *);
} SIControl;

extern SIControl Si_802FCA20;
extern volatile u32 __SIRegs[] : 0xCC006400;
extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32 enabled);

u32 SIEnablePolling(u32 poll)
{
    u32 enabled;

    if (poll == 0) {
        return Si_802FCA20.poll;
    }

    enabled = OSDisableInterrupts();
    poll >>= 24;
    Si_802FCA20.poll &= ~((poll & 0xF0) >> 4);
    poll &= 0x03FFFFF0 | ((poll & 0xF0) >> 4);
    poll &= 0xFC0000FF;
    Si_802FCA20.poll |= poll;
    poll = Si_802FCA20.poll;
    __SIRegs[14] = 0x80000000;
    __SIRegs[12] = poll;
    OSRestoreInterrupts(enabled);
    return poll;
}
