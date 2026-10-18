#include "src/game/types.h"

typedef struct DecodeTree DecodeTree;
typedef struct BitReader {
    const u8 *input;
    u8 pad04[8];
    u8 current;
    u8 mask;
    u8 pad0E[2];
    DecodeTree *tree;
} BitReader;

typedef struct ModePlane {
    u8 pad00[0x10];
    u16 indices[4];
    u8 pad18[0x1C];
    u8 count;
    u8 pad35[3];
} ModePlane;

typedef struct Decoder {
    ModePlane planes[3];
    u8 padA8[0x30D8 - 0xA8];
    BitReader dc[3];
    u8 pad3114[0x3234 - 0x3114];
    BitReader modes;
    BitReader types;
    u8 pad325C[0x3CC6 - 0x325C];
    s16 upper;
    s16 lower;
} Decoder;

typedef struct PlaneCursor {
    s32 run;
    s32 dc;
    u8 *modes;
    u8 *mode_row;
    u8 *row;
    u8 *destination;
    u8 pad18[0xC];
    u16 block_step;
    u8 pad26[2];
    s32 row_step;
    s32 modes_step;
    s32 mode_row_step;
} PlaneCursor;

typedef struct FrameContext {
    PlaneCursor planes[3];
} FrameContext;

typedef struct Movie {
    Decoder *decoder;
    u16 width;
    u16 height;
} Movie;

extern s16 decodeHuff(BitReader *reader);
extern void decode_PB_cc(Decoder *decoder, FrameContext *context, s32 mode, s32 flags);
extern s32 lbl_8023A208[2][3];

static inline s32 read_bit(register BitReader *reader)
{
    register s32 bit;
    register s32 set;
    register u8 mask;
    if (reader->mask == 0) {
        reader->current = *reader->input++;
        reader->mask = 0x80;
    }
    bit = reader->current;
    /* ASM: li keeps the shift count in a register; C folds it to an
     * immediate shift instead of the retail variable shift. */
    asm { li set, 1 }
    mask = reader->mask;
    bit &= mask;
    reader->mask = mask >> set;
    if ((u8)bit != 0) {
        /* ASM: b preserves the retail two-branch boolean decision;
         * C otherwise inverts the conditional and removes the jump. */
        asm { b bit_set }
    } else {
        set = 0;
    }
bit_set:
    return set;
}

