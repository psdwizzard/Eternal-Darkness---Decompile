typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 unk0;
    u32 unk4;
    u32 length;
    u32 position;
    u8 data[0x880];
} TRKBuffer;

extern void TRK_memset(void *, int, u32);

void TRKResetBuffer(TRKBuffer *buffer, u8 preserve_data)
{
    buffer->length = 0;
    buffer->position = 0;
    if (preserve_data == 0)
        TRK_memset(buffer->data, 0, 0x880);
}
