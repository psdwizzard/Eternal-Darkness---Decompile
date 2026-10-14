typedef unsigned int u32;
typedef int BOOL;
typedef void (*AIStreamCallback)(u32 sampleCount);

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern AIStreamCallback lbl_8064DAD8;

/* AIRegisterStreamCallback: replace the stream callback and return the old one. */
AIStreamCallback fn_8021A140(AIStreamCallback callback)
{
    AIStreamCallback previous = lbl_8064DAD8;
    BOOL level = OSDisableInterrupts();

    lbl_8064DAD8 = callback;
    OSRestoreInterrupts(level);
    return previous;
}
