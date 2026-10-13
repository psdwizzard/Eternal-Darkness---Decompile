typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef struct OSThread OSThread;
typedef struct OSMutex OSMutex;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;
struct OSThread {
    unsigned char context[0x2C8];
    u16 state;
    u16 attr;
    s32 suspend;
    s32 priority;
    s32 basePriority;
    void *value;
    OSThreadQueue *queue;
    OSThread *next;
    OSThread *prev;
    OSThreadQueue joinQueue;
    OSMutex *mutex;
    OSMutex *mutexHead;
    OSMutex *mutexTail;
    OSThread *activeNext;
    OSThread *activePrev;
    void *stackBase;
    u32 *stackEnd;
};
struct OSMutex {
    OSThreadQueue queue;
    OSThread *owner;
    s32 count;
    OSMutex *next;
    OSMutex *prev;
};

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32 enabled);
extern void SelectThread_8020F61C(s32 yield);
extern volatile s32 RunQueueHint_8064D98C;

#define OSGetCurrentThread() (*(OSThread **)0x800000E4)

/* OSSleepThread: put the current thread to sleep on queue, priority-ordered. */
void fn_80210004(OSThreadQueue *queue)
{
    s32 enabled;
    OSThread *currentThread;
    OSThread *prev;
    OSThread *next;

    enabled = OSDisableInterrupts();
    currentThread = OSGetCurrentThread();
    currentThread->state = 4;
    currentThread->queue = queue;
    for (next = queue->head; next && next->priority <= currentThread->priority; next = next->next) {
    }
    if (next == 0) {
        prev = queue->tail;
        if (prev == 0) {
            queue->head = currentThread;
        } else {
            prev->next = currentThread;
        }
        currentThread->prev = prev;
        currentThread->next = 0;
        queue->tail = currentThread;
    } else {
        currentThread->next = next;
        prev = next->prev;
        next->prev = currentThread;
        currentThread->prev = prev;
        if (prev == 0) {
            queue->head = currentThread;
        } else {
            prev->next = currentThread;
        }
    }
    RunQueueHint_8064D98C = 1;
    if (RunQueueHint_8064D98C) {
        SelectThread_8020F61C(0);
    }
    OSRestoreInterrupts(enabled);
}
