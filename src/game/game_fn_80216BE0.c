typedef unsigned int u32;
typedef int BOOL;
typedef void (*VIRetraceCallback)(u32 retraceCount);

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern VIRetraceCallback lbl_8064DA74;

/* Set the post-retrace callback and return the previous callback. */
VIRetraceCallback fn_80216BE0(VIRetraceCallback callback)
{
    VIRetraceCallback previous = lbl_8064DA74;
    BOOL level = OSDisableInterrupts();

    lbl_8064DA74 = callback;
    OSRestoreInterrupts(level);
    return previous;
}
