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

extern CardControl lbl_80641C60[];
extern void fn_802100F0(OSThreadQueue *queue);

/* Wake the threads waiting on this memory card channel. */
void fn_8021C378(int channel)
{
    CardControl *card = &lbl_80641C60[channel];
    fn_802100F0(&card->threadQueue);
}
