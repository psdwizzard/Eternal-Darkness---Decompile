typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 unk0;
    u32 unk4;
    u32 length;
    u32 position;
    u8 data[0x880];
} TRKBuffer;

int TRKSetBufferPosition(TRKBuffer *buffer, u32 position)
{
    int err = 0;

    if (position > 0x880) {
        err = 0x301;
    } else {
        buffer->position = position;
        if (position > buffer->length)
            buffer->length = position;
    }
    return err;
}
