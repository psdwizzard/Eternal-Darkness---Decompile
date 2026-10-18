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
    u8 *destination;
    u8 *reference;
    u8 pad1C[0x18];
} PlaneCursor;

typedef struct FrameContext {
    PlaneCursor planes[3];
} FrameContext;

extern void fn_80104BBC(u8 *destination, int width, u8 *reference,
                        int reference_width, int x_half, int y_half);

void fn_8010528C(register Decoder *decoder, register FrameContext *context,
                 register int x, register int y)
{
    register PlaneCursor *cursor;
    register MotionPlane *source;
    register int y_half;
    register int x_half;
    int plane;
    int block;
    int *offset;
    int count;
    register int full_y;
    register int full_x;
    register int reference;
    register int horizontal;
    register int x_shift;
    register int y_shift;
    register int shift_count;
    int vertical;
    register int destination_base;
    register int offset_value;
    register int destination_address;
    register int reference_address;
    register int reference_width;
    register int half_x_arg;
    register int half_y_arg;

    register u16 width;

    /* ASM: addi copies both coordinates; MWCC emits mr for equivalent C. */
    asm {
        addi full_x, x, 0
        addi full_y, y, 0
    }
    y_half = y & 1;
    x_half = x & 1;
    /* ASM: addi copies the cursor and source; MWCC emits mr for C copies. */
    asm {
        addi cursor, context, 0
        addi source, decoder, 0
    }
    plane = 0;
    do {
        offset = source->offsets;
        block = 0;
        x_shift = source->x_shift;
        y_shift = source->y_shift;
        shift_count = x_shift + 1;
        /* ASM: sraw keeps the horizontal shift before the adjacent field loads;
         * MWCC schedules the equivalent C shift later. */
        asm { sraw horizontal, full_x, shift_count }
        vertical = full_y >> (y_shift + 1);
        count = source->count;
        reference = (int)cursor->reference + vertical * source->width + horizontal;

        while (block < count) {
            offset_value = *offset;
            /* ASM: mr places the horizontal flag before stride; C schedules it later. */
            asm { mr half_x_arg, x_half }
            width = source->width;
            /* ASM: mr places the vertical flag before destination; C schedules it later. */
            asm { mr half_y_arg, y_half }
            destination_base = (int)cursor->destination;
            /* ASM: add, add, addi retain retail call setup order; MWCC moves
             * equivalent C address additions later and emits mr for stride. */
            asm {
                add reference_address, reference, offset_value
                add destination_address, destination_base, offset_value
                addi reference_width, width, 0
            }
            offset++;
            fn_80104BBC((u8 *)destination_address, width,
                        (u8 *)reference_address, reference_width,
                        half_x_arg, half_y_arg);
            block++;
        }
        plane++;
        /* ASM: addi advances both pointers after comparison; MWCC hoists
         * the C source increment before it. */
        asm {
            addi cursor, cursor, 0x34
            addi source, source, 0x38
        }
    } while (plane < 3);
}
