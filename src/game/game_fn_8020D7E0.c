/* OSLockMutex (0x8020D7E0, 220 bytes): OSLockMutex. */

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
    unsigned char pad2D4[0x1C];
    OSMutex* mutex;            /* 0x2F0 */
    OSMutexQueue queueMutex;   /* 0x2F4 */
};

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern OSThread* OSGetCurrentThread(void);
extern int __OSPromoteThread(OSThread* thread, int priority);
extern void OSSleepThread(OSThreadQueue* queue);

void OSLockMutex(OSMutex* mutex) {
    int enabled = OSDisableInterrupts();
    OSThread* currentThread = OSGetCurrentThread();
    OSThread* ownerThread;

    while (1) {
        ownerThread = mutex->thread;
        if (ownerThread == 0) {
            OSMutex* prev;
            mutex->thread = currentThread;
            mutex->count++;
            prev = currentThread->queueMutex.tail;
            if (prev == 0) {
                currentThread->queueMutex.head = mutex;
            } else {
                prev->next = mutex;
            }
            mutex->prev = prev;
            mutex->next = 0;
            currentThread->queueMutex.tail = mutex;
            break;
        } else if (ownerThread == currentThread) {
            mutex->count++;
            break;
        } else {
            currentThread->mutex = mutex;
            __OSPromoteThread(mutex->thread, currentThread->priority);
            OSSleepThread(&mutex->queue);
            currentThread->mutex = 0;
        }
    }
    OSRestoreInterrupts(enabled);
}
