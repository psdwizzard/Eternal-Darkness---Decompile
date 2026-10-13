/* fn_8020D7E0 (0x8020D7E0, 220 bytes): OSLockMutex. */

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
extern OSThread* fn_8020F2DC(void);
extern int fn_8020F5CC(OSThread* thread, int priority);
extern void fn_80210004(OSThreadQueue* queue);

void fn_8020D7E0(OSMutex* mutex) {
    int enabled = OSDisableInterrupts();
    OSThread* currentThread = fn_8020F2DC();
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
            fn_8020F5CC(mutex->thread, currentThread->priority);
            fn_80210004(&mutex->queue);
            currentThread->mutex = 0;
        }
    }
    OSRestoreInterrupts(enabled);
}
