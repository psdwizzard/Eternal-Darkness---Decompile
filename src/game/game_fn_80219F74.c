#include "src/game/types.h"

typedef struct OSContext OSContext;
typedef void (*PADSamplingCallback)(void);
typedef void (*SIPollingHandler)(s32, u32);

extern PADSamplingCallback lbl_8064DACC;
extern void fn_80219F14(s16 interrupt, OSContext *context);
extern s32 fn_802089E8(SIPollingHandler handler);
extern s32 fn_80208AB4(SIPollingHandler handler);

/* Replace the PAD callback and update its SI polling handler. */
PADSamplingCallback fn_80219F74(PADSamplingCallback callback)
{
    PADSamplingCallback previous = lbl_8064DACC;

    lbl_8064DACC = callback;
    if (callback != 0) {
        fn_802089E8((SIPollingHandler)fn_80219F14);
    } else {
        fn_80208AB4((SIPollingHandler)fn_80219F14);
    }
    return previous;
}
