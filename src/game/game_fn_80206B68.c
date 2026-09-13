typedef int BOOL;
typedef int s32;
typedef unsigned int u32;

typedef struct EXIControl {
    void *exiCallback;
    void *tcCallback;
    char pad_08[4];
    volatile u32 state;
    s32 immLen;
    void *immBuf;
    char pad_18[0x28];
} EXIControl;

extern EXIControl Ecb_80640AA8[3];

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL);
extern void __OSUnmaskInterrupts(u32);
extern void fn_80206E8C(s32, s32, s32, s32);

BOOL EXIDma(s32 chan, void *buf, s32 len, u32 type, void *callback)
{
    BOOL enabled;
    u32 regAddr;
    EXIControl *exi;

    exi = &Ecb_80640AA8[chan];
    enabled = OSDisableInterrupts();
    if ((exi->state & 3) || !(exi->state & 4)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }

    exi->tcCallback = callback;
    if (exi->tcCallback != 0) {
        fn_80206E8C(chan, 0, 1, 0);
        __OSUnmaskInterrupts(0x200000u >> (chan * 3));
    }

    exi->state |= 1;
    regAddr = 0xCC006800;
    regAddr += chan * 20;
    *(volatile u32 *)(regAddr + 4) = (u32)buf & 0x03FFFFE0;
    *(volatile u32 *)(regAddr + 8) = len;
    *(volatile u32 *)(regAddr + 12) = (type << 2) | 3;
    OSRestoreInterrupts(enabled);
    return 1;
}
