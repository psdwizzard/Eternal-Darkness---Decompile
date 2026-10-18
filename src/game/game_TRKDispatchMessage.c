typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex;
    u32 in_use;
    u32 length;
    u32 position;
    u8 data[0x880];
} TRKBuffer;

typedef int (*TRKDispatchHandler)(TRKBuffer *);

extern u32 gTRKDispatchTableSize;
extern TRKDispatchHandler gTRKDispatchTable[];
extern int TRKSetBufferPosition(TRKBuffer *, u32);
extern int TRKReadBuffer1_ui8(TRKBuffer *, u8 *);

int TRKDispatchMessage(TRKBuffer *buffer)
{
    int error;
    u8 command;

    error = 0x500;
    TRKSetBufferPosition(buffer, 0);
    TRKReadBuffer1_ui8(buffer, &command);
    command &= 0xFF;
    if (command < gTRKDispatchTableSize) {
        error = gTRKDispatchTable[command](buffer);
    }
    return error;
}
