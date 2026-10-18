typedef unsigned int u32;
typedef signed int s32;
typedef void (*ARQCallback)(u32);

typedef struct ARQRequest ARQRequest;
struct ARQRequest {
    ARQRequest* next;
    u32 owner;
    u32 type;
    u32 priority;
    u32 source;
    u32 destination;
    u32 length;
    ARQCallback callback;
};

extern void ARStartDMA(u32 type, u32 mainMemory, u32 aram, u32 length);
extern void __ARQServiceQueueLo(void);
extern ARQRequest* __ARQRequestQueueHi;
extern ARQRequest* __ARQRequestPendingHi;
extern ARQRequest* __ARQRequestPendingLo;
extern ARQCallback __ARQCallbackHi;
extern ARQCallback __ARQCallbackLo;

/* ARQ DMA-complete interrupt: run the finished request's callback, then
 * start the next high-priority request or resume the low-priority chunks. */
void __ARQInterruptServiceRoutine(void)
{
    if (__ARQCallbackHi != 0) {
        __ARQCallbackHi((u32)__ARQRequestPendingHi);
        __ARQRequestPendingHi = 0;
        __ARQCallbackHi = 0;
    } else if (__ARQCallbackLo != 0) {
        __ARQCallbackLo((u32)__ARQRequestPendingLo);
        __ARQRequestPendingLo = 0;
        __ARQCallbackLo = 0;
    }

    if (__ARQRequestQueueHi != 0) {
        if (__ARQRequestQueueHi->type == 0) {
            ARStartDMA(__ARQRequestQueueHi->type, __ARQRequestQueueHi->source,
                        __ARQRequestQueueHi->destination, __ARQRequestQueueHi->length);
        } else {
            ARStartDMA(__ARQRequestQueueHi->type, __ARQRequestQueueHi->destination,
                        __ARQRequestQueueHi->source, __ARQRequestQueueHi->length);
        }
        __ARQCallbackHi = __ARQRequestQueueHi->callback;
        __ARQRequestPendingHi = __ARQRequestQueueHi;
        __ARQRequestQueueHi = __ARQRequestQueueHi->next;
    }

    if (__ARQRequestPendingHi == 0) {
        __ARQServiceQueueLo();
    }
}
