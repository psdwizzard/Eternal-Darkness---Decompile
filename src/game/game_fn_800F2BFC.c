typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int TRKGetFreeBuffer(int *, TRKBuffer **);
extern int TRKAppendBuffer1_ui32(TRKBuffer *, u32);
extern int TRKRequestSend(TRKBuffer *, int *, int, int, int);
extern TRKBuffer *TRKGetBuffer(int);
extern int TRKSetBufferPosition(TRKBuffer *, int);
extern int TRKReadBuffer1_ui8(TRKBuffer *, u8 *);
extern int TRKReadBuffer1_ui32(TRKBuffer *, u32 *);
extern void TRKReleaseBuffer(int);

static int append(TRKBuffer *buffer, u8 value)
{
    if (buffer->position >= 0x880)
        return 0x301;
    buffer->data[buffer->position++] = value;
    buffer->length++;
    return 0;
}

int HandlePositionFileSupportRequest(u32 arg0, u32 *arg1, u8 arg2, u8 *arg3)
{
    int reply_buffer;
    int first_buffer;
    TRKBuffer *buffer;
    TRKBuffer *reply;
    int result;

    result = TRKGetFreeBuffer(&first_buffer, &buffer);
    if (result == 0)
        result = append(buffer, 0xD4);
    if (result == 0)
        result = TRKAppendBuffer1_ui32(buffer, arg0);
    if (result == 0)
        result = TRKAppendBuffer1_ui32(buffer, *arg1);
    if (result == 0)
        result = append(buffer, arg2);
    if (result == 0) {
        *arg3 = 0;
        result = TRKRequestSend(buffer, &reply_buffer, 3, 3, 0);
        if (result == 0) {
            reply = TRKGetBuffer(reply_buffer);
            TRKSetBufferPosition(reply, 2);
        }
        if (result == 0)
            result = TRKReadBuffer1_ui8(reply, arg3);
        if (result == 0)
            result = TRKReadBuffer1_ui32(reply, arg1);
        else
            *arg1 = -1;
        TRKReleaseBuffer(reply_buffer);
    }
    TRKReleaseBuffer(first_buffer);
    return result;
}
