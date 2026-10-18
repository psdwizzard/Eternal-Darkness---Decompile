typedef int BOOL;
typedef int s32;
typedef unsigned int u32;

typedef void (*EXICallback)(s32 chan, void *context);

typedef struct EXIControl {
    void *exiCallback;
    void *tcCallback;
    EXICallback extCallback;
    u32 state;
    char pad_10[0x10];
    s32 idTime;
    char pad_24[0x1C];
} EXIControl;

extern EXIControl Ecb_80640AA8[3];
extern BOOL __EXIProbe_80206F50(s32 chan);
extern BOOL EXIGetID(s32 chan, u32 dev, u32 *id);
extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL enabled);
extern void EXIClearInterrupts(s32 chan, u32 exi, u32 tc, u32 ext);
extern void __OSUnmaskInterrupts(u32 interrupts);

static inline BOOL __EXIAttach(s32 chan, EXICallback extCallback)
{
    EXIControl *exi = &Ecb_80640AA8[chan];
    BOOL enabled = OSDisableInterrupts();
    BOOL result;

    if ((exi->state & 8) || !__EXIProbe_80206F50(chan)) {
        OSRestoreInterrupts(enabled);
        result = 0;
    } else {
        EXIClearInterrupts(chan, 1, 0, 0);
        exi->extCallback = extCallback;
        __OSUnmaskInterrupts((u32)0x100000 >> (chan * 3));
        exi->state |= 8;
        OSRestoreInterrupts(enabled);
        result = 1;
    }
    return result;
}

BOOL EXIAttach(s32 chan, EXICallback extCallback)
{
    EXIControl *exi = &Ecb_80640AA8[chan];
    BOOL enabled;
    BOOL result;
    u32 id[2];

    if (__EXIProbe_80206F50(chan) && exi->idTime == 0) {
        EXIGetID(chan, 0, &id[1]);
    }

    enabled = OSDisableInterrupts();
    if (exi->idTime == 0) {
        OSRestoreInterrupts(enabled);
        return 0;
    }

    result = __EXIAttach(chan, extCallback);
    OSRestoreInterrupts(enabled);
    return result;
}
