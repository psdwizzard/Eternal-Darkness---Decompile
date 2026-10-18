/* fn_80219D80: Dolphin SDK PAD OnReset (PADSync, PADRecalibrate and DoReset inlined). */
#include "src/game/types.h"

typedef struct PADStatus {
    u16 button;
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
    u8 triggerL;
    u8 triggerR;
    u8 analogA;
    u8 analogB;
    s8 err;
} PADStatus;

typedef void (*SITypeCallback)(s32 chan, u32 type);
typedef void (*PADSamplingCallback)(void);

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern int SIBusy(void);                    /* SIBusy */
extern u32 SIDisablePolling(u32 mask);               /* SIDisablePolling */
extern u32 SIGetTypeAsync(s32 chan, SITypeCallback callback); /* SIGetTypeAsync */
extern PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback callback);        /* PADSetSamplingCallback */
extern void *memset(void *dst, int c, unsigned long n);
extern void PADTypeAndStatusCallback(s32 chan, u32 type);     /* PADTypeAndStatusCallback */

extern PADStatus Origin[4];   /* Origin */
extern s32 ResettingChan;            /* ResettingChan */
extern u32 EnabledBits;            /* EnabledBits */
extern u32 ResettingBits;          /* ResettingBits */
extern u32 RecalibrateBits;            /* RecalibrateBits */
extern u32 WaitingBits;            /* WaitingBits */
extern u32 CheckingBits;            /* CheckingBits */
extern u32 PendingBits;            /* PendingBits */
extern PADSamplingCallback SamplingCallback;          /* SamplingCallback */
extern int lbl_8064DAD0;            /* recalibrated */

/* Low-memory boot flag byte; bit 6 set means keep stored calibration. */
u8 __gUnknown800030E3 : 0x800030E3;

static inline int PADRecalibrate(u32 mask) {
    int enabled;
    u32 disableBits;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    mask |= PendingBits;
    PendingBits = 0;
    mask &= ~(WaitingBits | CheckingBits);
    ResettingBits |= mask;
    disableBits = ResettingBits & EnabledBits;
    EnabledBits &= ~mask;
    if (!(__gUnknown800030E3 & 0x40)) {
        RecalibrateBits |= mask;
    }
    SIDisablePolling(disableBits);
    if (ResettingChan == 32) {
        disableBits = ResettingBits;
        ResettingChan = __cntlzw(disableBits);
        if (ResettingChan != 32) {
            chanBit = 0x80000000U >> ResettingChan;
            ResettingBits = disableBits & ~chanBit;
            memset(&Origin[ResettingChan], 0, sizeof(PADStatus));
            SIGetTypeAsync(ResettingChan, PADTypeAndStatusCallback);
        }
    }
    OSRestoreInterrupts(enabled);
    return 1;
}

static inline int PADSync(void) {
    return ResettingBits == 0 && ResettingChan == 32 && !SIBusy();
}

int fn_80219D80(int final) {
    int sync;

    if (SamplingCallback) {
        PADSetSamplingCallback(0);
    }

    if (!final) {
        sync = PADSync();
        if (!lbl_8064DAD0 && sync) {
            lbl_8064DAD0 = PADRecalibrate(0xF0000000);
            return 0;
        }
        return sync;
    }
    lbl_8064DAD0 = 0;
    return 1;
}
