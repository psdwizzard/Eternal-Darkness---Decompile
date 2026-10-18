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

/* Validate the endpoints and reciprocal links of a thread queue. */
s32 CheckThreadQueue(OSThreadQueue *queue)
{
    OSThread *thread;

    if (queue->head && queue->head->prev) {
        return 0;
    }
    if (queue->tail && queue->tail->next) {
        return 0;
    }
    for (thread = queue->head; thread; thread = thread->next) {
        if (thread->next && thread != thread->next->prev) {
            return 0;
        }
        if (thread->prev && thread != thread->prev->next) {
            return 0;
        }
    }
    return 1;
}
