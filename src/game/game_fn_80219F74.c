#include "src/game/types.h"

typedef struct OSContext OSContext;
typedef void (*PADSamplingCallback)(void);
typedef void (*SIPollingHandler)(s32, u32);

extern PADSamplingCallback SamplingCallback;
extern void SamplingHandler(s16 interrupt, OSContext *context);
extern s32 SIRegisterPollingHandler(SIPollingHandler handler);
extern s32 SIUnregisterPollingHandler(SIPollingHandler handler);

/* Replace the PAD callback and update its SI polling handler. */
PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback callback)
{
    PADSamplingCallback previous = SamplingCallback;

    SamplingCallback = callback;
    if (callback != 0) {
        SIRegisterPollingHandler((SIPollingHandler)SamplingHandler);
    } else {
        SIUnregisterPollingHandler((SIPollingHandler)SamplingHandler);
    }
    return previous;
}
