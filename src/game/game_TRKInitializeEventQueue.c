typedef unsigned int u32;
typedef struct TRKEventQueue {
    u32 mutex;
    int count;
    int next;
    u32 events[6];
    u32 next_id;
} TRKEventQueue;

extern TRKEventQueue gTRKEventQueue;
extern void TRKInitializeMutex(void *);
extern void TRKAcquireMutex(void *);
extern void TRKReleaseMutex(void *);

int TRKInitializeEventQueue(void)
{
    TRKInitializeMutex(&gTRKEventQueue);
    TRKAcquireMutex(&gTRKEventQueue);
    gTRKEventQueue.count = 0;
    gTRKEventQueue.next = 0;
    gTRKEventQueue.next_id = 0x100;
    TRKReleaseMutex(&gTRKEventQueue);
    return 0;
}
