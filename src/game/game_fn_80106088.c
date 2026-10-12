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
    s32 *offset;
    register PlaneCursor *cursor;
    register BlockInfo *base;
    register u16 width;
    s32 block;
    register u16 block_width;
    register s32 plane;
    register s32 count;
    u16 *block_id;
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
        /* ASM: lwz keeps this plane field load in retail order;
         * MWCC schedules the equivalent C expression across other loads. */
        asm { lwz base, 8(cursor) }
        block_id = source->blocks;
        /* ASM: lhz keeps this plane field load in retail order;
         * MWCC schedules the equivalent C expression across other loads. */
        asm { lhz width, 40(source) }
        offset = source->offsets;
        /* ASM: lhz keeps this plane field load in retail order;
         * MWCC schedules the equivalent C expression across other loads. */
        asm { lhz block_width, 12(source) }
        /* ASM: lbz keeps this plane field load in retail order;
         * MWCC schedules the equivalent C expression across other loads. */
        asm { lbz count, 52(source) }
        block = 0;
        while (block < count) {
            s32 id;
            s32 displacement;
            BlockInfo *current;
            u8 mode;
            register u8 dc;
            register u8 *dst;
            id = *block_id;
            block_id++;
            displacement = *offset++;
            current = base + id;
            mode = current->flags & 0xF;
            dc = current->value;
            dst = cursor->destination + displacement;
            if (mode == 0) {
                BlockInfo *above = base + (id - block_width);
                register u8 *call_dst;
                u8 left_dc;
                register u8 call_dc;
                u8 right_value;
                BlockInfo *below;
                u8 right_dc;
                s32 left_value;
                register s32 call_width;
                u8 below_dc;
                u8 above_dc;
                if (above->flags & 0x77) above_dc = dc;
                else above_dc = above->value;
                if (current[-1].flags & 0x77) left_value = dc;
                else left_value = current[-1].value;
                left_dc = left_value;
                if (current[1].flags & 0x77) right_value = dc;
                else right_value = current[1].value;
                right_dc = right_value;
                below = base + (id + block_width);
                if (below->flags & 0x77) below_dc = dc;
                else below_dc = below->value;
                /* ASM: addi preserves the retail argument-copy encodings;
                 * MWCC emits mr for equivalent C assignments. */
                asm {
                    addi call_dst, dst, 0
                    addi call_width, width, 0
                    addi call_dc, dc, 0
                }
                fn_80103510(call_dst, call_width, call_dc, above_dc, below_dc, left_dc, right_dc);
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
