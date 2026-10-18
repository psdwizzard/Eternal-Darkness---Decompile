typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int TRKGetFreeBuffer(int *, TRKBuffer **);
extern int TRKAppendBuffer1_ui32(TRKBuffer *, u32);
extern int TRKAppendBuffer1_ui16(TRKBuffer *, u16);
extern int TRKAppendBuffer_ui8(TRKBuffer *, const void *, int);
extern int TRKRequestSend(TRKBuffer *, int *, int, int, int);
extern TRKBuffer *TRKGetBuffer(int);
extern int TRKSetBufferPosition(TRKBuffer *, u32);
extern int TRKReadBuffer1_ui8(TRKBuffer *, u8 *);
extern int TRKReadBuffer1_ui16(TRKBuffer *, u16 *);
extern int TRKReadBuffer_ui8(TRKBuffer *, u8 *, int);
extern int TRKMessageSend(TRKBuffer *);
extern void TRKReleaseBuffer(int);

enum {
    DSMSG_WriteFile = 0xD0,
    DSMSG_ReadFile = 0xD1
};

static inline int append(TRKBuffer *buffer, u8 value)
{
    if (buffer->position >= 0x880)
        return 0x301;
    buffer->data[buffer->position++] = value;
    buffer->length++;
    return 0;
}

/* TRKSuppAccessFile */
int TRKSuppAccessFile(u32 file_handle, u8 *data, u32 *count, u8 *io_result, int need_reply, int read)
{
    int result;
    int exit;
    int reply_buffer_id;
    TRKBuffer *reply_buffer;
    int buffer_id;
    TRKBuffer *buffer;
    u32 length;
    u32 done;
    u8 reply_io_result;
    u16 reply_length;

    if (data == 0 || *count == 0)
        return 2;

    exit = 0;
    *io_result = 0;
    done = 0;
    result = 0;
    while (!exit && done < *count && result == 0 && *io_result == 0) {
        if (*count - done > 0x800)
            length = 0x800;
        else
            length = *count - done;

        result = TRKGetFreeBuffer(&buffer_id, &buffer);

        if (result == 0)
            result = append(buffer, read ? DSMSG_ReadFile : DSMSG_WriteFile);

        if (result == 0)
            result = TRKAppendBuffer1_ui32(buffer, (unsigned long)file_handle);

        if (result == 0)
            result = TRKAppendBuffer1_ui16(buffer, length);

        if (!read && result == 0)
            result = TRKAppendBuffer_ui8(buffer, data + done, length);

        if (result == 0) {
            if (need_reply) {
                reply_length = 0;
                reply_io_result = 0;

                result = TRKRequestSend(buffer, &reply_buffer_id, read ? 5 : 5, 3, !(read && file_handle == 0));
                if (result == 0) {
                    reply_buffer = TRKGetBuffer(reply_buffer_id);
                    TRKSetBufferPosition(reply_buffer, 2);
                }

                if (result == 0)
                    result = TRKReadBuffer1_ui8(reply_buffer, &reply_io_result);

                if (result == 0)
                    result = TRKReadBuffer1_ui16(reply_buffer, &reply_length);

                if (read && result == 0) {
                    if (reply_buffer->length != reply_length + 5) {
                        reply_length = reply_buffer->length - 5;
                        if (reply_io_result == 0)
                            reply_io_result = 1;
                    }

                    if (reply_length <= length)
                        result = TRKReadBuffer_ui8(reply_buffer, data + done, reply_length);
                }

                if (reply_length != length) {
                    if ((!read || reply_length >= length) && reply_io_result == 0)
                        reply_io_result = 1;
                    length = reply_length;
                    exit = 1;
                }

                *io_result = reply_io_result;
                TRKReleaseBuffer(reply_buffer_id);
            } else {
                result = TRKMessageSend(buffer);
            }
        }

        TRKReleaseBuffer(buffer_id);
        done += length;
    }

    *count = done;
    return result;
}
