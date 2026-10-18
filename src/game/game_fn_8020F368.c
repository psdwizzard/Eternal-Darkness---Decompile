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

extern volatile u32 RunQueueBits_8064D988;

/* Remove a thread from its run queue and clear the bit if it becomes empty. */
void UnsetRun(OSThread *thread) {
    OSThreadQueue *queue = thread->queue;
    OSThread *next = thread->link.next;
    OSThread *prev = thread->link.prev;

    if (next == 0) {
        queue->tail = prev;
    } else {
        next->link.prev = prev;
    }
    if (prev == 0) {
        queue->head = next;
    } else {
        prev->link.next = next;
    }
    if (queue->head == 0) {
        RunQueueBits_8064D988 &= ~(1u << (31 - thread->priority));
    }
    thread->queue = 0;
}
