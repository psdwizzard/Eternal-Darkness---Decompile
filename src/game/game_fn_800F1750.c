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
extern int TRKReadBuffer1_ui32(TRKBuffer *, u32 *);
extern int TRKReadBuffer(TRKBuffer *, void *, u32);
extern int TRKTargetAccessMemory(void *, u32, u32 *, int, int);
extern int TRKAppendBuffer1_ui16(TRKBuffer *, u16);
extern int TRKMessageSend(TRKBuffer *);

static inline void append(TRKBuffer *buffer, u8 value)
{
    if (buffer->position < 0x880) {
        buffer->data[buffer->position++] = value;
        buffer->length++;
    }
}

static inline int sendReply(TRKBuffer *buffer)
{
    int result;
    int retry = 3;

    do {
        result = TRKMessageSend(buffer);
        retry--;
        if (result == 0) break;
    } while (retry > 0);
    return result;
}

/* MetroTRK: write target memory and send an acknowledgement. */
int TRKDoWriteMemory(TRKBuffer *buffer)
{
    u8 data[0x800];
    u32 address;
    u32 size;
    u16 length;
    u8 message_command;
    u8 options;
    int result;
    u8 status;

    if (buffer->length <= 8) {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 2);
        return sendReply(buffer);
    }

    TRKSetBufferPosition(buffer, 0);
    result = TRKReadBuffer1_ui8(buffer, &message_command);
    if (result == 0) result = TRKReadBuffer1_ui8(buffer, &options);
    if (result == 0) result = TRKReadBuffer1_ui16(buffer, &length);
    if (result == 0) result = TRKReadBuffer1_ui32(buffer, &address);

    if (options & 2) {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 0x12);
        return sendReply(buffer);
    }

    if (buffer->length != length + 8 || length > 0x800) {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 0x11);
        return sendReply(buffer);
    }

    if (result == 0) {
        size = length;
        result = TRKReadBuffer(buffer, data, length);
        if (result == 0) {
            result = TRKTargetAccessMemory(data, address, &size,
                                ((options >> 3) & 1) ^ 1, 0);
        }
        length = size;
    }

    if (result == 0) {
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, 0);
    }
    if (result == 0) result = TRKAppendBuffer1_ui16(buffer, length);

    if (result != 0) {
        switch (result) {
        case 0x702: status = 0x15; break;
        case 0x700: status = 0x13; break;
        case 0x704: status = 0x21; break;
        case 0x705: status = 0x22; break;
        case 0x706: status = 0x20; break;
        default: status = 3; break;
        }
        TRKResetBuffer(buffer, 1);
        append(buffer, 0x80);
        append(buffer, status);
        result = sendReply(buffer);
    } else {
        result = sendReply(buffer);
    }
    return result;
}
