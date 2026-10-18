/* cbForReadSync: wake threads waiting for a synchronous DVD read. */
typedef int s32;
typedef struct DVDCommandBlock DVDCommandBlock;
typedef struct OSThread OSThread;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

extern OSThreadQueue __DVDThreadQueue;
extern void OSWakeupThread(OSThreadQueue *queue); /* OSWakeupThread */

void cbForReadSync(s32 result, DVDCommandBlock *block) {
    OSWakeupThread(&__DVDThreadQueue);
}
