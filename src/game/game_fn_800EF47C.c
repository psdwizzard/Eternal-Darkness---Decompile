typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 unk0;
    u32 unk4;
    u32 length;
    u32 position;
    u8 data[1];
} TRKBuffer;

extern void TRK_memcpy(void *, const void *, u32);
extern int gTRKBigEndian[];

int TRKReadBuffer_ui32(TRKBuffer *buffer, u32 *out, int count)
{
    int read_err;
    u32 *destination;
    u32 amount;
    int *endian = gTRKBigEndian;
    u32 *cursor = out;
    int i = 0;
    int err = 0;

    while (err == 0 && i < count) {
        u32 value;
        u32 remaining;

        if (*endian != 0) {
            destination = cursor;
        } else {
            destination = &value;
        }
        amount = 4;
        read_err = 0;
        remaining = buffer->length - buffer->position;
        if (amount > remaining) {
            read_err = 0x302;
            amount = remaining;
        }
        TRK_memcpy(destination, buffer->data + buffer->position, amount);
        buffer->position += amount;
        if (*endian == 0 && read_err == 0) {
            u8 *source = (u8 *)destination;
            u8 *result = (u8 *)cursor;
            result[0] = source[3];
            result[1] = source[2];
            result[2] = source[1];
            result[3] = source[0];
        }
        err = read_err;
        cursor++;
        i++;
    }
    return err;
}
