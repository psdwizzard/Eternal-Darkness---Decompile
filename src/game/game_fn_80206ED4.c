typedef int BOOL;
typedef int s32;

typedef void (*EXICallback)(s32, void *);

typedef struct EXIControl {
    EXICallback exiCallback;
    void *tcCallback;
    char pad_08[0x38];
} EXIControl;

extern EXIControl Ecb_80640AA8[3];

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL);
extern void SetExiInterruptMask(s32, EXIControl *);

EXICallback EXISetExiCallback(s32 chan, EXICallback exiCallback)
{
    EXIControl *exi = &Ecb_80640AA8[chan];
    EXICallback previous;
    BOOL enabled;

    enabled = OSDisableInterrupts();
    previous = exi->exiCallback;
    exi->exiCallback = exiCallback;
    if (chan != 2) {
        SetExiInterruptMask(chan, exi);
    } else {
        SetExiInterruptMask(0, Ecb_80640AA8);
    }
    OSRestoreInterrupts(enabled);
    return previous;
}
