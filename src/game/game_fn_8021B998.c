typedef signed int s32;
typedef unsigned short u16;

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32 enable);
extern s32 __DSP_init_flag;

volatile u16 DSPRegisters[] : 0xCC005000;

/* Reset the DSP and clear its initialization state. */
void DSPReset(void)
{
    s32 enabled;
    u16 status;

    enabled = OSDisableInterrupts();
    status = DSPRegisters[5];
    DSPRegisters[5] = (status & ~0xA8) | 0x801;
    __DSP_init_flag = 0;
    OSRestoreInterrupts(enabled);
}
