typedef unsigned int u32;

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);
extern void* lbl_8064D4FC;

void fn_801CD504(void* value)
{
    u32 interrupts = OSDisableInterrupts();
    lbl_8064D4FC = value;
    OSRestoreInterrupts(interrupts);
}
