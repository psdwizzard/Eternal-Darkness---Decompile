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
extern void fn_80206778(s32, EXIControl *);

EXICallback fn_80206ED4(s32 chan, EXICallback exiCallback)
{
    EXIControl *exi = &Ecb_80640AA8[chan];
    EXICallback previous;
    BOOL enabled;

    enabled = OSDisableInterrupts();
    previous = exi->exiCallback;
    exi->exiCallback = exiCallback;
    if (chan != 2) {
        fn_80206778(chan, exi);
    } else {
        fn_80206778(0, Ecb_80640AA8);
    }
    OSRestoreInterrupts(enabled);
    return previous;
}
