#include "src/game/types.h"

/* Pick the first level that accepts the sample peak, the sum of rounded
 * magnitudes, and the partition position. */

extern double rint(double x); /* rint */

typedef struct LevelTable {
    char pad0[0x514];
    float sum_limit[64];
    float peak_limit[64];
    char pad714[0x100];
    s32 thresh[64];
} LevelTable;

extern float lbl_80651860;

int _testhack(float *in, s32 n, LevelTable **tablep, s32 count, s32 value)
{
    float buf[128];
    float *b;
    LevelTable *table;
    double peak;
    float sum;
    s32 i;
    float *p;

    peak = lbl_80651860;
    b = buf;
    table = *tablep;
    sum = peak;
    /* Convert eight magnitudes at a time, retaining the preceding result
     * while computing the next one. */
    if (n > 0) {
        s32 blocks = (u32)n >> 3;
        s32 left = n;
        float *dest = b;
        if (blocks) {
            do {
                float sample = in[0];
                double magnitude = __fabs(sample);
                double previous;
                previous = magnitude;
                sample = in[1];
                magnitude = __fabs(sample);
                dest[0] = previous;
                previous = magnitude;
                sample = in[2];
                magnitude = __fabs(sample);
                dest[1] = previous;
                previous = magnitude;
                sample = in[3];
                magnitude = __fabs(sample);
                dest[2] = previous;
                previous = magnitude;
                sample = in[4];
                magnitude = __fabs(sample);
                dest[3] = previous;
                previous = magnitude;
                sample = in[5];
                magnitude = __fabs(sample);
                dest[4] = previous;
                previous = magnitude;
                sample = in[6];
                magnitude = __fabs(sample);
                dest[5] = previous;
                previous = magnitude;
                sample = in[7];
                magnitude = __fabs(sample);
                dest[6] = previous;
                dest[7] = magnitude;
                in += 8;
                dest += 8;
            } while (--blocks > 0);
            left &= 7;
        }
        if (left) {
            do {
                *dest++ = __fabs(*in++);
            } while (--left > 0);
        }
    }
    p = b;
    for (i = 0; i < n; i++, p++) {
        if (*p > peak) {
            peak = *p;
        }
    }
    for (i = 0; i < n; i++) {
        b[i] = rint(b[i]);
    }
    for (i = 0; i < n; i++) {
        sum += b[i];
    }
    for (i = 0; i < count - 1; i++) {
        if (value < table->thresh[i] && sum <= table->sum_limit[i] &&
            peak <= table->peak_limit[i]) {
            break;
        }
    }
    return i;
}
