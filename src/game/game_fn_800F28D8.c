typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

typedef struct TRKEvent {
    u8 type;
    u8 pad[3];
    u32 id;
    int buffer;
} TRKEvent;

extern int IsTRKConnected;
extern int TRKResetBuffer(TRKBuffer *, int);
extern int TRKMessageSend(TRKBuffer *);
extern void TRKConstructEvent(TRKEvent *, u8);
extern int TRKPostEvent(const TRKEvent *);

int TRKDoDisconnect(TRKBuffer *arg)
{
    TRKEvent event;
    TRKBuffer *buffer = arg;
    int retry;
    int result;

    IsTRKConnected = 0;
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
        result = TRKMessageSend(buffer);
        retry--;
        if (result == 0)
            break;
    } while (retry > 0);
    if (result == 0) {
        TRKConstructEvent(&event, 1);
        TRKPostEvent(&event);
    }
    return result;
}
