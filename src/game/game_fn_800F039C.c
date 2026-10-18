typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int TRKSetBufferPosition(TRKBuffer *, int);
extern int TRKReadBuffer1_ui8(TRKBuffer *, u8 *);
extern int TRKResetBuffer(TRKBuffer *, int);
extern int TRKMessageSend(TRKBuffer *);
extern void SetUseSerialIO(u8);

static void append(TRKBuffer *buffer, u8 value)
{
    if (buffer->position < 0x880) {
        buffer->data[buffer->position++] = value;
        buffer->length++;
    }
}

void TRKDoSetOption(TRKBuffer *buffer)
{
    u8 a = 0, b = 0, c = 0;
    int result, retry;

    TRKSetBufferPosition(buffer, 0);
    result = TRKReadBuffer1_ui8(buffer, &a);
    if (result == 0) result = TRKReadBuffer1_ui8(buffer, &b);
    if (result == 0) result = TRKReadBuffer1_ui8(buffer, &c);
    if (result != 0) {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 1);
        retry = 3;
        do {
            result = TRKMessageSend(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
    } else if (b == 1) {
        SetUseSerialIO(c);
    }
    TRKResetBuffer(buffer, 1);
    append(buffer, 0x80);
    append(buffer, 0);
    retry = 3;
    do {
        result = TRKMessageSend(buffer);
        retry--;
        if (result == 0) break;
    } while (retry > 0);
}
