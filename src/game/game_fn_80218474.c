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

extern PadClampRegion ClampRegion;
extern void ClampStick(s8* px, s8* py, s8 max, s8 xy, s8 min);

/* Clamp all four controllers' sticks and triggers, applying their dead zones. */
void PADClamp(PadStatus* status)
{
    s32 i;

    for (i = 0; i < 4; i++, status++) {
        if (status->err == 0) {
            ClampStick(&status->stickX, &status->stickY,
                         ClampRegion.maxStick, ClampRegion.xyStick,
                         ClampRegion.minStick);
            ClampStick(&status->substickX, &status->substickY,
                         ClampRegion.maxSubstick, ClampRegion.xySubstick,
                         ClampRegion.minSubstick);

            if (status->triggerL <= ClampRegion.minTrigger) {
                status->triggerL = 0;
            } else {
                if (ClampRegion.maxTrigger < status->triggerL) {
                    status->triggerL = ClampRegion.maxTrigger;
                }
                status->triggerL -= ClampRegion.minTrigger;
            }
            if (status->triggerR <= ClampRegion.minTrigger) {
                status->triggerR = 0;
            } else {
                if (ClampRegion.maxTrigger < status->triggerR) {
                    status->triggerR = ClampRegion.maxTrigger;
                }
                status->triggerR -= ClampRegion.minTrigger;
            }
        }
    }
}
