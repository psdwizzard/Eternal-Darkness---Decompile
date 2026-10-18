typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Stream {
    u32 source;
    u32 pad4;
    u32 buffer_index;
    u32 padC;
    u8 command[0x20];
    u32 offset;
    u32 length;
    int mode;
    void* buffers[2];
    u32 buffer_size;
} Stream;

typedef struct ArchiveState {
    u8 pad[0x14];
    u32 size;
} ArchiveState;

extern volatile ArchiveState lbl_805BB1E0;
extern void DCInvalidateRange(void*, u32);
extern void fn_8015B7CC(void);
extern void ARQPostRequest(void*, Stream*, int, int, u32, void*, u32, void (*)(void));

void fn_8015B628(Stream* stream)
{
    u32 length;
    void* buffer;

    if (stream->source != 0) {
        length = stream->buffer_size;
        buffer = stream->buffers[stream->buffer_index ^ 1];
        if (stream->source < length) {
            length = stream->source;
        }
        stream->length = length;

        if (stream->mode == 1 && stream->offset + stream->length > lbl_805BB1E0.size) {
            stream->length = lbl_805BB1E0.size - stream->offset;
        }

        DCInvalidateRange(buffer, (stream->length + 31) & ~31);
        ARQPostRequest(stream->command, stream, 1, 0, stream->offset, buffer,
                    (stream->length + 31) & ~31, fn_8015B7CC);
    }
}
