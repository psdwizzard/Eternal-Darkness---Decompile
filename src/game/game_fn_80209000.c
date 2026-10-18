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

u32 SIDisablePolling(u32 poll)
{
    u32 enabled;
    u32 current;

    if (poll == 0) {
        return Si_802FCA20.poll;
    }

    enabled = OSDisableInterrupts();
    current = Si_802FCA20.poll;
    poll = (poll >> 24) & 0xF0;
    poll = current & ~poll;
    Si_802FCA20.poll = __SIRegs[12] = poll;
    OSRestoreInterrupts(enabled);
    return poll;
}
