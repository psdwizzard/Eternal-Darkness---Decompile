typedef unsigned char u8;
typedef unsigned short u16;

typedef struct MotionPlane {
    u8 pad00[0x18];
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
} Decoder;

typedef struct PlaneCursor {
    u8 pad00[0x14];
    int destination;
    int reference;
    u8 pad1C[0x18];
} PlaneCursor;

typedef struct FrameContext {
    PlaneCursor planes[3];
} FrameContext;

extern void _MotionComp(int destination, u16 width, int reference,
                        u16 reference_width, int x_half, int y_half);

void MotionComp(Decoder *decoder, FrameContext *context, int x, int y)
{
    PlaneCursor *cursor;
    MotionPlane *source;
    int y_half;
    int x_half;
    int plane;
    int block;
    int *offset;
    int count;
    int reference;
    int offset_value;
    int reference_block;
    int destination_block;
    u16 width;

    y_half = y & 1;
    x_half = x & 1;
    cursor = context->planes;
    source = decoder->planes;
    plane = 0;
    do {
        offset = source->offsets;
        block = 0;
        count = source->count;
        reference = cursor->reference +
            (y >> (source->y_shift + 1)) * source->width +
            (x >> (source->x_shift + 1));

        while (block < count) {
            offset_value = *offset;
            width = source->width;
            reference_block = reference + offset_value;
            destination_block = cursor->destination + offset_value;
            offset++;
            _MotionComp(destination_block, width, reference_block, width,
                        x_half, y_half);
            block++;
        }
        plane++;
        cursor++;
        source++;
    } while (plane < 3);
}
