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

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32 enable);
extern void ARStartDMA(u32 type, u32 mainMemory, u32 aram, u32 length);
extern void __ARQServiceQueueLo(void);
extern void __ARQCallbackHack(u32 request);
extern ARQRequest* __ARQRequestQueueHi;
extern ARQRequest* __ARQRequestTailHi;
extern ARQRequest* __ARQRequestQueueLo;
extern ARQRequest* __ARQRequestTailLo;
extern ARQRequest* __ARQRequestPendingHi;
extern ARQRequest* __ARQRequestPendingLo;
extern ARQCallback __ARQCallbackHi;

/* Post an ARAM DMA request to the queue for its priority. */
void ARQPostRequest(ARQRequest* request, u32 owner, u32 type, s32 priority,
                 u32 source, u32 destination, u32 length, ARQCallback callback)
{
    s32 enabled;

    request->next = 0;
    request->owner = owner;
    request->type = type;
    request->source = source;
    request->destination = destination;
    request->length = length;
    if (callback != 0) {
        request->callback = callback;
    } else {
        request->callback = __ARQCallbackHack;
    }

    enabled = OSDisableInterrupts();
    switch (priority) {
    case 0:
        if (__ARQRequestQueueLo != 0) {
            __ARQRequestTailLo->next = request;
        } else {
            __ARQRequestQueueLo = request;
        }
        __ARQRequestTailLo = request;
        break;
    case 1:
        if (__ARQRequestQueueHi != 0) {
            __ARQRequestTailHi->next = request;
        } else {
            __ARQRequestQueueHi = request;
        }
        __ARQRequestTailHi = request;
        break;
    }

    if (__ARQRequestPendingHi == 0 && __ARQRequestPendingLo == 0) {
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
    OSRestoreInterrupts(enabled);
}
