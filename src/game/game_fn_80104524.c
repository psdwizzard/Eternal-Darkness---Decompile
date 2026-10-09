typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;

typedef struct Stream {
    u8 *cur;
    u8 pad[12];
} Stream;

extern s32 fn_80104044(void *ctx, s32 *out, u8 mode, u8 *table, u16 count);
extern u8 lbl_8032CC08[];

void fn_80104524(u8 *ctx, u8 *dst, s32 stride, u8 dc, u8 mode, s32 index) {
    s32 coef[16];
    u8 *clamp = lbl_8032CC08;
    u8 shift;
    s32 bias;

    if (mode == 6) {
        Stream *s = (Stream *)(ctx + 0x31DC) + index;
        u8 *row = dst + stride;

        dst[0] = *s->cur++;
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
    bias = ((dc + 0x80) << shift) - fn_80104044(ctx, coef, mode, ctx + 0x3261, *(u16 *)(ctx + 0x325C));
    dst[0] = clamp[(coef[0] + bias) >> shift];
    dst[1] = clamp[(coef[1] + bias) >> shift];
    dst[2] = clamp[(coef[2] + bias) >> shift];
    dst[3] = clamp[(coef[3] + bias) >> shift];
    dst += stride;
    dst[0] = clamp[(coef[4] + bias) >> shift];
    dst[1] = clamp[(coef[5] + bias) >> shift];
    dst[2] = clamp[(coef[6] + bias) >> shift];
    dst[3] = clamp[(coef[7] + bias) >> shift];
    dst += stride;
    dst[0] = clamp[(coef[8] + bias) >> shift];
    dst[1] = clamp[(coef[9] + bias) >> shift];
    dst[2] = clamp[(coef[10] + bias) >> shift];
    dst[3] = clamp[(coef[11] + bias) >> shift];
    dst += stride;
    dst[0] = clamp[(coef[12] + bias) >> shift];
    dst[1] = clamp[(coef[13] + bias) >> shift];
    dst[2] = clamp[(coef[14] + bias) >> shift];
    dst[3] = clamp[(coef[15] + bias) >> shift];
}
