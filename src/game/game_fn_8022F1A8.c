/* Record bytes written to the audio synchronization buffer. */
typedef struct AudioSync {
    unsigned char *data;
    int storage;
    int fill;
    int returned;
    int unsynced;
    int headerBytes;
    int bodyBytes;
} AudioSync;

int ogg_sync_wrote(AudioSync *sync, int bytes) {
    int newFill = sync->fill + bytes;

    if (newFill > sync->storage) {
        return -1;
    }
    sync->fill = newFill;
    return 0;
}
