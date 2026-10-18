#include "src/game/types.h"

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32 enabled);
extern u32 SIDisablePolling(u32 poll);          /* SIDisablePolling */
extern void OSSetWirelessID(s32 chan, u16 id); /* OSSetWirelessID */
extern void UpdateOrigin(s32 chan);         /* PAD UpdateOrigin */

extern u32 EnabledBits; /* EnabledBits */
extern u32 WaitingBits; /* WaitingBits */
extern u32 CheckingBits; /* CheckingBits */
extern u32 PendingBits; /* PendingBits */

static inline void PADDisable(s32 chan)
{
    u32 enabled;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    chanBit = 0x80000000U >> chan;
    SIDisablePolling(chanBit);
    EnabledBits &= ~chanBit;
    WaitingBits &= ~chanBit;
    CheckingBits &= ~chanBit;
    PendingBits &= ~chanBit;
    OSSetWirelessID(chan, 0);
    OSRestoreInterrupts(enabled);
}

/* PADOriginUpdateCallback: update the origin on success, or disable a
 * controller that is no longer present. */
void PADOriginUpdateCallback(s32 chan, u32 error, void *context)
{
    u32 chanBit = 0x80000000U >> chan;

    if (EnabledBits & chanBit) {
        if (!(error & 0xF)) {
            UpdateOrigin(chan);
        }
        if (error & 8) {
            PADDisable(chan);
        }
    }
}
