/* Completion callback for DVDCancelAll: notify the waiting thread. */
typedef int s32;
typedef int BOOL;
typedef struct DVDCommandBlock DVDCommandBlock;
typedef struct OSThread OSThread;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

extern BOOL lbl_8064DA3C;
extern OSThreadQueue __DVDThreadQueue;
extern void fn_802100F0(OSThreadQueue *queue);

void fn_802161B4(s32 result, DVDCommandBlock *block) {
    lbl_8064DA3C = 1;
    fn_802100F0(&__DVDThreadQueue);
}
