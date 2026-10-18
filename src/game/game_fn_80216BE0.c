typedef unsigned int u32;
typedef int BOOL;
typedef void (*VIRetraceCallback)(u32 retraceCount);

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern VIRetraceCallback PostCB;

/* Set the post-retrace callback and return the previous callback. */
VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback callback)
{
    VIRetraceCallback previous = PostCB;
    BOOL level = OSDisableInterrupts();

    PostCB = callback;
    OSRestoreInterrupts(level);
    return previous;
}
