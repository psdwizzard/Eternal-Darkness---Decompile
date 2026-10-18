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
extern u32 SIDisablePolling(u32 mask);
extern u32 SIGetTypeAsync(s32 chan, SITypeCallback callback);
extern void PADTypeAndStatusCallback(s32 chan, u32 type);
extern void *memset(void *dst, int value, unsigned long size);

extern PadStatus Origin[4]; /* Origin */
extern s32 ResettingChan;          /* ResettingChan */
extern u32 EnabledBits;          /* EnabledBits */
extern u32 ResettingBits;          /* ResettingBits */
extern u32 RecalibrateBits;          /* RecalibrateBits */
extern u32 WaitingBits;          /* WaitingBits */
extern u32 CheckingBits;          /* CheckingBits */
extern u32 PendingBits;          /* PendingBits */

extern u8 __PADBootFlags : 0x800030E3;

int PADRecalibrate(u32 mask)
{
    int enabled;
    u32 bits;

    enabled = OSDisableInterrupts();
    mask |= PendingBits;
    PendingBits = 0;
    mask &= ~(WaitingBits | CheckingBits);
    ResettingBits |= mask;
    bits = ResettingBits & EnabledBits;
    EnabledBits &= ~mask;

    /* The boot flag suppresses recalibration when bit 6 is set. */
    if (!(__PADBootFlags & 0x40)) {
        RecalibrateBits |= mask;
    }
    SIDisablePolling(bits);

    if (ResettingChan == 32) {
        bits = ResettingBits;
        ResettingChan = __cntlzw(bits);
        if (ResettingChan != 32) {
            ResettingBits = bits & ~(0x80000000U >> ResettingChan);
            memset(&Origin[ResettingChan], 0, sizeof(PadStatus));
            SIGetTypeAsync(ResettingChan, PADTypeAndStatusCallback);
        }
    }
    OSRestoreInterrupts(enabled);
    return 1;
}
