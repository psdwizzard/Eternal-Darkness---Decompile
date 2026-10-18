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

TRKBuffer *TRKGetBuffer(int id)
{
    TRKBuffer *buffer = 0;

    if (id >= 0 && id < 3)
        buffer = &gTRKMsgBufs[id];
    return buffer;
}
