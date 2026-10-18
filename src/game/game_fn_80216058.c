/* Completion callback for DVDCancel: wake threads waiting for cancellation. */
typedef int s32;
typedef struct DVDCommandBlock DVDCommandBlock;
typedef struct OSThread OSThread;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

extern OSThreadQueue __DVDThreadQueue;
extern void OSWakeupThread(OSThreadQueue *queue);

void cbForCancelSync(s32 result, DVDCommandBlock *block) {
    OSWakeupThread(&__DVDThreadQueue);
}
