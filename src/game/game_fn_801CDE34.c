typedef unsigned int u32;
typedef unsigned char u8;

extern void* salAIBufferBase;
extern volatile u32 salDspIsDone;
extern u32 salLogicIsWaiting;
extern u32 salLogicActive;
extern volatile u32 salLastTick;
extern void (*userCallback)(void);
extern u8 salAIBufferIndex;

extern void AIInitDMA(void*, u32);
extern u32 OSGetTick(void);
extern void OSEnableInterrupts(void);
extern void OSDisableInterrupts(void);

void salCallback(void)
{
    char* base;

    salAIBufferIndex = (salAIBufferIndex + 1) % 4;
    base = (char*)salAIBufferBase + 0x80000000;
    AIInitDMA(base + salAIBufferIndex * 640, 640);
    salLastTick = OSGetTick();
    if (salDspIsDone != 0) {
        if (salLogicActive == 0) {
            salLogicActive = 1;
            OSEnableInterrupts();
            userCallback();
            OSDisableInterrupts();
            salLogicActive = 0;
        }
    } else {
        salLogicIsWaiting = 1;
    }
}
