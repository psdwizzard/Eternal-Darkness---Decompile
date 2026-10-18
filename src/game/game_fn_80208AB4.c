typedef signed int s32;
typedef unsigned int u32;

typedef void (*SIPollingHandler)(s32, u32);

extern SIPollingHandler RDSTHandler[4];

extern s32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(s32 enabled);
extern s32 SIEnablePollingInterrupt(s32 enable);

s32 SIUnregisterPollingHandler(SIPollingHandler handler)
{
    s32 interrupts;
    s32 i;

    interrupts = OSDisableInterrupts();
    for (i = 0; i < 4; i++) {
        if (RDSTHandler[i] == handler) {
            RDSTHandler[i] = 0;

            for (i = 0; i < 4; i++) {
                if (RDSTHandler[i] != 0) {
                    break;
                }
            }

            if (i == 4) {
                SIEnablePollingInterrupt(0);
            }

            OSRestoreInterrupts(interrupts);
            return 1;
        }
    }

    OSRestoreInterrupts(interrupts);
    return 0;
}
