typedef unsigned long u32;
typedef long s32;
typedef struct OSContext OSContext;
typedef void (*EXICallback)(s32, OSContext *);

typedef struct EXIControl {
    EXICallback exiCallback;
    EXICallback transferCallback;
    EXICallback extCallback;
    volatile u32 state;
    s32 length;
    void *buffer;
} EXIControl;

extern EXIControl *lbl_8064C4B8;
extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int);

volatile u32 __EXIRegs[15] : 0xCC006800;
#define REG(chan, index) (__EXIRegs[(chan) * 5 + (index)])

/* Deselect the device on EXI channel 2. */
s32 fn_8022DFE8(void)
{
    volatile u32 *state;
    int enabled;

    enabled = OSDisableInterrupts();
    state = &lbl_8064C4B8->state;
    if (!(*state & 4)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    *state &= ~4;
    REG(2, 0) &= 0x405;
    OSRestoreInterrupts(enabled);
    return 1;
}
