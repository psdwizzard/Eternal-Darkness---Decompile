typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex;
    u32 in_use;
    u32 length;
    u32 position;
    u8 data[0x880];
} TRKBuffer;

extern TRKBuffer gTRKMsgBufs[3];
extern void TRKAcquireMutex(void *);
extern void TRKReleaseMutex(void *);

void TRKReleaseBuffer(int id)
{
    TRKBuffer *buffer;

    if (id != -1 && id >= 0 && id < 3) {
        buffer = &gTRKMsgBufs[id];
        TRKAcquireMutex(buffer);
        buffer->in_use = 0;
        TRKReleaseMutex(buffer);
    }
}