/* Decode run-length block types and modes, and each intra block's DC value. */
void spread_PB_descMap(Movie *volatile movie, register FrameContext *input_context)
{
    register PlaneCursor *cursor;
    register s32 total;
    register s32 i;
    register u16 *indices;
    register Decoder *decoder;
    register s16 upper;
    register s16 lower;
    register u16 index;
    register BitReader *reader;
    register s32 count;
    register ModePlane *plane;
    register u8 *reader_base;
    register s32 p;
    register s32 type_run;
    register s32 mode_run;
    register FrameContext *context;
    register PlaneCursor *v;
    register PlaneCursor *u;
    register s16 value;
    s32 (*volatile transitions)[3];
    volatile s32 mode;
    volatile s32 type;
    s32 x;
    s32 y;
    register const u8 *input;

    /* ASM: mr keeps the incoming cursor copy explicit; C coalesces the
     * argument and local cursor, changing their register allocation. */
    asm { mr context, input_context }
    decoder = movie->decoder;
    input = decoder->modes.input;
    if (input != 0) {
        s32 bit;
        if (decoder->modes.mask == 0) {
            decoder->modes.input = input + 1;
            decoder->modes.current = *input;
            decoder->modes.mask = 0x80;
        }
        mode = 1;
        bit = decoder->modes.current & decoder->modes.mask;
        decoder->modes.mask >>= mode;
        if ((u8)bit == 0) {
            mode = 0;
        }
        mode_run = 0;
        do {
            value = decodeHuff(&decoder->modes);
            mode_run += value;
        } while (value >= 255);
    }
    if (decoder->types.input != 0) {
        register s32 high;
        register s32 shift;
        register u8 bit;
        register u8 mask;
        if (decoder->types.mask == 0) {
            decoder->types.current = *decoder->types.input++;
            decoder->types.mask = 0x80;
        }
        bit = decoder->types.current;
        /* ASM: li retains a register shift count; C folds the constant
         * into an immediate shift instead of the retail sraw. */
        asm { li shift, 1 }
        mask = decoder->types.mask;
        bit &= mask;
        decoder->types.mask = mask >> shift;
        if (bit != 0) {
            /* ASM: li keeps the two-bit type decision as branches;
             * C replaces this decision with branchless arithmetic. */
            asm { li high, 2 }
        } else {
            high = 0;
        }
        type = high | read_bit(&decoder->types);
        type_run = 0;
        do {
            value = decodeHuff(&decoder->types);
            type_run += value;
        } while (value >= 255);
    }

    transitions = lbl_8023A208;
    /* ASM: addi keeps the chroma cursors in separate registers. C folds
     * these addresses into offsets from the luma cursor. */
    asm { addi u, context, 0x34 }
    y = 0;
    /* ASM: addi keeps the V cursor separate; C folds its address into
     * offsets from the luma cursor. */
    asm { addi v, context, 0x68 }
    for (; y < movie->height; y += 8) {
        context->planes[0].destination = context->planes[0].row;
        u->destination = u->row;
        v->destination = v->row;
        for (x = 0; x < movie->width; x += 8) {
            if (type_run == 0) {
                register s32 choice = read_bit(&decoder->types);
                register s32 row_offset;
                register s32 (*table)[3];
                register s32 *entry;
                register s32 column;
                row_offset = choice * sizeof(*table);
                table = transitions;
                /* ASM: add preserves the row address before the column load;
                 * C reassociates the two offsets. */
                asm { add entry, table, row_offset }
                column = type;
                type_run = 0;
                column *= sizeof(s32);
                /* ASM: add preserves a separate column addition and load;
                 * C combines them into lwzx. */
                asm { add entry, entry, column }
                type = *entry;
                do {
                    value = decodeHuff(&decoder->types);
                    type_run += value;
                } while (value >= 255);
            }
            type_run--;
            if (type == 0) {
                cursor = context->planes;
                plane = decoder->planes;
                reader_base = (u8 *)decoder;
                p = 0;
                do {
                    count = plane->count;
                    reader = (BitReader *)(reader_base + 0x30D8);
                    indices = plane->indices;
                    for (i = 0; i < count; i++) {
                        index = *indices++;
                        total = 0;
                        upper = decoder->upper;
                        lower = decoder->lower;
                        /* Symbols at either endpoint extend the DC delta. */
                        do {
                            value = decodeHuff(reader);
                            total += value;
                        } while (lower >= value || value >= upper);
                        cursor->modes[index * 2] = cursor->dc += total;
                    }
                    p++;
                    /* ASM: addi keeps cursor advancement before the other
                     * plane increments; C schedules this after them. */
                    asm { addi cursor, cursor, 0x34 }
                    plane++;
                    reader_base += sizeof(BitReader);
                } while (p < 3);
                {
                    register Decoder *call_decoder;
                    register FrameContext *call_context;
                    register s32 call_type = type;
                    /* ASM: addi preserves the retail argument-copy encoding;
                     * C assignments and argument passing emit mr. */
                    asm {
                        addi call_decoder, decoder, 0
                        addi call_context, context, 0
                    }
                    decode_PB_cc(call_decoder, call_context, 0, call_type);
                }
            } else {
                context->planes[0].dc = 127;
                context->planes[1].dc = 127;
                context->planes[2].dc = 127;
                if (mode_run == 0) {
                    mode ^= 1;
                    mode_run = 0;
                    do {
                        value = decodeHuff(&decoder->modes);
                        mode_run += value;
                    } while (value >= 255);
                }
                mode_run--;
                {
                    register Decoder *call_decoder;
                    register FrameContext *call_context;
                    register s32 call_mode = mode;
                    register s32 call_type;
                    /* ASM: addi preserves the retail decoder argument copy;
                     * C assignments emit mr. */
                    asm { addi call_decoder, decoder, 0 }
                    call_type = type;
                    /* ASM: addi preserves the retail context argument copy;
                     * C assignments emit mr. */
                    asm { addi call_context, context, 0 }
                    decode_PB_cc(call_decoder, call_context, call_mode, call_type);
                }
            }
            context->planes[0].destination += context->planes[0].block_step;
            context->planes[0].modes += context->planes[0].modes_step * 2;
            u->destination += u->block_step;
            u->modes += u->modes_step * 2;
            v->destination += v->block_step;
            v->modes += v->modes_step * 2;
        }
        context->planes[0].row += context->planes[0].row_step;
        context->planes[0].modes = context->planes[0].mode_row += context->planes[0].mode_row_step * 2;
        u->row += u->row_step;
        u->modes = u->mode_row += u->mode_row_step * 2;
        v->row += v->row_step;
        v->modes = v->mode_row += v->mode_row_step * 2;
    }
}
