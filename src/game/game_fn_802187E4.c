#include "src/game/types.h"

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32 enabled);
extern u32 fn_80209000(u32 poll);          /* SIDisablePolling */
extern void fn_8020EEA8(s32 chan, u16 id); /* OSSetWirelessID */
extern void fn_8021857C(s32 chan);         /* PAD UpdateOrigin */

extern u32 lbl_8064DAB4; /* EnabledBits */
extern u32 lbl_8064DAC0; /* WaitingBits */
extern u32 lbl_8064DAC4; /* CheckingBits */
extern u32 lbl_8064DAC8; /* PendingBits */

static inline void PADDisable(s32 chan)
{
    u32 enabled;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    chanBit = 0x80000000U >> chan;
    fn_80209000(chanBit);
    lbl_8064DAB4 &= ~chanBit;
    lbl_8064DAC0 &= ~chanBit;
    lbl_8064DAC4 &= ~chanBit;
    lbl_8064DAC8 &= ~chanBit;
    fn_8020EEA8(chan, 0);
    OSRestoreInterrupts(enabled);
}

/* PADOriginUpdateCallback: update the origin on success, or disable a
 * controller that is no longer present. */
void fn_802187E4(s32 chan, u32 error, void *context)
{
    u32 chanBit = 0x80000000U >> chan;

    if (lbl_8064DAB4 & chanBit) {
        if (!(error & 0xF)) {
            fn_8021857C(chan);
        }
        if (error & 8) {
            PADDisable(chan);
        }
    }
}
