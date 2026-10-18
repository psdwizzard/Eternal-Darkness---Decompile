/* PAD origin callback: update the origin, enable polling, and reset the next channel. */
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

extern s32 SIGetResponse(s32 chan, void *data);          /* SIGetResponse */
extern void SISetCommand(s32 chan, u32 command);       /* SISetCommand */
extern u32 SIEnablePolling(u32 poll);                    /* SIEnablePolling */
extern u32 SIGetTypeAsync(s32 chan, SITypeCallback callback);
extern void PADTypeAndStatusCallback(s32 chan, u32 type);
extern void *memset(void *dst, int value, unsigned long size);

extern PadStatus Origin[4]; /* Origin */
extern s32 ResettingChan;          /* ResettingChan */
extern u32 AnalogMode;          /* AnalogMode */
extern u32 EnabledBits;          /* EnabledBits */
extern u32 ResettingBits;          /* ResettingBits */
extern void UpdateOrigin(s32 chan); /* PAD UpdateOrigin */

static void PADEnable(s32 chan)
{
    u32 cmd;
    u32 analogMode;
    u32 chanBit;
    u32 data[2];

    chanBit = 0x80000000U >> chan;
    EnabledBits |= chanBit;
    SIGetResponse(chan, data);
    analogMode = AnalogMode;
    cmd = analogMode | 0x400000;
    SISetCommand(chan, cmd);
    SIEnablePolling(EnabledBits);
}

void PADOriginCallback(s32 unused, u32 type, void *context)
{
    if (!(type & 0xF)) {
        UpdateOrigin(ResettingChan);
        PADEnable(ResettingChan);
    }
    {
        u32 chanBit;
        s32 chan;
        u32 bits = ResettingBits;

        ResettingChan = __cntlzw(bits);
        chan = ResettingChan;
        if (chan != 32) {
            chanBit = 0x80000000U >> chan;
            ResettingBits = bits & ~chanBit;
            memset(&Origin[chan], 0, sizeof(PadStatus));
            SIGetTypeAsync(ResettingChan, PADTypeAndStatusCallback);
        }
    }
}
