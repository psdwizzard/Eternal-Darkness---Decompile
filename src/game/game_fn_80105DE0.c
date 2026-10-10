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
    u8 *destination;
    u8 *reference;
    u8 pad1C[0x18];
} PlaneCursor;

typedef struct FrameContext {
    PlaneCursor planes[3];
} FrameContext;

extern void fn_80104BBC(u8 *destination, u16 width, u8 *reference,
                        u16 reference_width, int x_half, int y_half);
extern void fn_80105804(Decoder *decoder, u8 *destination, u8 *reference,
                        u16 width, u32 mode, u8 *base, u16 base_width,
                        int plane, int x_half, int y_half);

static inline void copy_raw_block(u8 **stream, u8 *dst, u16 width)
{
    u8 *row;

    row = dst + width;

    dst[0] = *(*stream)++;
    dst[1] = *(*stream)++;
    dst[2] = *(*stream)++;
    dst[3] = *(*stream)++;
    row[0] = *(*stream)++;
    row[1] = *(*stream)++;
    row[2] = *(*stream)++;
    row[3] = *(*stream)++;
    row += width;
    row[0] = *(*stream)++;
    row[1] = *(*stream)++;
    row[2] = *(*stream)++;
    row[3] = *(*stream)++;
    row += width;
    row[0] = *(*stream)++;
    row[1] = *(*stream)++;
    row[2] = *(*stream)++;
    row[3] = *(*stream)++;
}

void fn_80105DE0(register Decoder *input_decoder, register FrameContext *context,
                 register int input_x, register int input_y)
{
    register Decoder *decoder;
    register u8 **stream;
    register PlaneCursor *cursor;
    register MotionPlane *source;
    register int y_half;
    register int x_half;
    register int plane;
    register int block;
    register u8 *reference;
    register int *offset;
    register u16 *block_id;
    register int count;
    register u8 *base;
    register u8 *stream_base;
    register int y;
    register int x;
    register int x_offset;
    register int y_offset;
    register u8 *base_reference;
    register u8 *base_sum;
    register int reference_x;
    register int reference_y;
    register u8 *reference_origin;
    int offset_value;
    register u8 *destination;
    u32 mode;
    register u16 width;

    /* ASM: addi preserves the retail register-copy encoding; equivalent C
     * assignments are emitted as mr by this compiler. */
    asm {
        addi x, input_x, 0
        addi y, input_y, 0
        addi decoder, input_decoder, 0
    }

    x_offset = x >> 1;
    y_half = y & 1;
    x_half = x & 1;
    /* ASM: addi retains zero-offset copies, which C lowers to mr. */
    asm {
        addi cursor, context, 0
        addi source, decoder, 0
        addi stream_base, decoder, 0
    }
    plane = 0;
    y_offset = ((y >> 1) - 16) * input_decoder->planes[0].width;
    base_reference = context->planes[0].reference;
    /* ASM: add/add/addi preserve the retail address-addition order, which
     * MWCC reassociates when expressed as C pointer arithmetic. */
    asm {
        add base_sum, base_reference, x_offset
        add base, base_sum, y_offset
        addi base, base, -32
    }
    do {
        block_id = source->blocks;
        offset = source->offsets;
        count = source->count;
        reference_x = x >> (source->x_shift + 1);
        reference_y = (y >> (source->y_shift + 1)) * source->width;
        reference_origin = cursor->reference;
        /* ASM: add/add retain the retail grouping of the motion offset
         * and reference address; MWCC reassociates the equivalent C sum. */
        asm {
            add reference, reference_y, reference_origin
            add reference, reference_x, reference
        }
        /* ASM: addi keeps the stream address in a register; MWCC folds the
         * equivalent C addition into every load and store instead. */
        asm { addi stream, stream_base, 0x31DC }
        block = 0;

        while (block < count) {
            u32 id = *block_id++;
            offset_value = *offset++;
            mode = cursor->block_info[id].flags & 0xF;
            destination = cursor->destination + offset_value;
            if (mode == 6) {
                copy_raw_block(stream, destination, source->width);
            } else {
                u8 *reference_block = reference + offset_value;
                if (mode == 0) {
                    register u8 *copy_destination;
                    register int copy_x;
                    register int copy_y;
                    register u16 copy_stride;

                    width = source->width;
                    /* ASM: addi preserves the retail argument-copy encoding;
                     * equivalent C assignments compile to mr. */
                    asm {
                        addi copy_destination, destination, 0
                        addi copy_x, x_half, 0
                        addi copy_stride, width, 0
                        addi copy_y, y_half, 0
                    }
                    fn_80104BBC(copy_destination, width, reference_block,
                                copy_stride, copy_x, copy_y);
                } else {
                    fn_80105804(decoder, destination, reference_block,
                                source->width, mode, base,
                                decoder->planes[0].width, plane,
                                x_half, y_half);
                }
            }
            block++;
        }
        plane++;
        cursor++;
        source++;
        stream_base += sizeof(Stream);
    } while (plane < 3);
}
