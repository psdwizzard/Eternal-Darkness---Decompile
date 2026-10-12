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
extern void OSReport(const char *, ...);
extern void fn_8020C5D0(const char *, int, const char *, ...);
extern s32 fn_802102B4(OSThreadQueue *);
extern s32 fn_8020DAF4(OSThread *);
extern s32 fn_8020DB2C(OSThread *);
extern u32 RunQueueBits_8064D988;
volatile OSThreadQueue ActiveThreadQueue : 0x800000DC;
extern OSThreadQueue RunQueue_80640E98[32];
extern char lbl_802FD8E0[];
extern const char lbl_8064C3E8[8];
#define ASSERT_THREAD(condition, offset, line) \
    do { if (!(condition)) { \
        OSReport(diagnostic.text + (offset), line); \
        fn_8020C5D0(diagnostic.text + 0x60, line, lbl_8064C3E8); \
    } } while (0)

static inline s32 Contains(OSThreadQueue *queue, OSThread *thread)
{
    OSThread *iter;
    for (iter = queue->head; iter; iter = iter->next) {
        if (thread == iter) {
            return 1;
        }
    }
    return 0;
}

static inline s32 EffectivePriority(OSThread *thread)
{
    s32 priority = thread->basePriority;
    OSMutex *mutex;
    for (mutex = thread->mutexHead; mutex; mutex = mutex->next) {
        OSThread *waiter = mutex->queue.head;
        if (waiter) {
            s32 candidate = waiter->priority;
            if (candidate < priority) {
                priority = candidate;
            }
        }
    }
    return priority;
}

enum {
    THREAD_READY = 1,
    THREAD_RUNNING = 2,
    THREAD_WAITING = 4,
    THREAD_MORIBUND = 8
};

/* Check scheduler queues and active threads with interrupts disabled. */
s32 fn_80210350(void)
{
    OSThreadQueue *runQueues = RunQueue_80640E98;
    /* Assertion messages and the source filename share this packed table. */
    struct { const char *text; } diagnostic;
    s32 count = 0;
    s32 enabled;
    OSThreadQueue *queue;
    s32 priority;
    OSThread *thread;
    diagnostic.text = lbl_802FD8E0;
    enabled = OSDisableInterrupts();
    queue = runQueues;
    priority = 0;
    do {
        if (RunQueueBits_8064D988 & (1 << (31 - priority))) {
            ASSERT_THREAD(queue->head && queue->tail, 0x0, 0x566);
        } else {
            ASSERT_THREAD(!queue->head && !queue->tail, 0x6C, 0x56B);
        }
        ASSERT_THREAD(fn_802102B4(queue), 0xCC, 0x56D);
        priority++;
        queue++;
    } while (priority <= 31);
    thread = ActiveThreadQueue.head;
    if (thread) {
        ASSERT_THREAD(!thread->activePrev, 0x114, 0x572);
    }
    thread = ActiveThreadQueue.tail;
    if (thread) {
        ASSERT_THREAD(!thread->activeNext, 0x194, 0x574);
    }
    for (thread = ActiveThreadQueue.head; thread; thread = thread->activeNext) {
        count++;
        if (thread->activeNext) {
            ASSERT_THREAD(thread == thread->activeNext->activePrev, 0x214, 0x57C);
        }
        if (thread->activePrev) {
            ASSERT_THREAD(thread == thread->activePrev->activeNext, 0x290, 0x57E);
        }
        ASSERT_THREAD(*thread->stackEnd == 0xDEADBABE, 0x30C, 0x581);
        ASSERT_THREAD(thread->priority >= 0 && thread->priority <= 32, 0x360, 0x584);
        ASSERT_THREAD(thread->suspend >= 0, 0x3D4, 0x585);
        ASSERT_THREAD(fn_802102B4(&thread->joinQueue), 0x410, 0x586);
        switch (thread->state) {
        case THREAD_READY:
            if (thread->suspend <= 0) {
                ASSERT_THREAD(thread->queue == &runQueues[thread->priority], 0x45C, 0x58C);
                ASSERT_THREAD(Contains(&runQueues[thread->priority], thread), 0x4B0, 0x58D);
                ASSERT_THREAD(thread->priority == EffectivePriority(thread), 0x504, 0x58E);
            }
            break;
        case THREAD_RUNNING:
            ASSERT_THREAD(thread->suspend <= 0, 0x560, 0x592);
            ASSERT_THREAD(!thread->queue, 0x5A4, 0x593);
            ASSERT_THREAD(thread->priority == EffectivePriority(thread), 0x504, 0x594);
            break;
        case THREAD_WAITING:
            ASSERT_THREAD(thread->queue, 0x5E0, 0x597);
            ASSERT_THREAD(fn_802102B4(thread->queue), 0x61C, 0x598);
            ASSERT_THREAD(Contains(thread->queue, thread), 0x660, 0x599);
            if (thread->suspend <= 0) {
                ASSERT_THREAD(thread->priority == EffectivePriority(thread), 0x504, 0x59C);
            } else {
                ASSERT_THREAD(thread->priority == 32, 0x6A4, 0x5A0);
            }
            ASSERT_THREAD(!fn_8020DAF4(thread), 0x6E0, 0x5A2);
            break;
        case THREAD_MORIBUND:
            ASSERT_THREAD(!thread->mutexHead && !thread->mutexTail, 0x720, 0x5A6);
            break;
        default:
            OSReport(diagnostic.text + 0x788, thread->state, thread);
            fn_8020C5D0(diagnostic.text + 0x60, 0x5AC, lbl_8064C3E8);
            break;
        }
        ASSERT_THREAD(fn_8020DB2C(thread), 0x7D0, 0x5B1);
    }
    OSRestoreInterrupts(enabled);
    return count;
}
