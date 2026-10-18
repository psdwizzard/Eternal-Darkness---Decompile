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

/* Validate the mutex wait queue and ownership count. */
s32 __OSCheckMutex(OSMutex *mutex)
{
    OSThread *thread;
    s32 priority = 0;

    if (mutex->queue.head && mutex->queue.head->prev) {
        return 0;
    }
    if (mutex->queue.tail && mutex->queue.tail->next) {
        return 0;
    }
    for (thread = mutex->queue.head; thread; thread = thread->next) {
        if (thread->next && thread != thread->next->prev) {
            return 0;
        }
        if (thread->prev && thread != thread->prev->next) {
            return 0;
        }
        if (thread->state != 4) {
            return 0;
        }
        if (thread->priority < priority) {
            return 0;
        }
        priority = thread->priority;
    }
    if (mutex->owner) {
        if (mutex->count <= 0) {
            return 0;
        }
    } else {
        if (mutex->count != 0) {
            return 0;
        }
    }
    return 1;
}
