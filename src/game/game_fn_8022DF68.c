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

/* Select device 0 on channel 2 at the given frequency (EXISelect). */
s32 fn_8022DF68(u32 freq)
{
    volatile u32 *state;
    int enabled;
    u32 cpr;

    enabled = OSDisableInterrupts();
    state = &lbl_8064C4B8->state;
    if (*state & 4) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    *state |= 4;
    cpr = REG(2, 0);
    cpr &= 0x405;
    cpr |= 0x80 | (freq << 4);
    REG(2, 0) = cpr;
    OSRestoreInterrupts(enabled);
    return 1;
}
