/* OSUnlockMutex (0x8020D8BC, 200 bytes): OSUnlockMutex. */

typedef struct OSThread OSThread;
typedef struct OSMutex OSMutex;

typedef struct OSThreadQueue {
    OSThread* head;
    OSThread* tail;
} OSThreadQueue;

struct OSMutex {
    OSThreadQueue queue; /* 0x00 */
    OSThread* thread;    /* 0x08 */
    int count;           /* 0x0C */
    OSMutex* next;       /* 0x10 */
    OSMutex* prev;       /* 0x14 */
};

typedef struct OSMutexQueue {
    OSMutex* head;
    OSMutex* tail;
} OSMutexQueue;

struct OSThread {
    unsigned char pad0[0x2D0];
    int priority;              /* 0x2D0 */
    int base;                  /* 0x2D4 */
    unsigned char pad2D8[0x18];
    OSMutex* mutex;            /* 0x2F0 */
    OSMutexQueue queueMutex;   /* 0x2F4 */
};

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern OSThread* OSGetCurrentThread(void);
extern int __OSGetEffectivePriority(OSThread* thread);
extern void OSWakeupThread(OSThreadQueue* queue);

void OSUnlockMutex(OSMutex* mutex) {
    int enabled = OSDisableInterrupts();
    OSThread* currentThread = OSGetCurrentThread();

    if (mutex->thread == currentThread && --mutex->count == 0) {
        OSMutex* next = mutex->next;
        OSMutex* prev = mutex->prev;
        if (next == 0) {
            currentThread->queueMutex.tail = prev;
        } else {
            next->prev = prev;
        }
        if (prev == 0) {
            currentThread->queueMutex.head = next;
        } else {
            prev->next = next;
        }
        mutex->thread = 0;
        if (currentThread->priority < currentThread->base) {
            currentThread->priority = __OSGetEffectivePriority(currentThread);
        }
        OSWakeupThread(&mutex->queue);
    }
    OSRestoreInterrupts(enabled);
}
