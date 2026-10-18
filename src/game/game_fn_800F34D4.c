typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int TRKGetFreeBuffer(int *, TRKBuffer **);
extern int TRKTargetAddStopInfo(TRKBuffer *);
extern int TRKTargetAddExceptionInfo(TRKBuffer *);
extern int TRKRequestSend(TRKBuffer *, int *, int, int, int);
extern void TRKReleaseBuffer(int);

static int append(TRKBuffer *buffer, u8 value)
{
    if (buffer->position >= 0x880)
        return 0x301;
    buffer->data[buffer->position++] = value;
    buffer->length++;
    return 0;
}

int TRKDoNotifyStopped(u8 command)
{
    int reply_buffer;
    int first_buffer;
    TRKBuffer *buffer;
    int append_result;
    int result;

    result = TRKGetFreeBuffer(&first_buffer, &buffer);
    if (result == 0) {
        append_result = append(buffer, command);
        if (append_result == 0) {
            if (command == 0x90)
                TRKTargetAddStopInfo(buffer);
            else
                TRKTargetAddExceptionInfo(buffer);
        }
        result = TRKRequestSend(buffer, &reply_buffer, 2, 3, 1);
        if (result == 0)
            TRKReleaseBuffer(reply_buffer);
        TRKReleaseBuffer(first_buffer);
    }
    return result;
}
