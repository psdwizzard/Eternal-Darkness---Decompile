#include "src/game/types.h"

typedef struct CodecComment {
    u8 **comments;
    s32 *lengths;
    s32 count;
    u8 *vendor;
} CodecComment;

extern s32 fn_8022E868(void *stream, s32 bits);
extern void *fn_8022F780(s32 size);
extern void *memset(void *dest, int value, unsigned long size);

static inline void readBytes(void *stream, u8 *cursor, s32 remaining)
{
    while (remaining--) {
        *cursor++ = fn_8022E868(stream, 8);
    }
}

/* Decode the vendor string and user comments from a codec header. */
s32 fn_80232430(CodecComment *comment, void *stream)
{
    s32 i;
    s32 length;

    length = fn_8022E868(stream, 32);
    if (length < 0) goto error;
    comment->vendor = fn_8022F780(length + 1);
    readBytes(stream, comment->vendor, length);

    comment->count = fn_8022E868(stream, 32);
    if (comment->count < 0) goto error;
    comment->comments = fn_8022F780(comment->count + 4);
    comment->lengths = fn_8022F780(comment->count + 4);
    for (i = 0; i < comment->count; i++) {
        s32 length = fn_8022E868(stream, 32);
        if (length < 0) goto error;
        comment->lengths[i] = length;
        comment->comments[i] = fn_8022F780(length + 1);
        readBytes(stream, comment->comments[i], length);
    }
    if (fn_8022E868(stream, 1) != 1) goto error;
    return 0;

error:
    memset(comment, 0, sizeof(*comment));
    return -0x85;
}
