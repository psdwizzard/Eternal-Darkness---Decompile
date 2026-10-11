/* Accumulate weighted 4-by-4 image blocks and return their mean. */

typedef unsigned char u8;
typedef signed int s32;

extern s32 fn_801036AC(void *ctx, u8 *block, s32 *state,
                      u8 *table, s32 stride, s32 index);

s32 fn_80104044(void *ctx, s32 *out, u8 count,
                u8 *table, s32 stride, s32 index)
{
    s32 state = 0;
    u8 block[16];
    s32 weight;

    out[15] = 0;
    out[14] = 0;
    out[13] = 0;
    out[12] = 0;
    out[11] = 0;
    out[10] = 0;
    out[9] = 0;
    out[8] = 0;
    out[7] = 0;
    out[6] = 0;
    out[5] = 0;
    out[4] = 0;
    out[3] = 0;
    out[2] = 0;
    out[1] = 0;
    out[0] = 0;

    while (count--) {
        weight = fn_801036AC(ctx, block, &state, table, stride, index);
        out[0] += weight * block[0];
        out[1] += weight * block[1];
        out[2] += weight * block[2];
        out[3] += weight * block[3];
        out[4] += weight * block[4];
        out[5] += weight * block[5];
        out[6] += weight * block[6];
        out[7] += weight * block[7];
        out[8] += weight * block[8];
        out[9] += weight * block[9];
        out[10] += weight * block[10];
        out[11] += weight * block[11];
        out[12] += weight * block[12];
        out[13] += weight * block[13];
        out[14] += weight * block[14];
        out[15] += weight * block[15];
    }
    return (out[0] + out[1] + out[2] + out[3] +
            out[4] + out[5] + out[6] + out[7] +
            out[8] + out[9] + out[10] + out[11] +
            out[12] + out[13] + out[14] + out[15]) >> 4;
}
