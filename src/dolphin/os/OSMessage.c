typedef int BOOL;
typedef int s32;
typedef void* OSMessage;

typedef struct OSThreadQueue {
    void* head;
    void* tail;
} OSThreadQueue;

typedef struct OSMessageQueue {
    OSThreadQueue queueSend;
    OSThreadQueue queueReceive;
    OSMessage* msgArray;
    s32 msgCount;
    s32 firstIndex;
    s32 usedCount;
} OSMessageQueue;

extern void OSInitThreadQueue(OSThreadQueue*);
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL);
extern void OSSleepThread(OSThreadQueue*);
extern void OSWakeupThread(OSThreadQueue*);

void OSInitMessageQueue(OSMessageQueue* mq, OSMessage* msgArray, s32 msgCount)
{
    OSInitThreadQueue(&mq->queueSend);
    OSInitThreadQueue(&mq->queueReceive);
    mq->msgArray = msgArray;
    mq->msgCount = msgCount;
    mq->firstIndex = 0;
    mq->usedCount = 0;
}

BOOL OSSendMessage(OSMessageQueue* mq, OSMessage msg, s32 flags)
{
    BOOL enabled = OSDisableInterrupts();

    while (mq->msgCount <= mq->usedCount) {
        if (!(flags & 1)) {
            OSRestoreInterrupts(enabled);
            return 0;
        }
        OSSleepThread(&mq->queueSend);
    }

    mq->msgArray[(mq->firstIndex + mq->usedCount) % mq->msgCount] = msg;
    mq->usedCount++;
    OSWakeupThread(&mq->queueReceive);
    OSRestoreInterrupts(enabled);
    return 1;
}

BOOL OSReceiveMessage(OSMessageQueue* mq, OSMessage* msg, s32 flags)
{
    BOOL enabled = OSDisableInterrupts();

    while (mq->usedCount == 0) {
        if (!(flags & 1)) {
            OSRestoreInterrupts(enabled);
            return 0;
        }
        OSSleepThread(&mq->queueReceive);
    }

    if (msg != 0) {
        *msg = mq->msgArray[mq->firstIndex];
    }
    mq->firstIndex = (mq->firstIndex + 1) % mq->msgCount;
    mq->usedCount--;
    OSWakeupThread(&mq->queueSend);
    OSRestoreInterrupts(enabled);
    return 1;
}

BOOL OSJamMessage(OSMessageQueue* mq, OSMessage msg, s32 flags)
{
    BOOL enabled = OSDisableInterrupts();

    while (mq->msgCount <= mq->usedCount) {
        if (!(flags & 1)) {
            OSRestoreInterrupts(enabled);
            return 0;
        }
        OSSleepThread(&mq->queueSend);
    }

    mq->firstIndex = (mq->firstIndex + mq->msgCount - 1) % mq->msgCount;
    mq->msgArray[mq->firstIndex] = msg;
    mq->usedCount++;
    OSWakeupThread(&mq->queueReceive);
    OSRestoreInterrupts(enabled);
    return 1;
}
