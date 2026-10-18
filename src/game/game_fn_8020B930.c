typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);
extern void __LCEnable(void);

void LCEnable(void)
{
    BOOL enabled = OSDisableInterrupts();

    __LCEnable();
    OSRestoreInterrupts(enabled);
}
