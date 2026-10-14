typedef int BOOL;
typedef unsigned int u32;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u32 CurrTvMode_8064DAA4;

u32 VIGetTvFormat(void)
{
    BOOL enabled;
    u32 format;

    enabled = OSDisableInterrupts();
    switch (CurrTvMode_8064DAA4) {
    case 0:
    case 3:
        format = 0;
        break;
    case 1:
    case 4:
        format = 1;
        break;
    case 2:
    case 5:
        format = CurrTvMode_8064DAA4;
        break;
    }
    OSRestoreInterrupts(enabled);
    return format;
}
