typedef int BOOL;
typedef unsigned short u16;
typedef void (*GXBreakPtCallback)(u16 token);

extern GXBreakPtCallback TokenCB;
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);

/* Replace the PE token callback and return the previous callback. */
GXBreakPtCallback GXSetDrawSyncCallback(GXBreakPtCallback callback)
{
    GXBreakPtCallback previous = TokenCB;
    BOOL enabled = OSDisableInterrupts();

    TokenCB = callback;
    OSRestoreInterrupts(enabled);
    return previous;
}
