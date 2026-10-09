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

int fn_800EFB3C(TRKBuffer *buffer, void *data, u32 length)
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

    fn_80003130(data, buffer->data + buffer->position, length);
    buffer->position += length;
    return error;
}
