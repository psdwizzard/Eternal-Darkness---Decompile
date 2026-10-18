typedef int BOOL;
typedef int s32;
typedef unsigned int u32;

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
extern BOOL __EXIProbe_80206F50(s32 chan);
extern u32 EXIClearInterrupts(s32 chan, s32 exi, s32 tc, s32 ext);
extern void SetExiInterruptMask(s32 chan, EXIControl *exi);
extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL enabled);
extern void __OSMaskInterrupts(u32 interrupts);
extern void __OSUnmaskInterrupts(u32 interrupts);
extern BOOL EXILock(s32 chan, u32 dev, EXICallback callback);
extern BOOL EXISelect(s32 chan, u32 dev, u32 freq);
extern BOOL EXIImm(s32 chan, void *buf, s32 len, u32 type, void *callback);
extern BOOL EXISync(s32 chan);
extern BOOL EXIDeselect(s32 chan);
extern void *memmove(void *dest, const void *src, u32 size);
extern void UnlockedHandler(s32 chan, void *context);

s32 __gUnknown800030C0[2] : 0x800030C0;

static inline BOOL AttachForID(s32 chan, EXICallback extCallback)
{
    EXIControl *exi;
    BOOL enabled;

    exi = &Ecb_80640AA8[chan];
    enabled = OSDisableInterrupts();
    if ((exi->state & 8) || !__EXIProbe_80206F50(chan)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    EXIClearInterrupts(chan, 1, 0, 0);
    exi->extCallback = extCallback;
    __OSUnmaskInterrupts(0x100000U >> (chan * 3));
    exi->state |= 8;
    OSRestoreInterrupts(enabled);
    return 1;
}

static inline BOOL UnlockForID(s32 chan)
{
    EXIControl *exi;
    BOOL enabled;
    EXICallback unlockedCallback;

    exi = &Ecb_80640AA8[chan];
    enabled = OSDisableInterrupts();
    if (!(exi->state & 0x10)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    exi->state &= ~0x10;
    SetExiInterruptMask(chan, exi);
    if (exi->queueLength > 0) {
        unlockedCallback = exi->queue[0].callback;
        if (--exi->queueLength > 0) {
            memmove(&exi->queue[0], &exi->queue[1],
                        exi->queueLength * sizeof(EXIQueueEntry));
        }
        unlockedCallback(chan, 0);
    }
    OSRestoreInterrupts(enabled);
    return 1;
}

static inline BOOL DetachForID(s32 chan)
{
    EXIControl *exi;
    BOOL enabled;

    exi = &Ecb_80640AA8[chan];
    enabled = OSDisableInterrupts();
    if (!(exi->state & 8)) {
        OSRestoreInterrupts(enabled);
        return 1;
    }
    if ((exi->state & 0x10) && exi->dev == 0) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    exi->state &= ~8;
    __OSMaskInterrupts(0x700000U >> (chan * 3));
    OSRestoreInterrupts(enabled);
    return 1;
}

BOOL EXIGetID(s32 chan, u32 dev, u32 *id)
{
    EXIControl *exi = &Ecb_80640AA8[chan];
    s32 err;
    u32 cmd;
    s32 startTime;
    BOOL enabled;

    if (chan < 2 && dev == 0) {
        if (!__EXIProbe_80206F50(chan)) {
            return 0;
        }

        if (exi->idTime == __gUnknown800030C0[chan]) {
            *id = exi->id;
            return exi->idTime;
        }

        if (!AttachForID(chan, 0)) {
            return 0;
        }

        startTime = __gUnknown800030C0[chan];
    }

    err = !EXILock(chan, dev, (chan < 2 && dev == 0) ? UnlockedHandler : 0);
    if (err == 0) {
        err = !EXISelect(chan, dev, 0);
        if (err == 0) {
            cmd = 0;
            err |= !EXIImm(chan, &cmd, 2, 1, 0);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, id, 4, 0, 0);
            err |= !EXISync(chan);
            err |= !EXIDeselect(chan);
        }

        UnlockForID(chan);
    }
    if (chan < 2 && dev == 0) {
        DetachForID(chan);
        enabled = OSDisableInterrupts();
        err |= __gUnknown800030C0[chan] != startTime;
        if (!err) {
            exi->id = *id;
            exi->idTime = startTime;
        }
        OSRestoreInterrupts(enabled);

        if (err) {
            return 0;
        }
        return exi->idTime;
    }

    if (err) {
        return 0;
    }
    return 1;
}
