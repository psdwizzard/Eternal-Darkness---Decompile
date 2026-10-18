typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int TRKGetFreeBuffer(int *, TRKBuffer **);
extern int TRKAppendBuffer1_ui16(TRKBuffer *, u16);
extern int TRKAppendBuffer_ui8(TRKBuffer *, const void *, u32);
extern int TRKRequestSend(TRKBuffer *, int *, int, int, int);
extern TRKBuffer *TRKGetBuffer(int);
extern int TRKSetBufferPosition(TRKBuffer *, int);
extern int TRKReadBuffer1_ui8(TRKBuffer *, u8 *);
extern int TRKReadBuffer1_ui32(TRKBuffer *, u32 *);
extern void TRKReleaseBuffer(int);
extern u32 strlen(const char *);

static int append(TRKBuffer *buffer, u8 value)
{
    if (buffer->position >= 0x880)
        return 0x301;
    buffer->data[buffer->position++] = value;
    buffer->length++;
    return 0;
}

int HandleOpenFileSupportRequest(const char *name, u8 kind, u32 *value, u8 *status)
{
    int reply_buffer;
    int first_buffer;
    TRKBuffer *buffer;
    TRKBuffer *reply;
    int result;

    *value = 0;
    result = TRKGetFreeBuffer(&first_buffer, &buffer);
    if (result == 0)
        result = append(buffer, 0xD2);
    if (result == 0)
        result = append(buffer, kind);
    if (result == 0)
        result = TRKAppendBuffer1_ui16(buffer, (u16)(strlen(name) + 1));
    if (result == 0)
        result = TRKAppendBuffer_ui8(buffer, name, strlen(name) + 1);
    if (result == 0) {
        *status = 0;
        result = TRKRequestSend(buffer, &reply_buffer, 7, 3, 0);
        if (result == 0) {
            reply = TRKGetBuffer(reply_buffer);
            TRKSetBufferPosition(reply, 2);
        }
        if (result == 0)
            result = TRKReadBuffer1_ui8(reply, status);
        if (result == 0)
            result = TRKReadBuffer1_ui32(reply, value);
        TRKReleaseBuffer(reply_buffer);
    }
    TRKReleaseBuffer(first_buffer);
    return result;
}
