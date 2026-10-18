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
volatile u32 __PIRegs[12] : 0xCC003000;

/* Acknowledge the PI debug interrupt and dispatch the channel 2 callback. */
void AmcDebugIntHandler(short interrupt, OSContext *context)
{
    EXICallback callback;

    __PIRegs[0] = (__PIRegs[0] & 0x1000) | 0x1000;
    callback = lbl_8064C4B8->exiCallback;
    if (callback != 0) {
        callback(2, context);
    }
}
