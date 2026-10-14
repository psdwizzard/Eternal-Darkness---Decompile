typedef signed int s32;
typedef unsigned short u16;

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32 enable);

volatile u16 DSPRegisters[] : 0xCC005000;

/* Assert the DSP interrupt request while preserving the interrupt state. */
void fn_8021B9E0(void)
{
    s32 enabled;
    u16 status;

    enabled = OSDisableInterrupts();
    status = DSPRegisters[5];
    DSPRegisters[5] = (status & ~0xA8) | 4;
    OSRestoreInterrupts(enabled);
}
