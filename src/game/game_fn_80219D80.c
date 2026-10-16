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
extern int fn_802082B4(void);                    /* SIBusy */
extern u32 fn_80209000(u32 mask);               /* SIDisablePolling */
extern u32 fn_80209858(s32 chan, SITypeCallback callback); /* SIGetTypeAsync */
extern PADSamplingCallback fn_80219F74(PADSamplingCallback callback);        /* PADSetSamplingCallback */
extern void *memset(void *dst, int c, unsigned long n);
extern void fn_8021897C(s32 chan, u32 type);     /* PADTypeAndStatusCallback */

extern PADStatus lbl_80641C20[4];   /* Origin */
extern s32 lbl_8064C428;            /* ResettingChan */
extern u32 lbl_8064DAB4;            /* EnabledBits */
extern u32 lbl_8064DAB8;          /* ResettingBits */
extern u32 lbl_8064DABC;            /* RecalibrateBits */
extern u32 lbl_8064DAC0;            /* WaitingBits */
extern u32 lbl_8064DAC4;            /* CheckingBits */
extern u32 lbl_8064DAC8;            /* PendingBits */
extern PADSamplingCallback lbl_8064DACC;          /* SamplingCallback */
extern int lbl_8064DAD0;            /* recalibrated */

/* Low-memory boot flag byte; bit 6 set means keep stored calibration. */
u8 __gUnknown800030E3 : 0x800030E3;

static inline int PADRecalibrate(u32 mask) {
    int enabled;
    u32 disableBits;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    mask |= lbl_8064DAC8;
    lbl_8064DAC8 = 0;
    mask &= ~(lbl_8064DAC0 | lbl_8064DAC4);
    lbl_8064DAB8 |= mask;
    disableBits = lbl_8064DAB8 & lbl_8064DAB4;
    lbl_8064DAB4 &= ~mask;
    if (!(__gUnknown800030E3 & 0x40)) {
        lbl_8064DABC |= mask;
    }
    fn_80209000(disableBits);
    if (lbl_8064C428 == 32) {
        disableBits = lbl_8064DAB8;
        lbl_8064C428 = __cntlzw(disableBits);
        if (lbl_8064C428 != 32) {
            chanBit = 0x80000000U >> lbl_8064C428;
            lbl_8064DAB8 = disableBits & ~chanBit;
            memset(&lbl_80641C20[lbl_8064C428], 0, sizeof(PADStatus));
            fn_80209858(lbl_8064C428, fn_8021897C);
        }
    }
    OSRestoreInterrupts(enabled);
    return 1;
}

static inline int PADSync(void) {
    return lbl_8064DAB8 == 0 && lbl_8064C428 == 32 && !fn_802082B4();
}

int fn_80219D80(int final) {
    int sync;

    if (lbl_8064DACC) {
        fn_80219F74(0);
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
