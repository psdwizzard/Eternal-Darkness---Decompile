typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;

typedef struct MotionPlane {
    u8 pad00[0xC];
    u16 block_width;
    u8 pad0E[2];
    u16 blocks[4];
    s32 offsets[4];
    u16 width;
    u8 pad2A[0xA];
    u8 count;
    u8 pad35[3];
} MotionPlane;

typedef struct Decoder {
    MotionPlane planes[3];
} Decoder;

typedef struct BlockInfo {
    u8 value;
    u8 flags;
} BlockInfo;

typedef struct PlaneCursor {
    u8 pad00[8];
    BlockInfo *block_info;
    u8 pad0C[8];
    u8 *destination;
    u8 pad18[0x1C];
} PlaneCursor;

typedef struct FrameContext {
    PlaneCursor planes[3];
} FrameContext;

extern void fn_80103510(u8 *dst, s32 stride, u8 dc, u8 a, u8 b, u8 c, u8 d);
extern void fn_80104524(u8 *ctx, u8 *dst, s32 stride, u8 dc, u8 mode, s32 index);

/* Decode each plane's intra blocks, using adjacent DC values for mode zero. */
void fn_80106088(register Decoder *input_decoder, register FrameContext *context)
{
    register MotionPlane *source;
    register s32 *offset;
    register PlaneCursor *cursor;
    register BlockInfo *base;
    register u16 width;
    register s32 block;
    register u16 block_width;
    register s32 plane;
    register s32 count;
    register u16 *block_id;
    register Decoder *decoder;
    /* ASM: addi preserves zero-offset register copies; MWCC emits mr for
     * the equivalent C assignments. */
    asm {
        addi decoder, input_decoder, 0
        addi cursor, context, 0
        addi source, decoder, 0
    }
    plane = 0;
    do {
        base = cursor->block_info;
        block_id = source->blocks;
        width = source->width;
        offset = source->offsets;
        block_width = source->block_width;
        count = source->count;
        block = 0;
        while (block < count) {
            register s32 id;
            s32 displacement;
            BlockInfo *current;
            u8 mode;
            register u8 dc;
            register u8 *dst;
            /* ASM: lhz avoids the redundant 16-bit mask MWCC emits for
             * an equivalent C block-index load and address calculation. */
            asm {
                lhz id, 0(block_id)
            }
            block_id++;
            displacement = *offset++;
            current = (BlockInfo *)((u8 *)base + id * 2);
            mode = current->flags & 0xF;
            dc = current->value;
            dst = cursor->destination + displacement;
            if (mode == 0) {
                BlockInfo *above = base + (id - block_width);
                register u8 *call_dst;
                register u8 left;
                register u8 call_dc;
                register u8 d;
                BlockInfo *below;
                register u8 right;
                register u8 c;
                register s32 call_width;
                register u8 b;
                register u8 a;
                if (above->flags & 0x77) a = dc;
                else a = above->value;
                if (current[-1].flags & 0x77) c = dc;
                else c = current[-1].value;
                /* ASM: addi retains the retail coefficient copy; MWCC
                 * merges the C assignment into the call argument register. */
                asm { addi left, c, 0 }
                if (current[1].flags & 0x77) d = dc;
                else d = current[1].value;
                /* ASM: addi retains the right coefficient copy, which the
                 * compiler eliminates for an equivalent C assignment. */
                asm { addi right, d, 0 }
                below = base + (id + block_width);
                if (below->flags & 0x77) b = dc;
                else b = below->value;
                /* ASM: addi preserves the retail argument-copy encodings;
                 * MWCC emits mr for equivalent C assignments. */
                asm {
                    addi call_dst, dst, 0
                    addi call_width, width, 0
                    addi call_dc, dc, 0
                }
                fn_80103510(call_dst, call_width, call_dc, a, b, left, right);
            } else {
                register u8 *call_ctx;
                register s32 call_width;
                register u8 call_dc;
                register s32 call_plane;
                /* ASM: addi preserves the retail argument-copy encodings;
                 * MWCC emits mr for equivalent C assignments. */
                asm {
                    addi call_ctx, decoder, 0
                    addi call_width, width, 0
                    addi call_dc, dc, 0
                    addi call_plane, plane, 0
                }
                fn_80104524(call_ctx, dst, call_width, call_dc, mode, call_plane);
            }
            block++;
        }
        plane++;
        /* ASM: addi retains the retail increment scheduling; MWCC reorders
         * this update when expressed as C. */
        asm { addi cursor, cursor, 52 }
        source++;
    } while (plane < 3);
}
