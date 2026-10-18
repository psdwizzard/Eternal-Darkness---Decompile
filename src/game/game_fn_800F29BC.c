typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int IsTRKConnected;
extern int TRKResetBuffer(TRKBuffer *, int);
extern int TRKMessageSend(TRKBuffer *);

void TRKDoConnect(TRKBuffer *buffer)
{
    int retry;

    IsTRKConnected = 1;
    TRKResetBuffer(buffer, 1);
    if (buffer->position < 0x880) {
        buffer->data[buffer->position++] = 0x80;
        buffer->length++;
    }
    if (buffer->position < 0x880) {
        buffer->data[buffer->position++] = 0;
        buffer->length++;
    }
    retry = 3;
    do {
        int result = TRKMessageSend(buffer);
        retry--;
        if (result == 0)
            break;
    } while (retry > 0);
}
