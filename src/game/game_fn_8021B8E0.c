typedef signed short s16;
typedef signed int s32;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct OSContext OSContext;
typedef struct DSPTask DSPTask;
typedef void (*OSInterruptHandler)(s16, OSContext *);

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32 enable);
extern OSInterruptHandler __OSSetInterruptHandler(s16 interrupt, OSInterruptHandler handler);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern void __DSP_debug_printf(char *format, ...);
extern void __DSPHandler(s16 interrupt, OSContext *context);
extern char lbl_802FE9E8[];
extern s32 __DSP_init_flag;
extern DSPTask *__DSP_tmp_task;
extern DSPTask *__DSP_last_task;
extern DSPTask *__DSP_first_task;
extern DSPTask *__DSP_curr_task;

volatile u16 DSPRegisters[] : 0xCC005000;

/* Initialize the DSP interrupt handler and task queue once. */
void DSPInit(void)
{
    s32 enabled;
    u16 status;

    __DSP_debug_printf(lbl_802FE9E8, lbl_802FE9E8 + 0x20, lbl_802FE9E8 + 0x2C);
    if (__DSP_init_flag == 1) {
        return;
    }

    enabled = OSDisableInterrupts();
    __OSSetInterruptHandler(7, __DSPHandler);
    __OSUnmaskInterrupts(0x01000000);
    DSPRegisters[5] = (DSPRegisters[5] & ~0xA8) | 0x800;
    status = DSPRegisters[5];
    DSPRegisters[5] = status & ~0xAC;
    __DSP_tmp_task = 0;
    __DSP_curr_task = 0;
    __DSP_last_task = 0;
    __DSP_first_task = 0;
    __DSP_init_flag = 1;
    OSRestoreInterrupts(enabled);
}
