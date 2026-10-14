#include "src/game/types.h"

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32 level);

/* Read the video interface's DTV status with interrupts disabled. */
u32 fn_80218308(void)
{
    s32 level = OSDisableInterrupts();
    u32 status = *(volatile u16*)0xCC00206E & 3;

    OSRestoreInterrupts(level);
    return status & 1;
}
