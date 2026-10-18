typedef unsigned int u32;

extern void* salAIBufferBase;
extern void* AIRegisterDMACallback(void*);
extern void AIStopDMA(void);
extern void salFree(void*);

u32 salExitAi(void)
{
    AIRegisterDMACallback(0);
    AIStopDMA();
    salFree(salAIBufferBase);
    return 1;
}
