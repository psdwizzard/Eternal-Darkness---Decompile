typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 unk0;
    u32 unk4;
    u32 length;
    u32 position;
    u8 data[0x880];
} TRKBuffer;

extern void fn_80003130(void *, const void *, u32);

int fn_800EFBC8(TRKBuffer *buffer, const u8 *data, u32 length)
{
    int err = 0;

    if (length == 0)
        return 0;

    if (0x880 - buffer->position < length) {
        err = 0x301;
        length = 0x880 - buffer->position;
    }

    if (length == 1)
        buffer->data[buffer->position] = *data;
    else
        fn_80003130(buffer->data + buffer->position, data, length);

    buffer->position += length;
    buffer->length = buffer->position;
    return err;
}
