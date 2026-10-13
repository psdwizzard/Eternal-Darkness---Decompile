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
extern void OSClearContext(void *context);
extern void fn_8020D984(OSThread *thread);
extern void fn_8020F368(OSThread *thread);
extern s32 fn_8020F3D0(OSThread *thread);
extern OSThread *fn_8020F40C(OSThread *thread, s32 priority);
extern void fn_802100F0(OSThreadQueue *queue);
extern void SelectThread_8020F61C(s32 yield);
extern volatile s32 RunQueueHint_8064D98C;

#define OS_THREAD_STATE_READY 1
#define OS_THREAD_STATE_RUNNING 2
#define OS_THREAD_STATE_WAITING 4
#define OS_THREAD_STATE_MORIBUND 8
#define OS_THREAD_ATTR_DETACH 1

#define __OSActiveThreadQueue (*(OSThreadQueue *)0x800000DC)

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

void OSCancelThread(OSThread *thread)
{
    s32 enabled = OSDisableInterrupts();
    OSThread *next;
    OSThread *prev;

    switch (thread->state) {
    case OS_THREAD_STATE_READY:
        if (!(0 < thread->suspend)) {
            fn_8020F368(thread);
        }
        break;
    case OS_THREAD_STATE_RUNNING:
        RunQueueHint_8064D98C = 1;
        break;
    case OS_THREAD_STATE_WAITING:
        next = thread->next;
        prev = thread->prev;
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
        thread->queue = 0;
        if (!(0 < thread->suspend) && thread->mutex) {
            UpdatePriority(thread->mutex->owner);
        }
        break;
    default:
        OSRestoreInterrupts(enabled);
        return;
    }

    OSClearContext(&thread->context);
    if (thread->attr & OS_THREAD_ATTR_DETACH) {
        next = thread->activeNext;
        prev = thread->activePrev;
        if (next == 0) {
            __OSActiveThreadQueue.tail = prev;
        } else {
            next->activePrev = prev;
        }
        if (prev == 0) {
            __OSActiveThreadQueue.head = next;
        } else {
            prev->activeNext = next;
        }
        thread->state = 0;
    } else {
        thread->state = OS_THREAD_STATE_MORIBUND;
    }
    fn_8020D984(thread);
    fn_802100F0(&thread->joinQueue);
    if (RunQueueHint_8064D98C) {
        SelectThread_8020F61C(0);
    }
    OSRestoreInterrupts(enabled);
}
