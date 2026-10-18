typedef struct OSThread OSThread;
typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

typedef struct CardControl {
    unsigned char reserved00[0x8C];
    OSThreadQueue threadQueue;
    unsigned char reserved94[0x7C];
} CardControl;

extern CardControl __CARDBlock[];
extern void OSWakeupThread(OSThreadQueue *queue);

/* Wake the threads waiting on this memory card channel. */
void __CARDSyncCallback(int channel)
{
    CardControl *card = &__CARDBlock[channel];
    OSWakeupThread(&card->threadQueue);
}
