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
extern s32 __OSGetEffectivePriority(OSThread *thread);
extern OSThread *SetEffectivePriority(OSThread *thread, s32 priority);
extern void SelectThread_8020F61C(s32 yield);
extern volatile s32 RunQueueHint_8064D98C;

static inline void UpdatePriority(OSThread *thread)
{
    s32 priority;
    do {
        if (0 < thread->suspend) {
            break;
        }
        priority = __OSGetEffectivePriority(thread);
        if (thread->priority == priority) {
            break;
        }
        thread = SetEffectivePriority(thread, priority);
    } while (thread);
}

/* OSSetThreadPriority: update the base priority and propagate inheritance. */
s32 OSSetThreadPriority(OSThread *thread, s32 priority)
{
    s32 enabled;

    if (priority < 0 || priority > 31) {
        return 0;
    }
    enabled = OSDisableInterrupts();
    if (thread->basePriority != priority) {
        thread->basePriority = priority;
        UpdatePriority(thread);
        if (RunQueueHint_8064D98C) {
            SelectThread_8020F61C(0);
        }
    }
    OSRestoreInterrupts(enabled);
    return 1;
}
