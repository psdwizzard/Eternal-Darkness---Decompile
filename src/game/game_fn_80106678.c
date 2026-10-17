typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;

typedef struct DecodeTree DecodeTree;

typedef struct BitReader {
    const u8* input;
    u8 pad04[8];
    volatile u8 current;
    volatile u8 mask;
    u8 pad0E[2];
    DecodeTree* tree;
} BitReader;

typedef struct SrcPlane {
    u8* blocks;
    u8 pad04[0x24];
    int size;
    u8 pad2C[0xC];
} SrcPlane;

typedef struct Decoder {
    u8 pad00[4];
    SrcPlane planes[3];
    u8 pad_ac[0x320C - 0xAC];
    BitReader mv_x;
    BitReader mv_y;
    u8 pad3234[0x3CCC - 0x3234];
    u8 range_x[2];
    u8 range_y[2];
} Decoder;

typedef struct Movie {
    Decoder* decoder;
    u16 width;
    u16 height;
} Movie;

typedef struct PlaneCursor {
    volatile int run;
    volatile int dc;
    u8* volatile blocks;
    u8* volatile block_row;
    volatile int row;
    volatile int pos;
    volatile int ref;
    volatile int refs[2];
    volatile u16 block_step;
    volatile int row_step;
    volatile int blocks_step;
    volatile int block_row_step;
} PlaneCursor;

typedef struct FrameContext {
    PlaneCursor planes[3];
} FrameContext;

s16 fn_80102C6C(BitReader* reader);
void fn_80104B30(Decoder* decoder, FrameContext* ctx, int dest, int arg2, int arg3);
void fn_801061E0(Movie* movie, FrameContext* ctx);
void fn_80106088(Decoder* decoder, FrameContext* ctx);
void fn_80105DE0(Decoder* decoder, FrameContext* ctx, int x, int y);
void fn_8010528C(Decoder* decoder, FrameContext* ctx, int x, int y);

static inline void DecodeIntra(Decoder* decoder, FrameContext* ctx)
{
    register Decoder* input = decoder;
    register Decoder* call_decoder;
    /* ASM: addi preserves the retail argument copy, where C emits mr. */
    asm { addi call_decoder, input, 0 }
    fn_80106088(call_decoder, ctx);
}

static inline void SetupFrame(Decoder* source, FrameContext* ctx, int dest, int arg2, int arg3)
{
    register Decoder* input = source;
    register Decoder* call_source;
    /* ASM: addi preserves the retail argument copy, where C emits mr. */
    asm { addi call_source, input, 0 }
    fn_80104B30(call_source, ctx, dest, arg2, arg3);
}

static inline void DecodeModes(Movie* source, FrameContext* ctx)
{
    register Movie* input = source;
    register Movie* call_source;
    /* ASM: addi preserves the retail argument copy, where C emits mr. */
    asm { addi call_source, input, 0 }
    fn_801061E0(call_source, ctx);
}

static inline void CopyMotion(Decoder* source, FrameContext* ctx, int x, int y)
{
    register Decoder* input = source;
    register Decoder* call_source;
    /* ASM: addi preserves the retail argument copy, where C emits mr. */
    asm { addi call_source, input, 0 }
    fn_80105DE0(call_source, ctx, x, y);
}

static inline void BlendMotion(Decoder* source, FrameContext* ctx, int x, int y)
{
    register Decoder* input = source;
    register Decoder* call_source;
    /* ASM: addi preserves the retail argument copy, where C emits mr. */
    asm { addi call_source, input, 0 }
    fn_8010528C(call_source, ctx, x, y);
}

