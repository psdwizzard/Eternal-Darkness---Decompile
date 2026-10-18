typedef unsigned char u8;
typedef unsigned int u32;

extern void (*userCallback)(void);
extern void* salAIBufferBase;
extern u32 salDspIsDone;
extern volatile u32 salLogicIsWaiting;
extern volatile u32 salLogicActive;
extern u8 salAIBufferIndex;
extern u8 synthInfo[];

extern void* salMalloc(u32);
extern void salCallback(void);
extern void* memset(void*, int, u32);
extern void DCFlushRange(void*, u32);
extern void* AIRegisterDMACallback(void*);
extern void AIInitDMA(void*, u32);

u32 salInitAi(void (*callback)(void), u32 unused, u32* config)
{
    void* allocation;
    char* base;

    allocation = salMalloc(0xA00);
    salAIBufferBase = allocation;
    if (allocation != 0) {
        memset(salAIBufferBase, 0, 0xA00);
        DCFlushRange(salAIBufferBase, 0xA00);
        userCallback = callback;
        salDspIsDone = 1;
        salAIBufferIndex = 1;
        salLogicActive = salLogicIsWaiting = 0;
        AIRegisterDMACallback((void*)salCallback);
        base = (char*)((u32)salAIBufferBase + 0x80000000U);
        AIInitDMA(base + salAIBufferIndex * 0x280, 0x280);
        *(u32*)(synthInfo + 4) = 0x20;
        *config = 32000;
        return 1;
    }
    return 0;
}
