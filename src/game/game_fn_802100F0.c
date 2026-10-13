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
extern OSThreadQueue RunQueue_80640E98[32];
extern volatile u32 RunQueueBits_8064D988;
extern volatile s32 RunQueueHint_8064D98C;

/* OSWakeupThread: move each waiter to its priority's ready queue. */
void fn_802100F0(OSThreadQueue *queue)
{
    s32 enabled;
    OSThread *thread;
    OSThread *next;
    OSThread *prev;

    enabled = OSDisableInterrupts();
    while ((thread = queue->head) != 0) {
        next = thread->next;
        if (next == 0) {
            queue->tail = 0;
        } else {
            next->prev = 0;
        }
        queue->head = next;
        thread->state = 1;
        if (thread->suspend <= 0) {
            thread->queue = &RunQueue_80640E98[thread->priority];
            prev = thread->queue->tail;
            if (prev == 0) {
                thread->queue->head = thread;
            } else {
                prev->next = thread;
            }
            thread->prev = prev;
            thread->next = 0;
            thread->queue->tail = thread;
            RunQueueBits_8064D988 |= 1u << (31 - thread->priority);
            RunQueueHint_8064D98C = 1;
        }
    }
    if (RunQueueHint_8064D98C) {
        SelectThread_8020F61C(0);
    }
    OSRestoreInterrupts(enabled);
}
