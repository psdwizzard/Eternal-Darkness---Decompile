/* Completion callback for DVDCancel: wake threads waiting for cancellation. */
typedef int s32;
typedef struct DVDCommandBlock DVDCommandBlock;
typedef struct OSThread OSThread;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

extern OSThreadQueue __DVDThreadQueue;
extern void fn_802100F0(OSThreadQueue *queue);

void fn_80216058(s32 result, DVDCommandBlock *block) {
    fn_802100F0(&__DVDThreadQueue);
}
