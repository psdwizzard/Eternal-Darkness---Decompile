typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef struct OSThread OSThread;
typedef struct OSMutex OSMutex;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;
typedef struct OSThreadLink {
    OSThread *next;
    OSThread *prev;
} OSThreadLink;
struct OSThread {
    unsigned char context[0x2C8];
    u16 state;
    u16 attr;
    s32 suspend;
    s32 priority;
    s32 basePriority;
    void *value;
    OSThreadQueue *queue;
    OSThreadLink link;
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
    OSThread *thread;
    s32 count;
    OSMutex *next;
    OSMutex *prev;
};

#define OS_THREAD_STATE_READY 1
#define OS_THREAD_STATE_RUNNING 2
#define OS_THREAD_STATE_WAITING 4

extern void UnsetRun(OSThread *thread);
extern volatile u32 RunQueueBits_8064D988;
extern volatile s32 RunQueueHint_8064D98C;
extern OSThreadQueue RunQueue_80640E98[32];

#define AddTail(queue, thread, link)                \
    do {                                            \
        OSThread *prev;                             \
                                                    \
        prev = (queue)->tail;                       \
        if (prev == 0)                              \
            (queue)->head = (thread);               \
        else                                        \
            prev->link.next = (thread);             \
        (thread)->link.prev = prev;                 \
        (thread)->link.next = 0;                    \
        (queue)->tail = (thread);                   \
    } while (0)

#define AddPrio(queue, thread, link)                                       \
    do {                                                                   \
        OSThread *prev, *next;                                             \
                                                                           \
        for (next = (queue)->head; next && next->priority <= thread->priority; \
             next = next->link.next)                                       \
            ;                                                              \
        if (next == 0)                                                     \
            AddTail(queue, thread, link);                                  \
        else {                                                             \
            (thread)->link.next = next;                                    \
            prev = next->link.prev;                                        \
            next->link.prev = (thread);                                    \
            (thread)->link.prev = prev;                                    \
            if (prev == 0)                                                 \
                (queue)->head = (thread);                                  \
            else                                                           \
                prev->link.next = (thread);                                \
        }                                                                  \
    } while (0)

#define RemoveItem(queue, thread, link)             \
    do {                                            \
        OSThread *next, *prev;                      \
        next = (thread)->link.next;                 \
        prev = (thread)->link.prev;                 \
        if (next == 0)                              \
            (queue)->tail = prev;                   \
        else                                        \
            next->link.prev = prev;                 \
        if (prev == 0)                              \
            (queue)->head = next;                   \
        else                                        \
            prev->link.next = next;                 \
    } while (0)

/* SetEffectivePriority (OSThread.c) */
OSThread *SetEffectivePriority(OSThread *thread, s32 priority) {
    switch (thread->state) {
    case OS_THREAD_STATE_READY:
        UnsetRun(thread);
        thread->priority = priority;
        thread->queue = &RunQueue_80640E98[thread->priority];
        AddTail(thread->queue, thread, link);
        RunQueueBits_8064D988 |= 1u << (31 - thread->priority);
        RunQueueHint_8064D98C = 1;
        break;
    case OS_THREAD_STATE_WAITING:
        RemoveItem(thread->queue, thread, link);
        thread->priority = priority;
        AddPrio(thread->queue, thread, link);
        if (thread->mutex) {
            return thread->mutex->thread;
        }
        break;
    case OS_THREAD_STATE_RUNNING:
        RunQueueHint_8064D98C = 1;
        thread->priority = priority;
        break;
    }
    return 0;
}
