/* cbForReadSync: wake threads waiting for a synchronous DVD read. */
typedef int s32;
typedef struct DVDCommandBlock DVDCommandBlock;
typedef struct OSThread OSThread;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

extern OSThreadQueue __DVDThreadQueue;
extern void fn_802100F0(OSThreadQueue *queue); /* OSWakeupThread */

void fn_8021390C(s32 result, DVDCommandBlock *block) {
    fn_802100F0(&__DVDThreadQueue);
}
