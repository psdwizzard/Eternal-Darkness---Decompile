typedef unsigned char u8;
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

/* Copy the result of a finished channel 2 immediate transfer. */
static inline void CompleteTransfer(s32 chan)
{
    EXIControl *exi;
    volatile u32 *state;
    u8 *buf;
    u32 data;
    int i;
    int len;

    exi = lbl_8064C4B8;
    state = &exi->state;
    if (*state & 3) {
        if (*state & 2) {
            if ((len = exi->length) != 0) {
                buf = exi->buffer;
                data = REG(chan, 4);
                for (i = 0; i < len; i++) {
                    *buf++ = data >> ((3 - i) * 8);
                }
            }
        }
        lbl_8064C4B8->state &= ~3;
    }
}

/* Wait for the channel 2 immediate transfer to finish. */
void AmcEXISync(void)
{
    s32 chan = 2;
    EXIControl *exi = lbl_8064C4B8;
    int enabled;

    while (exi->state & 4) {
        if (!(REG(chan, 3) & 1)) {
            enabled = OSDisableInterrupts();
            CompleteTransfer(chan);
            OSRestoreInterrupts(enabled);
            return;
        }
    }
}
