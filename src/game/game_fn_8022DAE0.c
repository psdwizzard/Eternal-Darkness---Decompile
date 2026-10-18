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
extern u32 __OSUnmaskInterrupts(u32);
extern void AmcEXIClearInterrupts(int, int);

volatile u32 __EXIRegs[15] : 0xCC006800;
#define REG(chan, index) (__EXIRegs[(chan) * 5 + (index)])

/* Start an immediate EXI transfer on channel 2. */
int AmcEXIImm(void *buffer, s32 length, u32 type, EXICallback callback)
{
    s32 channel = 2;
    int enabled;
    u32 data;
    int i;

    enabled = OSDisableInterrupts();
    if ((lbl_8064C4B8->state & 3) || !(lbl_8064C4B8->state & 4)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    lbl_8064C4B8->transferCallback = callback;
    if (lbl_8064C4B8->transferCallback != 0) {
        AmcEXIClearInterrupts(0, 1);
        __OSUnmaskInterrupts(0x200000U >> (channel * 3));
    }
    lbl_8064C4B8->state |= 2;
    if (type != 0) {
        for (i = 0, data = 0; i < length; i++) {
            data |= ((u8 *)buffer)[i] << ((3 - i) * 8);
        }
        REG(channel, 4) = data;
    }
    lbl_8064C4B8->buffer = buffer;
    lbl_8064C4B8->length = type != 1 ? length : 0;
    REG(channel, 3) = ((type << 2) | 1) | ((length - 1) << 4);
    OSRestoreInterrupts(enabled);
    return 1;
}
