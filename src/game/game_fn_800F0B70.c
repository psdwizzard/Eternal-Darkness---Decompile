typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int TRKTargetStopped(void);
extern void TRKTargetContinue(void);
extern int TRKResetBuffer(TRKBuffer *, int);
extern int TRKMessageSend(TRKBuffer *);

static void append(TRKBuffer *buffer, u8 value)
{
    if (buffer->position < 0x880) {
        buffer->data[buffer->position++] = value;
        buffer->length++;
    }
}

void TRKDoContinue(TRKBuffer *buffer)
{
    int retry;
    int result;

    if (!TRKTargetStopped()) {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 0x16);
        retry = 3;
        do {
            result = TRKMessageSend(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
    } else {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 0);
        retry = 3;
        do {
            result = TRKMessageSend(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
        if (result == 0)
            TRKTargetContinue();
    }
}