void fn_80106678(register Movie* movie, int dest, int arg2, int arg3)
{
    FrameContext ctx;
    int plane_offset;
    register int destination = dest;
    register int range_x;
    register int bits_x;
    register int x2;
    register int y2;
    register int flags;
    register Decoder* reference_decoder;
    register Decoder* decoder;
    register int mv_x;
    register int mv_y;
    register int ref;
    register int x;
    register int y;

    decoder = movie->decoder;
    x = destination;
    SetupFrame(decoder, &ctx, x, arg2, arg3);
    DecodeModes(movie, &ctx);

    ctx.planes[0].row = x;
    y = 0;
    ref = -1;
    ctx.planes[0].block_row = ctx.planes[0].blocks = decoder->planes[0].blocks;
    plane_offset = x + decoder->planes[0].size;
    ctx.planes[1].row = plane_offset;
    ctx.planes[1].block_row = ctx.planes[1].blocks = decoder->planes[1].blocks;
    ctx.planes[2].row = plane_offset + decoder->planes[1].size;
    ctx.planes[2].block_row = ctx.planes[2].blocks = decoder->planes[2].blocks;

    for (y2 = y * 2; y < movie->height; y2 += 16, y += 8) {
        ctx.planes[0].pos = ctx.planes[0].row;
        ctx.planes[1].pos = ctx.planes[1].row;
        ctx.planes[2].pos = ctx.planes[2].row;

        for (x = 0, x2 = x * 2; x < movie->width; x2 += 16, x += 8) {
            int type;
            flags = ctx.planes[0].blocks[1];
            type = (flags >> 5) & 3;

            if (type == 0) {
                DecodeIntra(decoder, &ctx);
            } else {
                register int bits_y;
                register int range_y;

                if (type - 1 != ref) {
                    ref = type - 1;
                    if (ref == 0) {
                        ctx.planes[0].ref = ctx.planes[0].refs[0];
                        ctx.planes[1].ref = ctx.planes[1].refs[0];
                        ctx.planes[2].ref = ctx.planes[2].refs[0];
                    } else {
                        ctx.planes[0].ref = ctx.planes[0].refs[1];
                        ctx.planes[1].ref = ctx.planes[1].refs[1];
                        ctx.planes[2].ref = ctx.planes[2].refs[1];
                    }
                    mv_y = 0;
                    mv_x = 0;
                }

                reference_decoder = (Decoder*)((u8*)decoder + ref);
                bits_x = reference_decoder->range_x[0];
                range_x = 1 << (bits_x + 5);
                {
                    register u8 initial_mask;
                    const u8* input;
                    int i;
                    int delta;
                    s16 symbol = fn_80102C6C(&decoder->mv_x);
                    i = bits_x - 1;
                    delta = symbol << bits_x;
                    for (; i >= 0; i--) {
                        u8 bit;
                        register int set;
                        u8 mask;
                        if (decoder->mv_x.mask == 0) {
                            input = decoder->mv_x.input;
                            /* ASM: li keeps refill initialization inside the
                             * refill branch; C hoists this constant into the loop. */
                            asm { li initial_mask, 128 }
                            decoder->mv_x.input = input + 1;
                            decoder->mv_x.current = *input;
                            decoder->mv_x.mask = initial_mask;
                        }
                        bit = decoder->mv_x.current;
                        /* ASM: li preserves the variable shift count shared with
                         * the decoded bit; C folds this to an immediate shift. */
                        asm { li set, 1 }
                        mask = decoder->mv_x.mask;
                        bit &= mask;
                        decoder->mv_x.mask = mask >> set;
                        if ((u8)bit == 0) {
                            set = 0;
                        }
                        delta += set << i;
                    }
                    mv_x += delta;
                }
                if (mv_x >= range_x) {
                    mv_x -= range_x * 2;
                } else if (mv_x < -range_x) {
                    mv_x += range_x * 2;
                }

                /* ASM: lbz reuses the reference address register for its bit
                 * count; C splits these two nonoverlapping lifetimes. */
                asm { lbz reference_decoder, 15566(reference_decoder) }
                bits_y = (int)reference_decoder;
                bits_x = 1 << (bits_y + 5);
                range_y = bits_x;
                {
                    register u8 initial_mask;
                    const u8* input;
                    int i;
                    int delta;
                    s16 symbol = fn_80102C6C(&decoder->mv_y);
                    i = bits_y - 1;
                    delta = symbol << bits_y;
                    for (; i >= 0; i--) {
                        u8 bit;
                        register int set;
                        u8 mask;
                        if (decoder->mv_y.mask == 0) {
                            input = decoder->mv_y.input;
                            /* ASM: li keeps refill initialization inside the
                             * refill branch; C hoists this constant into the loop. */
                            asm { li initial_mask, 128 }
                            decoder->mv_y.input = input + 1;
                            decoder->mv_y.current = *input;
                            decoder->mv_y.mask = initial_mask;
                        }
                        bit = decoder->mv_y.current;
                        /* ASM: li preserves the variable shift count shared with
                         * the decoded bit; C folds this to an immediate shift. */
                        asm { li set, 1 }
                        mask = decoder->mv_y.mask;
                        bit &= mask;
                        decoder->mv_y.mask = mask >> set;
                        if ((u8)bit == 0) {
                            set = 0;
                        }
                        delta += set << i;
                    }
                    mv_y += delta;
                }
                if (mv_y >= range_y) {
                    mv_y -= range_y * 2;
                } else if (mv_y < -range_y) {
                    mv_y += range_y * 2;
                }

                if (!((flags >> 4) & 1)) {
                    CopyMotion(decoder, &ctx, x2 + mv_x, y2 + mv_y);
                } else {
                    BlendMotion(decoder, &ctx, x2 + mv_x, y2 + mv_y);
                }
            }

            ctx.planes[0].pos += ctx.planes[0].block_step;
            ctx.planes[0].blocks = ctx.planes[0].blocks_step * 2 + ctx.planes[0].blocks;
            ctx.planes[1].pos += ctx.planes[1].block_step;
            ctx.planes[1].blocks = ctx.planes[1].blocks_step * 2 + ctx.planes[1].blocks;
            ctx.planes[2].pos += ctx.planes[2].block_step;
            ctx.planes[2].blocks = ctx.planes[2].blocks_step * 2 + ctx.planes[2].blocks;
        }

        ctx.planes[0].row += ctx.planes[0].row_step;
        ctx.planes[0].blocks = ctx.planes[0].block_row = ctx.planes[0].block_row_step * 2 + ctx.planes[0].block_row;
        ctx.planes[1].row += ctx.planes[1].row_step;
        ctx.planes[1].blocks = ctx.planes[1].block_row = ctx.planes[1].block_row_step * 2 + ctx.planes[1].block_row;
        ctx.planes[2].row += ctx.planes[2].row_step;
        ctx.planes[2].blocks = ctx.planes[2].block_row = ctx.planes[2].block_row_step * 2 + ctx.planes[2].block_row;
    }
}
