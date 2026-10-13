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

typedef struct PadClampRegion {
    u8 minTrigger;
    u8 maxTrigger;
    s8 minStick;
    s8 maxStick;
    s8 xyStick;
    s8 minSubstick;
    s8 maxSubstick;
    s8 xySubstick;
} PadClampRegion;

extern PadClampRegion lbl_8064C420;
extern void fn_80218344(s8* px, s8* py, s8 max, s8 xy, s8 min);

/* Clamp all four controllers' sticks and triggers, applying their dead zones. */
void fn_80218474(PadStatus* status)
{
    s32 i;

    for (i = 0; i < 4; i++, status++) {
        if (status->err == 0) {
            fn_80218344(&status->stickX, &status->stickY,
                         lbl_8064C420.maxStick, lbl_8064C420.xyStick,
                         lbl_8064C420.minStick);
            fn_80218344(&status->substickX, &status->substickY,
                         lbl_8064C420.maxSubstick, lbl_8064C420.xySubstick,
                         lbl_8064C420.minSubstick);

            if (status->triggerL <= lbl_8064C420.minTrigger) {
                status->triggerL = 0;
            } else {
                if (lbl_8064C420.maxTrigger < status->triggerL) {
                    status->triggerL = lbl_8064C420.maxTrigger;
                }
                status->triggerL -= lbl_8064C420.minTrigger;
            }
            if (status->triggerR <= lbl_8064C420.minTrigger) {
                status->triggerR = 0;
            } else {
                if (lbl_8064C420.maxTrigger < status->triggerR) {
                    status->triggerR = lbl_8064C420.maxTrigger;
                }
                status->triggerR -= lbl_8064C420.minTrigger;
            }
        }
    }
}
