typedef int BOOL;
typedef int s32;
typedef unsigned int u32;

typedef struct EXIControl {
    void *exiCallback;
    void *tcCallback;
    void *extCallback;
    volatile u32 state;
    void *immBuf;
    u32 immLen;
    u32 dev;
    u32 id;
    s32 idTime;
    char pad_24[0x1C];
} EXIControl;

extern EXIControl Ecb_80640AA8[3];
extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL enabled);
extern void __OSMaskInterrupts(u32 interrupts);

BOOL EXIDetach(s32 chan)
{
    EXIControl *exi = &Ecb_80640AA8[chan];
    BOOL enabled = OSDisableInterrupts();

    if (!(exi->state & 8)) {
        OSRestoreInterrupts(enabled);
        return 1;
    }
    if ((exi->state & 0x10) && exi->dev == 0) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    exi->state &= ~8;
    __OSMaskInterrupts((u32)0x700000 >> (chan * 3));
    OSRestoreInterrupts(enabled);
    return 1;
}
