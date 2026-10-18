/* Compact consumed stream bytes and return space for more input. */
typedef struct AudioSync {
    unsigned char *data;
    int storage;
    int fill;
    int returned;
    int unsynced;
    int headerBytes;
    int bodyBytes;
} AudioSync;

extern void *memmove(void *dst, const void *src, unsigned long size);
extern void *fn_8022F780(int size);

void *ogg_sync_buffer(AudioSync *sync, int size) {
    int newStorage;

    if (sync->returned != 0) {
        sync->fill -= sync->returned;
        if (sync->fill > 0) {
            memmove(sync->data, sync->data + sync->returned, sync->fill);
        }
        sync->returned = 0;
    }

    if (size > sync->storage - sync->fill) {
        newStorage = sync->fill + 0x2000;
        newStorage += size;
        if (sync->data == 0) {
            sync->data = fn_8022F780(newStorage);
        }
        sync->storage = newStorage;
    }
    return sync->data + sync->fill;
}
