typedef int BOOL;
typedef int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct EXIControl {
    void *exiCallback;
    void *tcCallback;
    char pad_08[4];
    volatile u32 state;
    s32 immLen;
    void *immBuf;
    char pad_18[0x28];
} EXIControl;

extern EXIControl Ecb_80640AA8[3];

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL);
extern u32 fn_8020A59C(void);

volatile u32 __EXIRegs[15] : 0xCC006800;
#define REG(chan, index) (__EXIRegs[(chan) * 5 + (index)])
#define STATE_IMM 2
#define STATE_BUSY 3
#define STATE_SELECTED 4

static inline void CompleteTransfer(s32 chan)
{
    EXIControl *exi;
    u8 *buf;
    u32 data;
    int i;
    int len;

    exi = &Ecb_80640AA8[chan];
    if (exi->state & STATE_BUSY) {
        if (exi->state & STATE_IMM) {
            if ((len = exi->immLen) != 0) {
                buf = exi->immBuf;
                data = REG(chan, 4);
                for (i = 0; i < len; i++) {
                    *buf++ = data >> ((3 - i) * 8);
                }
            }
        }
        exi->state &= ~STATE_BUSY;
    }
}

BOOL EXISync(s32 chan)
{
    EXIControl *exi;
    BOOL result;
    BOOL enabled;

    exi = &Ecb_80640AA8[chan];
    result = 0;

    while (exi->state & STATE_SELECTED) {
        if (!(REG(chan, 3) & 1)) {
            enabled = OSDisableInterrupts();
            if (exi->state & STATE_SELECTED) {
                CompleteTransfer(chan);
                if (fn_8020A59C() != 0xFF || exi->immLen != 4 ||
                    (REG(chan, 0) & 0x70) ||
                    (REG(chan, 4) != 0x01010000 &&
                     REG(chan, 4) != 0x05070000 &&
                     REG(chan, 4) != 0x04220001) ||
                    *(u16 *)0x800030E6 == 0x8200) {
                    result = 1;
                }
            }
            OSRestoreInterrupts(enabled);
            break;
        }
    }

    return result;
}
