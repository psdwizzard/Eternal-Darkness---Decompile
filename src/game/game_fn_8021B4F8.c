typedef unsigned int u32;
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
extern ARQRequest* __ARQRequestQueueLo;
extern ARQRequest* __ARQRequestPendingLo;
extern ARQCallback __ARQCallbackLo;
extern u32 __ARQChunkSize;

/* Start the next chunk of the pending low-priority ARAM request. */
void __ARQServiceQueueLo(void)
{
    if (__ARQRequestPendingLo == 0 && __ARQRequestQueueLo != 0) {
        __ARQRequestPendingLo = __ARQRequestQueueLo;
        __ARQRequestQueueLo = __ARQRequestQueueLo->next;
    }
    if (__ARQRequestPendingLo != 0) {
        if (__ARQRequestPendingLo->length <= __ARQChunkSize) {
            if (__ARQRequestPendingLo->type == 0) {
                ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->source,
                            __ARQRequestPendingLo->destination, __ARQRequestPendingLo->length);
            } else {
                ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->destination,
                            __ARQRequestPendingLo->source, __ARQRequestPendingLo->length);
            }
            __ARQCallbackLo = __ARQRequestPendingLo->callback;
        } else {
            if (__ARQRequestPendingLo->type == 0) {
                ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->source,
                            __ARQRequestPendingLo->destination, __ARQChunkSize);
            } else {
                ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->destination,
                            __ARQRequestPendingLo->source, __ARQChunkSize);
            }
        }
        __ARQRequestPendingLo->length -= __ARQChunkSize;
        __ARQRequestPendingLo->source += __ARQChunkSize;
        __ARQRequestPendingLo->destination += __ARQChunkSize;
    }
}
