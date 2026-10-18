typedef unsigned int u32;

typedef struct Entry {
    struct Entry* previous;
    struct Entry* next;
    void* value;
    void* data;
    void* parameter;
    void* callback_arg;
    unsigned char callback[1];
} Entry;

extern Entry* __DTKPlayListHead;
extern Entry* __DTKPlayListTail;
extern Entry* __DTKCurrentTrack;
extern u32 __DTKState;

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);
extern int DVDOpen(void*, void*);
extern void __DTKCheckUserCallback(Entry*, u32);
extern void __DTKPrepareCurrentTrack(void);

int DTKQueueTrack(void* value, Entry* entry, void* data, void* parameter,
                void* callback_arg)
{
    u32 resume = 0;
    u32 interrupts;

    if (DVDOpen(value, entry->callback) == 0) {
        return 1;
    }

    interrupts = OSDisableInterrupts();
    entry->value = value;
    entry->data = data;
    entry->callback_arg = callback_arg;
    if (__DTKPlayListHead == 0) {
        __DTKPlayListHead = entry;
        __DTKPlayListTail = entry;
        entry->previous = 0;
        entry->next = 0;
        if (__DTKState == 1) {
            resume = 1;
        }
    } else {
        __DTKPlayListTail->next = entry;
        entry->previous = __DTKPlayListTail;
        __DTKPlayListTail = entry;
        entry->next = 0;
    }
    if (__DTKCurrentTrack == 0) {
        __DTKCurrentTrack = entry;
    }
    __DTKCurrentTrack->parameter = parameter;
    OSRestoreInterrupts(interrupts);
    __DTKCheckUserCallback(entry, 8);
    if (resume != 0) {
        __DTKState = 3;
        __DTKPrepareCurrentTrack();
    }
    return 0;
}
