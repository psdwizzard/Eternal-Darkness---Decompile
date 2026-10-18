#include "src/game/types.h"

typedef struct CodecComment {
    u8 **comments;
    s32 *lengths;
    s32 count;
    u8 *vendor;
} CodecComment;

extern s32 oggpack_read(void *stream, s32 bits);
extern void *fn_8022F780(s32 size);
extern void *memset(void *dest, int value, unsigned long size);

static inline void readBytes(void *stream, u8 *cursor, s32 remaining)
{
    while (remaining--) {
        *cursor++ = oggpack_read(stream, 8);
    }
}

/* Decode the vendor string and user comments from a codec header. */
s32 _vorbis_unpack_comment(CodecComment *comment, void *stream)
{
    s32 i;
    s32 length;

    length = oggpack_read(stream, 32);
    if (length < 0) goto error;
    comment->vendor = fn_8022F780(length + 1);
    readBytes(stream, comment->vendor, length);

    comment->count = oggpack_read(stream, 32);
    if (comment->count < 0) goto error;
    comment->comments = fn_8022F780(comment->count + 4);
    comment->lengths = fn_8022F780(comment->count + 4);
    for (i = 0; i < comment->count; i++) {
        s32 length = oggpack_read(stream, 32);
        if (length < 0) goto error;
        comment->lengths[i] = length;
        comment->comments[i] = fn_8022F780(length + 1);
        readBytes(stream, comment->comments[i], length);
    }
    if (oggpack_read(stream, 1) != 1) goto error;
    return 0;

error:
    memset(comment, 0, sizeof(*comment));
    return -0x85;
}
