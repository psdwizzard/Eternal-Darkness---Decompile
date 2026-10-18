/* Completion callback for DVDCancelAll: notify the waiting thread. */
typedef int s32;
typedef int BOOL;
typedef struct DVDCommandBlock DVDCommandBlock;
typedef struct OSThread OSThread;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

extern BOOL CancelAllSyncComplete;
extern OSThreadQueue __DVDThreadQueue;
extern void OSWakeupThread(OSThreadQueue *queue);

void cbForCancelAllSync(s32 result, DVDCommandBlock *block) {
    CancelAllSyncComplete = 1;
    OSWakeupThread(&__DVDThreadQueue);
}
