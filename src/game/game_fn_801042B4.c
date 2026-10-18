#include "src/game/types.h"

s32 GetMCAotBasis(s32 arg0, u8* weights, s32* state, s32 arg3, s32 arg4, s32 arg5);

s32 GetMCAotSum(s32 arg0, s32* sums, u8 count, s32 arg3, s32 arg4, s32 arg5) {
    s32 state;
    u8 weights[16];
    s32 value;
    s32 total;

    state = 0;
    sums[15] = 0;
    sums[14] = 0;
    sums[13] = 0;
    sums[12] = 0;
    sums[11] = 0;
    sums[10] = 0;
    sums[9] = 0;
    sums[8] = 0;
    sums[7] = 0;
    sums[6] = 0;
    sums[5] = 0;
    sums[4] = 0;
    sums[3] = 0;
    sums[2] = 0;
    sums[1] = 0;
    sums[0] = 0;

    while (count--) {
        value = GetMCAotBasis(arg0, weights, &state, arg3, arg4, arg5);
        sums[0] += value * weights[0];
        sums[1] += value * weights[1];
        sums[2] += value * weights[2];
        sums[3] += value * weights[3];
        sums[4] += value * weights[4];
        sums[5] += value * weights[5];
        sums[6] += value * weights[6];
        sums[7] += value * weights[7];
        sums[8] += value * weights[8];
        sums[9] += value * weights[9];
        sums[10] += value * weights[10];
        sums[11] += value * weights[11];
        sums[12] += value * weights[12];
        sums[13] += value * weights[13];
        sums[14] += value * weights[14];
        sums[15] += value * weights[15];
    }

    total = sums[0] + sums[1] + sums[2] + sums[3] + sums[4] + sums[5] + sums[6] + sums[7] +
            sums[8] + sums[9] + sums[10] + sums[11] + sums[12] + sums[13] + sums[14] + sums[15];
    return total >> 4;
}
