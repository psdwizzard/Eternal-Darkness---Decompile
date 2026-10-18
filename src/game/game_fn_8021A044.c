typedef int BOOL;
typedef void (*AIDMACallback)(void);

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern AIDMACallback __AID_Callback;

/* Replace the audio DMA callback and return the previous callback. */
AIDMACallback AIRegisterDMACallback(AIDMACallback callback)
{
    AIDMACallback previous = __AID_Callback;
    BOOL level = OSDisableInterrupts();

    __AID_Callback = callback;
    OSRestoreInterrupts(level);
    return previous;
}
