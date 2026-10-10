typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Stream {
    u8 *cur;
    u8 pad[12];
} Stream;

typedef struct MotionPlane {
    u8 pad00[0x10];
    u16 blocks[4];
    int offsets[4];
    u16 width;
    u8 pad2A[6];
    u8 x_shift;
    u8 y_shift;
    u8 pad32[2];
    u8 count;
    u8 pad35[3];
} MotionPlane;

typedef struct Decoder {
    MotionPlane planes[3];
    u8 pad[0x31DC - 3 * sizeof(MotionPlane)];
    Stream streams[3];
} Decoder;

typedef struct BlockInfo {
    u8 value;
    u8 flags;
} BlockInfo;

typedef struct PlaneCursor {
    u8 pad00[0x8];
    BlockInfo *block_info;
    u8 pad0C[0x8];
    int destination;
    int reference;
    u8 pad1C[0x18];
} PlaneCursor;

typedef struct FrameContext {
    PlaneCursor planes[3];
} FrameContext;

extern void fn_80104BBC(int destination, u16 width, int reference,
                        u16 reference_width, int x_half, int y_half);
extern void fn_80105804(Decoder *decoder, int destination, int reference,
                        u16 width, u32 mode, int base, u16 base_width,
                        int plane, int x_half, int y_half);

static inline void copy_raw_block(u8 **cur, u8 *dst, u16 stride)
{
    u8 *row = dst + stride;

    dst[0] = *(*cur)++;
    dst[1] = *(*cur)++;
    dst[2] = *(*cur)++;
    dst[3] = *(*cur)++;
    row[0] = *(*cur)++;
    row[1] = *(*cur)++;
    row[2] = *(*cur)++;
    row[3] = *(*cur)++;
    row += stride;
    row[0] = *(*cur)++;
    row[1] = *(*cur)++;
    row[2] = *(*cur)++;
    row[3] = *(*cur)++;
    row += stride;
    row[0] = *(*cur)++;
    row[1] = *(*cur)++;
    row[2] = *(*cur)++;
    row[3] = *(*cur)++;
}

void fn_80105DE0(Decoder *decoder, FrameContext *context, int x, int y)
{
    MotionPlane *source;
    PlaneCursor *cursor;
    u8 **stream;
    u16 *block_id;
    int *offset;
    int reference;
    int base;
    int offset_value;
    int destination;
    int block;
    int plane;
    int x_half;
    int y_half;
    u32 mode;
    u8 count;
    u16 width;

    y_half = y & 1;
    x_half = x & 1;
    cursor = context->planes;
    source = decoder->planes;
    plane = 0;
    base = (x >> 1) + cursor->reference + ((y >> 1) - 16) * decoder->planes[0].width - 32;
    do {
        block_id = source->blocks;
        offset = source->offsets;
        count = source->count;
        reference = (x >> (source->x_shift + 1)) +
            ((y >> (source->y_shift + 1)) * source->width + cursor->reference);
        stream = &((Stream *)((u8 *)decoder + 0x31DC) + plane)->cur;
        block = 0;

        while (block < count) {
            u16 id = *block_id++;
            offset_value = *offset++;
            destination = cursor->destination + offset_value;
            mode = cursor->block_info[id].flags & 0xF;
            if (mode == 6) {
                copy_raw_block(stream,(u8 *)destination, source->width);
            } else if (mode == 0) {
                width = source->width;
                fn_80104BBC(destination, width, reference + offset_value, width,
                            x_half, y_half);
            } else {
                fn_80105804(decoder, destination, reference + offset_value,
                            source->width, mode, base, decoder->planes[0].width,
                            plane, x_half, y_half);
            }
            block++;
        }
        plane++;
        cursor++;
        source++;
    } while (plane < 3);
}
