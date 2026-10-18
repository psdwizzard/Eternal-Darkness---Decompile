typedef unsigned char u8;
typedef unsigned int u32;

typedef enum BufferIndex {
    BUFFER_0,
    BUFFER_1
} BufferIndex;

typedef struct Stream {
    u32 remaining;
    u32 refill_size;
    BufferIndex buffer_index;
    void* cursor;
    u8 command[0x20];
    u32 offset;
    u32 length;
    int mode;
    void* buffers[2];
    u32 buffer_size;
    void* source;
} Stream;

typedef struct ArchiveState {
    u8 pad[0x10];
    u32 start;
    u32 size;
} ArchiveState;

extern ArchiveState lbl_805BB1E0;
extern int OSReceiveMessage(void*, u32*, int);
extern void fn_8015B628(Stream*);

void* fn_8015B708(Stream* stream)
{
    u32 result[4];

    OSReceiveMessage(stream->source, result, 1);
    stream->refill_size = stream->length;
    stream->remaining -= stream->length;
    stream->offset += stream->length;
    stream->buffer_index ^= 1;
    stream->cursor = stream->buffers[stream->buffer_index];

    if (stream->mode == 1 && stream->offset >= lbl_805BB1E0.size) {
        stream->offset = lbl_805BB1E0.start;
    }

    if (stream->remaining != 0) {
        fn_8015B628(stream);
    }
    return stream->cursor;
}
