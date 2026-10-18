typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Request {
    u8 pad00[0xC];
    u32 type;
} Request;

typedef struct Entry {
    u8 pad00[0x20];
    void (*callback)(u32);
    u32 argument;
} Entry;

extern Entry aramQueueLo;
extern Entry aramQueueHi;

void aramQueueCallback(Request* request)
{
    Entry* entries;
    u32 i;
    entries = request->type == 1 ? &aramQueueHi : &aramQueueLo;

    for (i = 0; i < 16; i++) {
        if ((Entry*)request == &entries[i] && entries[i].callback != 0) {
            entries[i].callback(entries[i].argument);
        }
    }
    ((u8*)entries)[0x281]--;
}
