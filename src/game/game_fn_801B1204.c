typedef unsigned char u8;

typedef struct Entry {
    struct Entry* previous;
    struct Entry* next;
    u8 pad008[8];
    int value;
    u8 pad014[4];
    u8 callback[1];
} Entry;

extern u8 __block_for_stream_status[];
extern unsigned int __DTKTrackEnded;
extern int __DTKPosition;
extern int __DTKRepeatMode;
extern int __DTKState;
extern Entry* __DTKPlayListHead;
extern Entry* __DTKCurrentTrack;

extern void __DTKStopAi(void);
extern void __DTKCheckUserCallback(Entry*, unsigned int);
extern void __DTKPrepareCurrentTrack(void);
extern void __DTKCallbackForStreamStatus(void);
extern void DVDGetStreamErrorStatusAsync(void*, void (*)(void));

void __DTKCallbackForPlaylist(int value)
{
    __DTKPosition = value;
    if (__DTKTrackEnded != 0) {
        __DTKTrackEnded = 0;
        __DTKCheckUserCallback(__DTKCurrentTrack, 0x10);
        __DTKState = 3;
        switch (__DTKRepeatMode) {
        case 0:
            if (__DTKCurrentTrack != 0) {
                Entry* entry = __DTKCurrentTrack->next;
                if (entry != 0) {
                    __DTKCurrentTrack = entry;
                    entry->value = 0;
                    __DTKStopAi();
                    __DTKPrepareCurrentTrack();
                } else {
                    entry = __DTKPlayListHead;
                    __DTKCurrentTrack = entry;
                    entry->value = 0;
                    __DTKStopAi();
                    __DTKState = 0;
                }
            }
            break;
        case 1:
            if (__DTKCurrentTrack != 0) {
                Entry* entry = __DTKCurrentTrack->next;
                if (entry != 0) {
                    __DTKCurrentTrack = entry;
                    entry->value = 0;
                    __DTKStopAi();
                    __DTKPrepareCurrentTrack();
                } else {
                    entry = __DTKPlayListHead;
                    __DTKCurrentTrack = entry;
                    entry->value = 0;
                    __DTKStopAi();
                    __DTKPrepareCurrentTrack();
                }
            }
            break;
        case 2:
            if (__DTKCurrentTrack != 0) {
                __DTKCurrentTrack->value = 0;
                __DTKStopAi();
                __DTKPrepareCurrentTrack();
            }
            break;
        }
    } else {
        DVDGetStreamErrorStatusAsync(__block_for_stream_status, __DTKCallbackForStreamStatus);
    }
}
