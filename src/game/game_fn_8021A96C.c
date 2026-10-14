typedef int BOOL;
typedef void (*ARCallback)(void);

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern ARCallback lbl_8064DB18;

/* ARRegisterDMACallback */
ARCallback fn_8021A96C(ARCallback callback)
{
    ARCallback previous = lbl_8064DB18;
    BOOL enabled = OSDisableInterrupts();

    lbl_8064DB18 = callback;
    OSRestoreInterrupts(enabled);
    return previous;
}
