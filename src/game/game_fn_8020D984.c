typedef struct OSThread OSThread;
typedef struct OSMutex OSMutex;

typedef struct OSThreadQueue {
    OSThread* head;
    OSThread* tail;
} OSThreadQueue;

struct OSMutex {
    OSThreadQueue queue;
    OSThread* thread;
    int count;
    OSMutex* next;
    OSMutex* prev;
};

typedef struct OSMutexQueue {
    OSMutex* head;
    OSMutex* tail;
} OSMutexQueue;

struct OSThread {
    unsigned char pad0[0x2D0];
    int priority;
    int base;
    unsigned char pad2D8[0x18];
    OSMutex* mutex;
    OSMutexQueue queueMutex;
};

extern void OSWakeupThread(OSThreadQueue* queue);

/* Release every mutex owned by the thread and wake its waiters. */
void __OSUnlockAllMutex(OSThread* thread)
{
    OSMutex* mutex;
    OSMutex* next;

    while (thread->queueMutex.head != 0) {
        mutex = thread->queueMutex.head;
        next = mutex->next;
        if (next == 0) {
            thread->queueMutex.tail = 0;
        } else {
            next->prev = 0;
        }
        thread->queueMutex.head = next;
        mutex->count = 0;
        mutex->thread = 0;
        OSWakeupThread(&mutex->queue);
    }
}
