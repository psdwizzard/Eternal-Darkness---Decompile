typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int TRKSetBufferPosition(TRKBuffer *, int);
extern int TRKReadBuffer1_ui8(TRKBuffer *, u8 *);
extern int TRKReadBuffer1_ui32(TRKBuffer *, u32 *);
extern int TRKResetBuffer(TRKBuffer *, int);
extern int TRKMessageSend(TRKBuffer *);
extern int TRKTargetFlushCache(u8, u32, u32);

static inline void append(TRKBuffer *buffer, u8 value)
{
    if (buffer->position < 0x880) {
        buffer->data[buffer->position++] = value;
        buffer->length++;
    }
}

void TRKDoFlushCache(TRKBuffer *buffer)
{
    u32 start;
    u32 end;
    u8 message_command;
    u8 options;
    int result;
    int retry;

    if (buffer->length != 10) {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 2);
        retry = 3;
        do {
            result = TRKMessageSend(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
        return;
    }

    TRKSetBufferPosition(buffer, 0);
    result = TRKReadBuffer1_ui8(buffer, &message_command);
    if (result == 0) result = TRKReadBuffer1_ui8(buffer, &options);
    if (result == 0) result = TRKReadBuffer1_ui32(buffer, &start);
    if (result == 0) result = TRKReadBuffer1_ui32(buffer, &end);

    if (start > end) {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 0x13);
        retry = 3;
        do {
            result = TRKMessageSend(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
        return;
    }

    if (result == 0)
        result = TRKTargetFlushCache(options, start, end);

    if (result == 0) {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 0);
    }

    if (result != 0) {
        switch (result) {
        case 0x703:
            result = 0x12;
            break;
        default:
            result = 3;
            break;
        }
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, (u8)result);
        retry = 3;
        do {
            result = TRKMessageSend(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
    } else {
        retry = 3;
        do {
            result = TRKMessageSend(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
    }
}
