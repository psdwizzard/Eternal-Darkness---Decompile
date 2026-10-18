typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int TRKSetBufferPosition(TRKBuffer *, u32);
extern void TRKResetBuffer(TRKBuffer *, u8);
extern int TRKReadBuffer1_ui8(TRKBuffer *, u8 *);
extern int TRKReadBuffer1_ui16(TRKBuffer *, u16 *);
extern int TRKMessageSend(TRKBuffer *);
extern int TRKTargetAccessDefault(u32, u32, TRKBuffer *, u32 *, int);
extern int TRKTargetAccessFP(u32, u32, TRKBuffer *, u32 *, int);
extern int TRKTargetAccessExtended1(u32, u32, TRKBuffer *, u32 *, int);
extern int TRKTargetAccessExtended2(u32, u32, TRKBuffer *, u32 *, int);

static inline void append(TRKBuffer *buffer, u8 value)
{
    if (buffer->position < 0x880) {
        buffer->data[buffer->position++] = value;
        buffer->length++;
    }
}

void TRKDoWriteRegisters(TRKBuffer *buffer)
{
    u32 size;
    u16 start;
    u16 end;
    u8 message_command;
    u8 options;
    int result;
    int retry;
    u8 status;

    if (buffer->length <= 6) {
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
    if (result == 0) result = TRKReadBuffer1_ui16(buffer, &start);
    if (result == 0) result = TRKReadBuffer1_ui16(buffer, &end);

    if (start > end) {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 0x14);
        retry = 3;
        do {
            result = TRKMessageSend(buffer);
            retry--;
            if (result == 0) break;
        } while (retry > 0);
        return;
    }

    switch (options) {
    case 0:
        result = TRKTargetAccessDefault(start, end, buffer, &size, 0);
        break;
    case 1:
        result = TRKTargetAccessFP(start, end, buffer, &size, 0);
        break;
    case 2:
        result = TRKTargetAccessExtended1(start, end, buffer, &size, 0);
        break;
    case 3:
        result = TRKTargetAccessExtended2(start, end, buffer, &size, 0);
        break;
    default:
        result = 0x703;
        break;
    }

    if (result == 0) {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 0);
    }

    if (result != 0) {
        switch (result) {
        case 0x703: status = 0x12; break;
        case 0x701: status = 0x14; break;
        case 0x302: status = 2; break;
        case 0x702: status = 0x15; break;
        case 0x704: status = 0x21; break;
        case 0x705: status = 0x22; break;
        case 0x706: status = 0x20; break;
        default: status = 3; break;
        }
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, status);
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
