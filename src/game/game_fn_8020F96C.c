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

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32);
extern void OSClearContext(void *context);
extern void fn_8020D984(OSThread *thread);
extern void fn_802100F0(OSThreadQueue *queue);
extern void SelectThread_8020F61C(s32 yield);
extern volatile s32 RunQueueHint_8064D98C;

#define OS_THREAD_STATE_MORIBUND 8
#define OS_THREAD_ATTR_DETACH 1

volatile OSThreadQueue __OSActiveThreadQueue : 0x800000DC;
#define __OSCurrentThread (*(OSThread **)0x800000E4)

/* OSExitThread */
void fn_8020F96C(void *val)
{
    OSThread *currentThread;
    s32 enabled;

    enabled = OSDisableInterrupts();
    currentThread = __OSCurrentThread;

    OSClearContext(currentThread);
    if (currentThread->attr & OS_THREAD_ATTR_DETACH) {
        OSThread *prev;
        OSThread *next;

        next = currentThread->activeNext;
        prev = currentThread->activePrev;
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
        currentThread->state = 0;
    } else {
        currentThread->state = OS_THREAD_STATE_MORIBUND;
        currentThread->value = val;
    }
    fn_8020D984(currentThread);
    fn_802100F0(&currentThread->joinQueue);
    RunQueueHint_8064D98C = 1;
    if (RunQueueHint_8064D98C != 0) {
        SelectThread_8020F61C(0);
    }
    OSRestoreInterrupts(enabled);
}
