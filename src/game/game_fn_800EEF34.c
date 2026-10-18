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

int TRKPostEvent(const TRKEvent *event)
{
    int result = 0;
    int offset;

    TRKAcquireMutex(&gTRKEventQueue);
    if (gTRKEventQueue.count == 2) {
        result = 0x100;
    } else {
        offset = (gTRKEventQueue.next + gTRKEventQueue.count) % 2;
        TRK_memcpy(&gTRKEventQueue.events[offset], event, 12);
        gTRKEventQueue.events[offset].id = gTRKEventQueue.next_id;
        gTRKEventQueue.next_id++;
        if (gTRKEventQueue.next_id < 0x100)
            gTRKEventQueue.next_id = 0x100;
        gTRKEventQueue.count++;
    }
    TRKReleaseMutex(&gTRKEventQueue);
    return result;
}
