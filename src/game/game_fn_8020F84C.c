typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef struct OSThread OSThread;
typedef struct OSMutex OSMutex;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;
typedef struct OSContext {
    u32 gpr[32];
    u32 cr;
    u32 lr;
    u32 ctr;
    u32 xer;
    double fpr[32];
    u32 fpscr_pad;
    u32 fpscr;
    u32 srr0;
    u32 srr1;
    u16 mode;
    u16 state;
    u32 gqr[8];
    u32 psf_pad;
    double psf[32];
} OSContext;
typedef struct OSMutexQueue {
    OSMutex *head;
    OSMutex *tail;
} OSMutexQueue;
struct OSThread {
    OSContext context;
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
    OSMutexQueue mutexQueue;
    OSThread *activeNext;
    OSThread *activePrev;
    void *stackBase;
    u32 *stackEnd;
};

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32);
extern void OSInitContext(OSContext *context, u32 pc, u32 sp);
extern void OSExitThread(void *val);

#define OS_THREAD_STATE_READY 1
#define OS_THREAD_ATTR_DETACH 1
#define OS_THREAD_STACK_MAGIC 0xDEADBABE

volatile OSThreadQueue __OSActiveThreadQueue : 0x800000DC;

static inline void OSInitThreadQueue(OSThreadQueue *queue)
{
    queue->head = queue->tail = 0;
}

static inline void OSInitMutexQueue(OSMutexQueue *queue)
{
    queue->head = queue->tail = 0;
}

/* OSCreateThread */
s32 OSCreateThread(OSThread *thread, void *(*func)(void *), void *param, void *stack,
                u32 stackSize, s32 priority, u16 attr)
{
    s32 enabled;
    u32 *sp;

    if (priority < 0 || 31 < priority) {
        return 0;
    }

    thread->state = OS_THREAD_STATE_READY;
    thread->attr = (u16)(attr & OS_THREAD_ATTR_DETACH);
    thread->priority = thread->basePriority = priority;
    thread->suspend = 1;
    thread->value = (void *)-1;
    thread->mutex = 0;
    OSInitThreadQueue(&thread->joinQueue);
    OSInitMutexQueue(&thread->mutexQueue);

    sp = (u32 *)stack;
    sp = (u32 *)((u32)sp & ~7);
    sp -= 2;
    sp[0] = 0;
    sp[1] = 0;

    {
        OSContext *context = &thread->context;
        OSInitContext(context, (u32)func, (u32)sp);
    }

    thread->context.lr = (u32)OSExitThread;
    thread->context.gpr[3] = (u32)param;
    thread->stackBase = stack;
    thread->stackEnd = (u32 *)((u32)stack - stackSize);
    *thread->stackEnd = OS_THREAD_STACK_MAGIC;

    enabled = OSDisableInterrupts();
    {
        OSThread *prev = __OSActiveThreadQueue.tail;
        if (prev == 0) {
            __OSActiveThreadQueue.head = thread;
        } else {
            prev->activeNext = thread;
        }
        thread->activePrev = prev;
        thread->activeNext = 0;
        __OSActiveThreadQueue.tail = thread;
    }
    OSRestoreInterrupts(enabled);
    return 1;
}
