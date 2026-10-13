/* fn_80219D80: Dolphin SDK PAD OnReset (PADSync, PADRecalibrate and DoReset inlined). */
#include "src/game/types.h"

typedef struct PADStatus {
    u8 data[12];
} PADStatus;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern int fn_802082B4(void);                    /* SIBusy */
extern void fn_80209000(u32 mask);               /* SIDisablePolling */
extern int fn_80209858(s32 chan, void *callback); /* SIGetTypeAsync */
extern void *fn_80219F74(void *callback);        /* PADSetSamplingCallback */
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
extern void *lbl_8064DACC;          /* SamplingCallback */
extern int lbl_8064DAD0;            /* recalibrated */

/* Low-memory boot flag byte; bit 6 set means keep stored calibration. */
u8 __gUnknown800030E3 : 0x800030E3;

static inline void DoReset(void) {
    u32 chanBit;

    lbl_8064C428 = __cntlzw(lbl_8064DAB8);
    if (lbl_8064C428 != 32) {
        chanBit = 0x80000000 >> lbl_8064C428;
        lbl_8064DAB8 &= ~chanBit;
        memset(&lbl_80641C20[lbl_8064C428], 0, sizeof(PADStatus));
        fn_80209858(lbl_8064C428, fn_8021897C);
    }
}

static inline int PADRecalibrate(u32 mask) {
    int enabled;
    u32 disableBits;

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
        DoReset();
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
