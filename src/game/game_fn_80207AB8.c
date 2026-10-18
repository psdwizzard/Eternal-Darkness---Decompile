typedef signed int s32;
typedef unsigned int u32;
typedef int BOOL;

typedef void (*EXICallback)(s32 chan, void *context);

typedef struct EXIQueueEntry {
    u32 dev;
    EXICallback callback;
} EXIQueueEntry;

typedef struct EXIControl {
    EXICallback exiCallback;
    EXICallback tcCallback;
    EXICallback extCallback;
    volatile u32 state;
    void *immBuf;
    s32 immLen;
    u32 dev;
    u32 id;
    s32 idTime;
    s32 queueLength;
    EXIQueueEntry queue[3];
} EXIControl;

extern EXIControl Ecb_80640AA8[3];
extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL enabled);
extern void SetExiInterruptMask(s32 chan, EXIControl *exi);

BOOL EXILock(s32 chan, u32 dev, EXICallback unlockedCallback)
{
    EXIControl *exi = &Ecb_80640AA8[chan];
    BOOL enabled = OSDisableInterrupts();
    s32 i;

    if (exi->state & 0x10) {
        if (unlockedCallback != 0) {
            for (i = 0; i < exi->queueLength; i++) {
                if (exi->queue[i].dev == dev) {
                    OSRestoreInterrupts(enabled);
                    return 0;
                }
            }
            exi->queue[exi->queueLength].callback = unlockedCallback;
            exi->queue[exi->queueLength].dev = dev;
            exi->queueLength++;
        }
        OSRestoreInterrupts(enabled);
        return 0;
    }

    exi->state |= 0x10;
    exi->dev = dev;
    SetExiInterruptMask(chan, exi);
    OSRestoreInterrupts(enabled);
    return 1;
}
