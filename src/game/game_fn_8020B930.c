typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);
extern void fn_8020B864(void);

void fn_8020B930(void)
{
    BOOL enabled = OSDisableInterrupts();

    fn_8020B864();
    OSRestoreInterrupts(enabled);
}
