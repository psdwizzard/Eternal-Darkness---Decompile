typedef int BOOL;
typedef unsigned short u16;
typedef void (*GXBreakPtCallback)(u16 token);

extern GXBreakPtCallback lbl_8064DBB0;
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);

/* Replace the PE token callback and return the previous callback. */
GXBreakPtCallback fn_80226814(GXBreakPtCallback callback)
{
    GXBreakPtCallback previous = lbl_8064DBB0;
    BOOL enabled = OSDisableInterrupts();

    lbl_8064DBB0 = callback;
    OSRestoreInterrupts(enabled);
    return previous;
}
