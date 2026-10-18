typedef unsigned int u32;
typedef signed int s32;
typedef struct ARQRequest ARQRequest;
typedef void (*ARQCallback)(u32);
typedef void (*ARCallback)(void);

extern ARCallback ARRegisterDMACallback(ARCallback callback);
extern void __ARQInterruptServiceRoutine(void);
extern ARQRequest* __ARQRequestQueueHi;
extern ARQRequest* __ARQRequestQueueLo;
extern ARQRequest* __ARQRequestPendingHi;
extern ARQRequest* __ARQRequestPendingLo;
extern ARQCallback __ARQCallbackHi;
extern ARQCallback __ARQCallbackLo;
extern u32 __ARQChunkSize;
extern s32 __ARQ_init_flag;

/* Initialize the ARAM request queues and install the DMA completion handler. */
void ARQInit(void)
{
    if (__ARQ_init_flag == 1) {
        return;
    }

    __ARQRequestQueueLo = 0;
    __ARQRequestQueueHi = 0;
    __ARQChunkSize = 0x1000;
    ARRegisterDMACallback(__ARQInterruptServiceRoutine);
    __ARQRequestPendingHi = 0;
    __ARQRequestPendingLo = 0;
    __ARQCallbackHi = 0;
    __ARQCallbackLo = 0;
    __ARQ_init_flag = 1;
}
