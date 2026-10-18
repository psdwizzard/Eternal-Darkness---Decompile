typedef int BOOL;
typedef void (*GXDrawDoneCallback)(void);

extern GXDrawDoneCallback DrawDoneCB;
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);

/* Install the draw-done callback and return the previous callback. */
GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback callback)
{
    GXDrawDoneCallback previous = DrawDoneCB;
    BOOL enabled = OSDisableInterrupts();

    DrawDoneCB = callback;
    OSRestoreInterrupts(enabled);
    return previous;
}
