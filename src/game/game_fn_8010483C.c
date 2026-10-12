typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;

typedef struct BlockInfo {
    u8 value;
    u8 flags;
} BlockInfo;

typedef struct BlockCursor {
    s32 plane;
    BlockInfo *above;
    BlockInfo *current;
    BlockInfo *below;
    BlockInfo right;
    u8 dc;
    u8 mode;
    u8 left;
} BlockCursor;

extern void fn_80103510(u8 *dst, s32 stride, u8 dc, u8 a, u8 b, u8 c, u8 d);
extern void fn_80104524(u8 *ctx, u8 *dst, s32 stride, u8 dc, u8 mode, s32 index);

/* Decode a 4x4 block and advance the adjacent-block cursors. */
void fn_8010483C(u8 *ctx, register u8 *dst, register s32 stride,
                 register BlockCursor *cursor, u16 *current)
{
    u8 mode = cursor->mode;
    if (mode == 0) {
        BlockInfo *above = cursor->above;
        register u8 dc = cursor->dc;
        register u8 a, d, above_value, right_value;
        register u8 left;
        register u8 b, below_value;
        register u8 *call_dst;
        register s32 call_stride;
        register u8 call_dc;
        register BlockInfo *below;
        register u8 right_flags;
        if (above->flags & 0x77) above_value = dc;
        else above_value = above->value;
        below = cursor->below;
        /* ASM: mr preserves the separate coefficient copy that MWCC
         * folds into the destination register for a C assignment. */
        asm { mr a, above_value }
        if (below->flags & 0x77) below_value = dc;
        else below_value = below->value;
        /* ASM: lbz and addi preserve the retail load/copy scheduling and
         * copy encoding that MWCC changes for equivalent C assignments. */
        asm {
            lbz right_flags, 17(cursor)
            addi b, below_value, 0
        }
        if (right_flags & 0x77) right_value = dc;
        else right_value = cursor->right.value;
        /* ASM: lbz, addi and mr retain the retail argument-load ordering
         * and copy encodings; MWCC moves the C load after the copies. */
        asm {
            lbz left, 20(cursor)
            addi call_dst, dst, 0
            addi call_stride, stride, 0
            mr d, right_value
            addi call_dc, dc, 0
        }
        fn_80103510(call_dst, call_stride, call_dc, a, b, left, d);
        cursor->left = dc;
    } else if (mode == 8) {
        register u8 dc = cursor->dc;
        u8 *row = dst + stride;
        dst[0] = dst[1] = dst[2] = dst[3] = dc;
        row[0] = row[1] = row[2] = row[3] = dc;
        row += stride;
        row[0] = row[1] = row[2] = row[3] = dc;
        row += stride;
        row[0] = row[1] = row[2] = row[3] = dc;
        cursor->left = dc;
    } else {
        fn_80104524(ctx, dst, stride, cursor->dc, mode, cursor->plane);
        cursor->left = cursor->right.value;
    }
    cursor->above++;
    cursor->below++;
}
