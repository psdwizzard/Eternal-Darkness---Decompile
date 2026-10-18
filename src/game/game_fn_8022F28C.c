/* Clear an audio synchronization state. */
typedef struct AudioSync {
    unsigned char *data;
    int storage;
    int fill;
    int returned;
    int unsynced;
    int headerBytes;
    int bodyBytes;
} AudioSync;

extern void *memset(void *dest, int value, unsigned long size);

int ogg_sync_clear(AudioSync *sync) {
    if (sync != 0) {
        /* The original clear path retains a second null check. */
        if (sync != 0) {
            memset(sync, 0, sizeof(*sync));
        }
    }
    return 0;
}
