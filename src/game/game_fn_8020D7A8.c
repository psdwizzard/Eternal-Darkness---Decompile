/* fn_8020D7A8 (0x8020D7A8, 56 bytes): OSInitMutex. */

typedef struct OSThread OSThread;
typedef struct OSMutex OSMutex;

typedef struct OSThreadQueue {
    OSThread* head;
    OSThread* tail;
} OSThreadQueue;

struct OSMutex {
    OSThreadQueue queue; /* 0x00 */
    OSThread* thread;    /* 0x08 */
    int count;          /* 0x0C */
    OSMutex* next;      /* 0x10 */
    OSMutex* prev;      /* 0x14 */
};

extern void OSInitThreadQueue(OSThreadQueue* queue);

void fn_8020D7A8(OSMutex* mutex) {
    OSInitThreadQueue(&mutex->queue);
    mutex->thread = 0;
    mutex->count = 0;
}
