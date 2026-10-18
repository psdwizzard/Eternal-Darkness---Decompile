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
extern u32 __OSMaskInterrupts(u32);
extern u32 __OSUnmaskInterrupts(u32);

/* Set the channel 2 EXI callback and return the previous callback. */
EXICallback AmcEXISetExiCallback(EXICallback callback)
{
    EXICallback previous;
    int enabled;

    enabled = OSDisableInterrupts();
    if (callback != 0) {
        __OSUnmaskInterrupts(0x40);
    } else {
        __OSMaskInterrupts(0x40);
    }
    previous = lbl_8064C4B8->exiCallback;
    lbl_8064C4B8->exiCallback = callback;
    OSRestoreInterrupts(enabled);
    return previous;
}
