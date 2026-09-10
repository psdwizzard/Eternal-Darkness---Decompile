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

extern TRKEventQueue lbl_803285E0;
extern void fn_800F34C4(void *);
extern void fn_800F34BC(void *);
extern void fn_80003130(void *, const void *, u32);

int TRKGetNextEvent(TRKEvent *event)
{
    int result = 0;

    fn_800F34C4(&lbl_803285E0);
    if (lbl_803285E0.count > 0) {
        fn_80003130(event, &lbl_803285E0.events[lbl_803285E0.next], 12);
        lbl_803285E0.count--;
        lbl_803285E0.next++;
        if (lbl_803285E0.next == 2)
            lbl_803285E0.next = 0;
        result = 1;
    }
    fn_800F34BC(&lbl_803285E0);
    return result;
}
