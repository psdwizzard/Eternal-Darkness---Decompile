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
extern s32 OSRestoreInterrupts(s32);
extern s32 fn_8020F3D0(OSThread *thread);
extern OSThread *fn_8020F40C(OSThread *thread, s32 priority);
extern void SelectThread_8020F61C(s32 yield);
extern void fn_8020F368(OSThread *thread);
extern volatile s32 RunQueueHint_8064D98C;

#define OS_THREAD_STATE_READY 1
#define OS_THREAD_STATE_RUNNING 2
#define OS_THREAD_STATE_WAITING 4

static inline void UpdatePriority(OSThread *thread)
{
    s32 priority;
    do {
        if (0 < thread->suspend) {
            break;
        }
        priority = fn_8020F3D0(thread);
        if (thread->priority == priority) {
            break;
        }
        thread = fn_8020F40C(thread, priority);
    } while (thread);
}

/* OSSuspendThread */
s32 fn_8020FE94(OSThread *thread)
{
    s32 enabled;
    s32 suspendCount;

    enabled = OSDisableInterrupts();
    suspendCount = thread->suspend++;
    if (suspendCount == 0) {
        switch (thread->state) {
        case OS_THREAD_STATE_RUNNING:
            RunQueueHint_8064D98C = 1;
            thread->state = OS_THREAD_STATE_READY;
            break;
        case OS_THREAD_STATE_READY:
            fn_8020F368(thread);
            break;
        case OS_THREAD_STATE_WAITING: {
            OSThread *next = thread->next;
            OSThread *prev = thread->prev;

            if (next == 0) {
                thread->queue->tail = prev;
            } else {
                next->prev = prev;
            }
            if (prev == 0) {
                thread->queue->head = next;
            } else {
                prev->next = next;
            }
            thread->priority = 32;
            prev = thread->queue->tail;
            if (prev == 0) {
                thread->queue->head = thread;
            } else {
                prev->next = thread;
            }
            thread->prev = prev;
            thread->next = 0;
            thread->queue->tail = thread;
            if (thread->mutex) {
                UpdatePriority(thread->mutex->owner);
            }
            break;
        }
        }
        if (RunQueueHint_8064D98C) {
            SelectThread_8020F61C(0);
        }
    }
    OSRestoreInterrupts(enabled);
    return suspendCount;
}
