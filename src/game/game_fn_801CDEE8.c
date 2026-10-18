typedef unsigned int u32;

extern void (*userCallback)(void);
extern volatile u32 salDspIsDone;
extern volatile u32 salLogicIsWaiting;
extern volatile u32 salLogicActive;

extern void OSEnableInterrupts(void);
extern void OSDisableInterrupts(void);

void dspResumeCallback(void)
{
    volatile u32 padding[2];

    salDspIsDone = 1;
    if (salLogicIsWaiting != 0) {
        salLogicIsWaiting = 0;
        if (salLogicActive == 0) {
            salLogicActive = 1;
            OSEnableInterrupts();
            userCallback();
            OSDisableInterrupts();
            salLogicActive = 0;
        }
    }
}
