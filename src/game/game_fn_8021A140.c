typedef unsigned int u32;
typedef int BOOL;
typedef void (*AIStreamCallback)(u32 sampleCount);

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern AIStreamCallback __AIS_Callback;

/* AIRegisterStreamCallback: replace the stream callback and return the old one. */
AIStreamCallback AIRegisterStreamCallback(AIStreamCallback callback)
{
    AIStreamCallback previous = __AIS_Callback;
    BOOL level = OSDisableInterrupts();

    __AIS_Callback = callback;
    OSRestoreInterrupts(level);
    return previous;
}
