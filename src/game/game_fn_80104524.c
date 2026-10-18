typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;

typedef struct Stream {
    u8 *cur;
    u8 pad[12];
} Stream;

extern s32 GetAotSum(void *ctx, s32 *out, u8 mode,
                      u8 *table, s32 stride, s32 index);
extern u8 clipTable[];

/* Decode a 4-by-4 block from a raw stream or weighted coefficients. */
void IntraAotBlock(register u8 *ctx, u8 *dst, s32 stride, u8 dc,
                 register u8 mode, s32 index)
{
    /* Preserve the coefficient buffer's original stack offset. */
    struct {
        u8 padding[0x14];
        s32 coef[16];
    } work;
    u8 *clamp = clipTable;
    u8 shift;
    s32 bias;
    register u8 callMode;

    if (mode == 6) {
        register Stream *s;
        register s32 offset = index * 16;
        u8 *row;
        register u8 *cur;
        /* ASM: addi and add keep the cursor field address in a register;
         * C folds its constant offset into every cursor load and store. */
        asm {
            addi s, offset, 0x31DC
            add s, ctx, s
        }
        /* ASM: lwz keeps the first cursor load before row calculation;
         * the compiler schedules the C load after that calculation. */
        asm { lwz cur, 0(s) }
        row = dst + stride;
        /* ASM: mr keeps the context live through row setup, preserving the
         * retail scratch-register lifetime; C drops it at cursor setup. */
        asm { mr ctx, ctx }
        s->cur = cur + 1;
        dst[0] = *cur;
        dst[1] = *s->cur++;
        dst[2] = *s->cur++;
        dst[3] = *s->cur++;
        row[0] = *s->cur++;
        row[1] = *s->cur++;
        row[2] = *s->cur++;
        row[3] = *s->cur++;
        row += stride;
        row[0] = *s->cur++;
        row[1] = *s->cur++;
        row[2] = *s->cur++;
        row[3] = *s->cur++;
        row += stride;
        row[0] = *s->cur++;
        row[1] = *s->cur++;
        row[2] = *s->cur++;
        row[3] = *s->cur++;
        return;
    }

    shift = ctx[0x3CCA];
    /* ASM: addi retains the retail argument-copy encoding; C uses mr. */
    asm { addi callMode, mode, 0 }
    bias = ((dc + 0x80) << shift) -
        GetAotSum(ctx, work.coef, callMode, ctx + 0x3261,
                    *(u16 *)(ctx + 0x325C), index);
    dst[0] = clamp[(work.coef[0] + bias) >> shift];
    dst[1] = clamp[(work.coef[1] + bias) >> shift];
    dst[2] = clamp[(work.coef[2] + bias) >> shift];
    dst[3] = clamp[(work.coef[3] + bias) >> shift];
    dst += stride;
    dst[0] = clamp[(work.coef[4] + bias) >> shift];
    dst[1] = clamp[(work.coef[5] + bias) >> shift];
    dst[2] = clamp[(work.coef[6] + bias) >> shift];
    dst[3] = clamp[(work.coef[7] + bias) >> shift];
    dst += stride;
    dst[0] = clamp[(work.coef[8] + bias) >> shift];
    dst[1] = clamp[(work.coef[9] + bias) >> shift];
    dst[2] = clamp[(work.coef[10] + bias) >> shift];
    dst[3] = clamp[(work.coef[11] + bias) >> shift];
    dst += stride;
    dst[0] = clamp[(work.coef[12] + bias) >> shift];
    dst[1] = clamp[(work.coef[13] + bias) >> shift];
    dst[2] = clamp[(work.coef[14] + bias) >> shift];
    dst[3] = clamp[(work.coef[15] + bias) >> shift];
}
