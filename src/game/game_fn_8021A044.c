typedef int BOOL;
typedef void (*AIDMACallback)(void);

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern AIDMACallback lbl_8064DADC;

/* Replace the audio DMA callback and return the previous callback. */
AIDMACallback fn_8021A044(AIDMACallback callback)
{
    AIDMACallback previous = lbl_8064DADC;
    BOOL level = OSDisableInterrupts();

    lbl_8064DADC = callback;
    OSRestoreInterrupts(level);
    return previous;
}
