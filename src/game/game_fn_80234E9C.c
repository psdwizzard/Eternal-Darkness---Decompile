#include "src/game/types.h"

/* fn_80234E9C: pick the first table level whose sum/peak limits fit the
 * rounded absolute values of the input samples. */

extern double fn_80102074(double x); /* rint */

typedef struct LevelTable {
    char pad0[0x514];
    float sum_limit[64];
    float peak_limit[64];
    char pad714[0x100];
    s32 thresh[64];
} LevelTable;

extern float lbl_80651860;

int fn_80234E9C(float *in, s32 n, LevelTable **tablep, s32 count, s32 value)
{
    float buf[128];
    float *b;
    LevelTable *table;
    float peak;
    float sum;
    s32 i;
    float *p;

    peak = lbl_80651860;
    b = buf;
    table = *tablep;
    sum = peak;
    for (i = 0; i < n; i++) {
        b[i] = __fabs(in[i]);
    }
    for (i = 0; i < n; i++) {
        if (b[i] > peak) {
            peak = b[i];
        }
    }
    p = b;
    for (i = 0; i < n; i++) {
        *p = fn_80102074(*p);
        p++;
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
