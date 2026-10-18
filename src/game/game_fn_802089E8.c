typedef signed int s32;
typedef unsigned int u32;

typedef void (*SIPollingHandler)(s32, u32);

extern SIPollingHandler RDSTHandler[4];

extern s32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(s32 enabled);
extern s32 SIEnablePollingInterrupt(s32 enable);

s32 SIRegisterPollingHandler(SIPollingHandler handler)
{
    s32 interrupts;
    s32 i;

    interrupts = OSDisableInterrupts();
    for (i = 0; i < 4; i++) {
        if (RDSTHandler[i] == handler) {
            OSRestoreInterrupts(interrupts);
            return 1;
        }
    }

    for (i = 0; i < 4; i++) {
        if (RDSTHandler[i] == 0) {
            RDSTHandler[i] = handler;
            SIEnablePollingInterrupt(1);
            OSRestoreInterrupts(interrupts);
            return 1;
        }
    }

    OSRestoreInterrupts(interrupts);
    return 0;
}
