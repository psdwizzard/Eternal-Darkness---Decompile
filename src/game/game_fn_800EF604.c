typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct TRKBuffer {
    u32 unk0;
    u32 unk4;
    u32 length;
    u32 position;
    u8 data[1];
} TRKBuffer;

extern void TRK_memcpy(void *, const void *, u32);
extern int gTRKBigEndian[];

static inline int TRKReadBuffer(TRKBuffer *buffer, void *data, unsigned long length)
{
    int error = 0;
    u32 bytesLeft;

    if (length == 0) {
        return 0;
    }

    bytesLeft = buffer->length - buffer->position;
    if (length > bytesLeft) {
        error = 0x302;
        length = bytesLeft;
    }

    TRK_memcpy(data, buffer->data + buffer->position, length);
    buffer->position += length;
    return error;
}

int TRKReadBuffer1_ui64(TRKBuffer *buffer, u64 *out)
{
    u8 *destination;
    u8 *byte_data;
    u8 swap_buffer[sizeof(out)];
    int read_err;

    if (gTRKBigEndian[0] != 0) {
        destination = (u8 *)out;
    } else {
        destination = swap_buffer;
    }
    read_err = TRKReadBuffer(buffer, destination, sizeof(*out));
    if (gTRKBigEndian[0] == 0 && read_err == 0) {
        byte_data = (u8 *)out;
        byte_data[0] = destination[7];
        byte_data[1] = destination[6];
        byte_data[2] = destination[5];
        byte_data[3] = destination[4];
        byte_data[4] = destination[3];
        byte_data[5] = destination[2];
        byte_data[6] = destination[1];
        byte_data[7] = destination[0];
    }
    return read_err;
}
