typedef int BOOL;
typedef void (*ARCallback)(void);

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern ARCallback __AR_Callback;

/* ARRegisterDMACallback */
ARCallback ARRegisterDMACallback(ARCallback callback)
{
    ARCallback previous = __AR_Callback;
    BOOL enabled = OSDisableInterrupts();

    __AR_Callback = callback;
    OSRestoreInterrupts(enabled);
    return previous;
}
