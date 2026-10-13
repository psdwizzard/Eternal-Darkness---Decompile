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
extern void fn_8021BAA0(char *format, ...);
extern void fn_8021BAF0(s16 interrupt, OSContext *context);
extern char lbl_802FE9E8[];
extern s32 lbl_8064DB60;
extern DSPTask *lbl_8064DB70;
extern DSPTask *lbl_8064DB74;
extern DSPTask *lbl_8064DB78;
extern DSPTask *lbl_8064DB7C;

volatile u16 DSPRegisters[] : 0xCC005000;

/* Initialize the DSP interrupt handler and task queue once. */
void fn_8021B8E0(void)
{
    s32 enabled;
    u16 status;

    fn_8021BAA0(lbl_802FE9E8, lbl_802FE9E8 + 0x20, lbl_802FE9E8 + 0x2C);
    if (lbl_8064DB60 == 1) {
        return;
    }

    enabled = OSDisableInterrupts();
    __OSSetInterruptHandler(7, fn_8021BAF0);
    __OSUnmaskInterrupts(0x01000000);
    DSPRegisters[5] = (DSPRegisters[5] & ~0xA8) | 0x800;
    status = DSPRegisters[5];
    DSPRegisters[5] = status & ~0xAC;
    lbl_8064DB70 = 0;
    lbl_8064DB7C = 0;
    lbl_8064DB74 = 0;
    lbl_8064DB78 = 0;
    lbl_8064DB60 = 1;
    OSRestoreInterrupts(enabled);
}
