extern volatile int lbl_8064CFE0;
extern volatile int lbl_8064CFE4;
extern volatile int lbl_8064CFE8;
extern unsigned char lbl_805E2ABC[];

extern void fn_80138F78(int);
extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);
extern void OSSendMessage(void*, int, int);

void fn_80139940(int cleanup)
{
    int wake;
    int enabled;

    if (cleanup != 0) {
        fn_80138F78(0);
    }
    wake = 0;
    enabled = OSDisableInterrupts();
    lbl_8064CFE8--;
    if (lbl_8064CFE8 == 0) {
        lbl_8064CFE4 = 0;
        if (lbl_8064CFE0 != 0) {
            wake = 1;
        }
    }
    OSRestoreInterrupts(enabled);
    if (wake != 0) {
        OSSendMessage(lbl_805E2ABC, 0, 1);
    }
}
