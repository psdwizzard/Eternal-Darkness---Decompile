typedef signed int s32;
typedef unsigned int u32;

typedef void (*SICallback)(s32 chan, u32 error, void *context);

typedef struct SIControl {
    s32 chan;
    u32 poll;
    u32 inputBytes;
    void *input;
    SICallback callback;
} SIControl;

typedef union SIComCSR {
    u32 value;
    struct {
        u32 TCINT : 1;
        u32 TCINTMSK : 1;
        u32 COMERR : 1;
        u32 RDSTINT : 1;
        u32 RDSTINTMSK : 1;
        u32 reserved0 : 3;
        u32 reserved1 : 1;
        u32 OUTLNGTH : 7;
        u32 reserved2 : 1;
        u32 INLNGTH : 7;
        u32 reserved3 : 5;
        u32 CHANNEL : 2;
        u32 TSTART : 1;
    } field;
} SIComCSR;

extern SIControl Si_802FCA20;
extern u32 __SIRegs[64] : 0xCC006400;

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32 enabled);

s32 __SITransfer(s32 chan, void *output, u32 outputBytes, void *input,
                u32 inputBytes, SICallback callback)
{
    register SIControl *si = &Si_802FCA20;
    u32 enabled = OSDisableInterrupts();
    u32 i;
    SIComCSR comcsr;
    u32 status;

    if (si->chan != -1) {
        OSRestoreInterrupts(enabled);
        return 0;
    }

    status = __SIRegs[14];
    status &= ((s32)0x0F000000 >> (chan * 8));
    __SIRegs[14] = status;
    si->chan = chan;
    si->callback = callback;
    si->inputBytes = inputBytes;
    si->input = input;

    for (i = 0; i < (outputBytes + 3) / 4; i++) {
        __SIRegs[32 + i] = ((u32 *)output)[i];
    }

    comcsr.value = __SIRegs[13];
    comcsr.field.TCINT = 1;
    i = callback ? 1 : 0;
    comcsr.field.TCINTMSK = i;
    comcsr.field.OUTLNGTH = outputBytes == 128 ? 0 : outputBytes;
    comcsr.field.INLNGTH = inputBytes == 128 ? 0 : inputBytes;
    comcsr.field.CHANNEL = chan;
    comcsr.field.TSTART = 1;
    __SIRegs[13] = comcsr.value;

    OSRestoreInterrupts(enabled);
    return 1;
}
