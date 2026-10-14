typedef int s32;

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32 enabled);
extern s32 Reschedule_8064D990;

s32 OSEnableScheduler(void)
{
    s32 enabled = OSDisableInterrupts();
    s32 previous = Reschedule_8064D990--;

    OSRestoreInterrupts(enabled);
    return previous;
}
