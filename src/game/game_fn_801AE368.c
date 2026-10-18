typedef unsigned char u8;

typedef struct Entry {
    u8 active;
    u8 padding01[19];
    u8 work[60];
    void* handle;
    u8 padding54[32];
    int pending;
    int stopped;
} Entry;

extern void sndStreamDeactivate(void*);
extern void DVDClose(void*);

void fn_801AE368(Entry* entry)
{
    if (entry != 0) {
        sndStreamDeactivate(entry->handle);
        if (entry->pending == 0) {
            DVDClose(entry->work);
            entry->active = 0;
        } else {
            entry->stopped = 1;
        }
    }
}
