typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int fn_800EFD6C(int *, TRKBuffer **);
extern int fn_800EFA84(TRKBuffer *, u32);
extern int fn_800EFAE8(TRKBuffer *, u16);
extern int fn_800EF994(TRKBuffer *, u8 *, u32);
extern int fn_800F3054(TRKBuffer *, int *, int, int, int);
extern TRKBuffer *TRKGetBuffer(int);
extern int fn_800EFC6C(TRKBuffer *, u32);
extern int fn_800EF86C(TRKBuffer *, u8 *);
extern int fn_800EF7B4(TRKBuffer *, u16 *);
extern int fn_800EF56C(TRKBuffer *, u8 *, u32);
extern int fn_800EF2A0(TRKBuffer *);
extern void fn_800EFCDC(int);

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
int fn_800F31F8(u32 file_handle, u8 *data, u32 *count, u8 *io_result, int need_reply, int read)
{
    int exit;
    int result;
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

        result = fn_800EFD6C(&buffer_id, &buffer);

        if (result == 0)
            result = append(buffer, read ? DSMSG_ReadFile : DSMSG_WriteFile);

        if (result == 0)
            result = fn_800EFA84(buffer, file_handle);

        if (result == 0)
            result = fn_800EFAE8(buffer, length);

        if (!read && result == 0)
            result = fn_800EF994(buffer, data + done, length);

        if (result == 0) {
            if (need_reply) {
                reply_length = 0;
                reply_io_result = 0;

                result = fn_800F3054(buffer, &reply_buffer_id, read ? 5 : 5, 3, !(read && file_handle == 0));
                if (result == 0) {
                    reply_buffer = TRKGetBuffer(reply_buffer_id);
                    fn_800EFC6C(reply_buffer, 2);
                }

                if (result == 0)
                    result = fn_800EF86C(reply_buffer, &reply_io_result);

                if (result == 0)
                    result = fn_800EF7B4(reply_buffer, &reply_length);

                if (read && result == 0) {
                    if (reply_buffer->length != reply_length + 5) {
                        reply_length = reply_buffer->length - 5;
                        if (reply_io_result == 0)
                            reply_io_result = 1;
                    }

                    if (reply_length <= length)
                        result = fn_800EF56C(reply_buffer, data + done, reply_length);
                }

                if (reply_length != length) {
                    if ((!read || reply_length >= length) && reply_io_result == 0)
                        reply_io_result = 1;
                    length = reply_length;
                    exit = 1;
                }

                *io_result = reply_io_result;
                fn_800EFCDC(reply_buffer_id);
            } else {
                result = fn_800EF2A0(buffer);
            }
        }

        fn_800EFCDC(buffer_id);
        done += length;
    }

    *count = done;
    return result;
}
