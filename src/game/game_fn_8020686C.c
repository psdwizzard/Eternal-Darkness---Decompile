typedef int BOOL;
typedef int s32;
typedef unsigned char u8;
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

#define EXI_REGS ((volatile u32 *)0xCC006800)

BOOL EXIImm(s32 chan, void *buf, s32 len, u32 type, void *callback)
{
    BOOL enabled;
    EXIControl *exi;
    u32 data;
    u32 regAddr;
    s32 i;

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

    exi->state |= 2;
    if (type != 0) {
        i = 0;
        data = 0;
        while (i < len) {
            data |= ((u8 *)buf)[i] << ((3 - i) * 8);
            i++;
        }
        regAddr = 0xCC006800;
        regAddr += chan * 20;
        *(volatile u32 *)(regAddr + 16) = data;
    }

    exi->immBuf = buf;
    regAddr = chan * 20;
    exi->immLen = type != 1 ? len : 0;
    data = (type << 2) | 1;
    data |= (len - 1) << 4;
    regAddr += 0xCC006800;
    *(volatile u32 *)(regAddr + 12) = data;
    OSRestoreInterrupts(enabled);
    return 1;
}
