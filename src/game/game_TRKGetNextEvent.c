typedef unsigned char u8;
typedef unsigned int u32;
typedef struct TRKEvent {
    u8 type;
    u8 pad[3];
    u32 id;
    int buffer;
} TRKEvent;
typedef struct TRKEventQueue {
    u32 mutex;
    int count;
    int next;
    TRKEvent events[2];
    u32 next_id;
} TRKEventQueue;

extern TRKEventQueue gTRKEventQueue;
extern void TRKAcquireMutex(void *);
extern void TRKReleaseMutex(void *);
extern void TRK_memcpy(void *, const void *, u32);

int TRKGetNextEvent(TRKEvent *event)
{
    int result = 0;

    TRKAcquireMutex(&gTRKEventQueue);
    if (gTRKEventQueue.count > 0) {
        TRK_memcpy(event, &gTRKEventQueue.events[gTRKEventQueue.next], 12);
        gTRKEventQueue.count--;
        gTRKEventQueue.next++;
        if (gTRKEventQueue.next == 2)
            gTRKEventQueue.next = 0;
        result = 1;
    }
    TRKReleaseMutex(&gTRKEventQueue);
    return result;
}
