typedef int BOOL;
typedef void (*GXDrawDoneCallback)(void);

extern GXDrawDoneCallback lbl_8064DBB4;
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);

/* Install the draw-done callback and return the previous callback. */
GXDrawDoneCallback fn_802268E0(GXDrawDoneCallback callback)
{
    GXDrawDoneCallback previous = lbl_8064DBB4;
    BOOL enabled = OSDisableInterrupts();

    lbl_8064DBB4 = callback;
    OSRestoreInterrupts(enabled);
    return previous;
}
