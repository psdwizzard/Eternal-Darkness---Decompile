typedef unsigned char u8;

typedef struct Entry {
    struct Entry* previous;
    struct Entry* next;
    u8 pad008[0x10];
    u8 callback[1];
} Entry;

extern void (*__DTKFlushCallback)(void);
extern int __DTKShutdownFlag;
extern int __DTKState;
extern Entry* __DTKPlayListTail;
extern Entry* __DTKPlayListHead;
extern Entry* __DTKCurrentTrack;

extern void DVDClose(void*);
extern void AISetStreamPlayState(int);

void __DTKCallbackForFlush(void)
{
    Entry* entry;

    AISetStreamPlayState(0);
    entry = __DTKPlayListHead;
    while (entry != 0) {
        DVDClose(entry->callback);
        entry = entry->next;
    }
    __DTKPlayListHead = 0;
    __DTKPlayListTail = 0;
    __DTKCurrentTrack = 0;
    __DTKState = 0;
    if (__DTKFlushCallback != 0) {
        __DTKFlushCallback();
        __DTKFlushCallback = 0;
    }
    __DTKState = 0;
    __DTKShutdownFlag = 0;
}
