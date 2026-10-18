typedef unsigned int u32;

typedef struct Entry {
    struct Entry* previous;
    struct Entry* next;
    unsigned char pad008[0x10];
    unsigned char callback[1];
} Entry;

extern Entry* __DTKPlayListHead;
extern Entry* __DTKPlayListTail;
extern Entry* __DTKCurrentTrack;
extern u32 __DTKRepeatMode;

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);
extern void DVDClose(void*);

int DTKRemoveTrack(Entry* entry)
{
    u32 interrupts;

    if (entry == __DTKCurrentTrack) {
        return 2;
    }
    interrupts = OSDisableInterrupts();
    DVDClose(entry->callback);
    if (entry == __DTKPlayListHead && entry == __DTKPlayListTail) {
        __DTKPlayListHead = 0;
        __DTKPlayListTail = 0;
        OSRestoreInterrupts(interrupts);
        return 0;
    }
    if (entry == __DTKPlayListHead) {
        __DTKPlayListHead = entry->next;
        __DTKPlayListHead->previous = 0;
        if (__DTKRepeatMode == 1) {
            __DTKPlayListTail->next = __DTKPlayListHead;
        }
        OSRestoreInterrupts(interrupts);
        return 0;
    }
    if (entry == __DTKPlayListTail) {
        __DTKPlayListTail = entry->previous;
        __DTKPlayListTail->next = 0;
        if (__DTKRepeatMode == 1) {
            __DTKPlayListTail->next = __DTKPlayListHead;
        }
        OSRestoreInterrupts(interrupts);
        return 0;
    }
    entry->previous->next = entry->next;
    entry->next->previous = entry->previous;
    OSRestoreInterrupts(interrupts);
    return 0;
}
