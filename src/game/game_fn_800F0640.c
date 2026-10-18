typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int TRKSetBufferPosition(TRKBuffer *, u32);
extern void TRKResetBuffer(TRKBuffer *, u8);
extern int TRKReadBuffer1_ui8(TRKBuffer *, u8 *);
extern int TRKReadBuffer1_ui32(TRKBuffer *, u32 *);
extern int TRKMessageSend(TRKBuffer *);
extern int TRKTargetStopped(void);
extern u32 TRKTargetGetPC(void);
extern int TRKTargetStepOutOfRange(u32, u32, int);
extern int TRKTargetSingleStep(u32, int);

static inline void append(TRKBuffer *buffer, u8 value)
{
    if (buffer->position < 0x880) {
        buffer->data[buffer->position++] = value;
        buffer->length++;
    }
}

static inline int reply(TRKBuffer *buffer, u8 status)
{
    int result;
    int retry;

    TRKResetBuffer(buffer, 1);
    append(buffer, 0x80);
    append(buffer, status);
    retry = 3;
    do {
        result = TRKMessageSend(buffer);
        retry--;
        if (result == 0) break;
    } while (retry > 0);
    return result;
}

void TRKDoStep(TRKBuffer *buffer)
{
    u32 range_start;
    u32 range_end;
    u8 command;
    u8 options;
    u8 count;
    u32 pc;
    int result;

    if (buffer->length < 3) {
        reply(buffer, 2);
        return;
    }

    TRKSetBufferPosition(buffer, 0);
    result = TRKReadBuffer1_ui8(buffer, &command);
    if (result == 0) result = TRKReadBuffer1_ui8(buffer, &options);

    switch (options) {
    case 0:
    case 0x10:
        if (result == 0) result = TRKReadBuffer1_ui8(buffer, &count);
        if (count < 1) {
            reply(buffer, 0x11);
            return;
        }
        break;
    case 1:
    case 0x11:
        if (buffer->length != 10) {
            reply(buffer, 2);
            return;
        }
        if (result == 0) result = TRKReadBuffer1_ui32(buffer, &range_start);
        if (result == 0) result = TRKReadBuffer1_ui32(buffer, &range_end);
        pc = TRKTargetGetPC();
        if (pc < range_start || pc > range_end) {
            reply(buffer, 0x11);
            return;
        }
        break;
    default:
        reply(buffer, 0x12);
        return;
    }

    if (!TRKTargetStopped()) {
        reply(buffer, 0x16);
        return;
    }

    result = reply(buffer, 0);
    if (result == 0) {
        switch (options) {
        case 0:
        case 0x10:
            TRKTargetSingleStep(count, options == 0x10);
            break;
        case 1:
        case 0x11:
            TRKTargetStepOutOfRange(range_start, range_end, options == 0x11);
            break;
        }
    }
}
