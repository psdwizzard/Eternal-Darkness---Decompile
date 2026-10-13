/* PADRecalibrate: queue controller resets and refresh their origins. */
#include "src/game/types.h"

typedef struct PadStatus {
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
} PadStatus;

typedef void (*SITypeCallback)(s32 chan, u32 type);

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);
extern u32 fn_80209000(u32 mask);
extern u32 fn_80209858(s32 chan, SITypeCallback callback);
extern void fn_8021897C(s32 chan, u32 type);
extern void *memset(void *dst, int value, unsigned long size);

extern PadStatus lbl_80641C20[4]; /* Origin */
extern s32 lbl_8064C428;          /* ResettingChan */
extern u32 lbl_8064DAB4;          /* EnabledBits */
extern u32 lbl_8064DAB8;          /* ResettingBits */
extern u32 lbl_8064DABC;          /* RecalibrateBits */
extern u32 lbl_8064DAC0;          /* WaitingBits */
extern u32 lbl_8064DAC4;          /* CheckingBits */
extern u32 lbl_8064DAC8;          /* PendingBits */

extern u8 __PADBootFlags : 0x800030E3;

int fn_80218EDC(u32 mask)
{
    int enabled;
    u32 bits;

    enabled = OSDisableInterrupts();
    mask |= lbl_8064DAC8;
    lbl_8064DAC8 = 0;
    mask &= ~(lbl_8064DAC0 | lbl_8064DAC4);
    lbl_8064DAB8 |= mask;
    bits = lbl_8064DAB8 & lbl_8064DAB4;
    lbl_8064DAB4 &= ~mask;

    /* The boot flag suppresses recalibration when bit 6 is set. */
    if (!(__PADBootFlags & 0x40)) {
        lbl_8064DABC |= mask;
    }
    fn_80209000(bits);

    if (lbl_8064C428 == 32) {
        bits = lbl_8064DAB8;
        lbl_8064C428 = __cntlzw(bits);
        if (lbl_8064C428 != 32) {
            lbl_8064DAB8 = bits & ~(0x80000000U >> lbl_8064C428);
            memset(&lbl_80641C20[lbl_8064C428], 0, sizeof(PadStatus));
            fn_80209858(lbl_8064C428, fn_8021897C);
        }
    }
    OSRestoreInterrupts(enabled);
    return 1;
}
