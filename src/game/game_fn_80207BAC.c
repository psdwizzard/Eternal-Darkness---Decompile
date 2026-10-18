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
extern void *memmove(void *dest, const void *src, u32 size);

BOOL EXIUnlock(s32 chan)
{
    EXIControl *exi = &Ecb_80640AA8[chan];
    BOOL enabled = OSDisableInterrupts();
    EXICallback unlockedCallback;

    if (!(exi->state & 0x10)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    exi->state &= ~0x10;
    SetExiInterruptMask(chan, exi);
    if (exi->queueLength > 0) {
        unlockedCallback = exi->queue[0].callback;
        if (--exi->queueLength > 0) {
            memmove(&exi->queue[0], &exi->queue[1], exi->queueLength * sizeof(EXIQueueEntry));
        }
        unlockedCallback(chan, 0);
    }
    OSRestoreInterrupts(enabled);
    return 1;
}
