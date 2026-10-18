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
extern void TRKInitializeMutex(void *);
extern void TRKAcquireMutex(void *);
extern void TRKReleaseMutex(void *);

static inline void TRKSetBufferUsed(TRKBuffer* buffer, int used)
{
    buffer->in_use = used;
}

int TRKInitializeMessageBuffers(void)
{
    int i;
    for (i = 0; i < 3; i++) {
        TRKInitializeMutex(&gTRKMsgBufs[i]);
        TRKAcquireMutex(&gTRKMsgBufs[i]);
        TRKSetBufferUsed(&gTRKMsgBufs[i], 0);
        TRKReleaseMutex(&gTRKMsgBufs[i]);
    }
    return 0;
}
