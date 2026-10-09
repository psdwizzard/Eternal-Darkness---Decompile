typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 unk0;
    u32 unk4;
    u32 length;
    u32 position;
    u8 data[0x880];
} TRKBuffer;

static int append_byte(TRKBuffer *buffer, u8 value)
{
    if (buffer->position >= 0x880)
        return 0x301;
    buffer->data[buffer->position++] = value;
    buffer->length++;
    return 0;
}

int fn_800EF994(TRKBuffer *buffer, const void *data, int length)
{
    const u8 *bytes = data;
    int i = 0;
    int err = 0;

    for (; err == 0 && i < length; i++, bytes++)
        err = append_byte(buffer, *bytes);
    return err;
}
