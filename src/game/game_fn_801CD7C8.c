typedef unsigned char u8;

typedef struct Queue {
    u8 entries[0x280];
    u8 write_index;
    volatile u8 count;
} Queue;

extern Queue aramQueueLo;

void aramSyncTransferQueue(void)
{
    while (aramQueueLo.count != 0) {
    }
}
