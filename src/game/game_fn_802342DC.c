#include "src/game/types.h"

typedef struct MdctLookup {
    s32 n;
    s32 log2n;
    float *trig;
    s32 *bitrev;
    float scale;
} MdctLookup;

extern void *fn_8022F780(s32 size);
extern double fn_80101988(double x); /* cos */
extern double fn_801021D0(double x); /* sin */
extern double fn_80102380(double x); /* log */
extern double fn_80102074(double x); /* rint */
extern double lbl_80651848;
extern float lbl_80651850;
extern float lbl_80651854;

/* Prepare the trigonometric and bit-reversal tables for an MDCT. */
void fn_802342DC(MdctLookup *lookup, s32 n)
{
    s32 log2n;
    s32 n4 = n / 4;
    s32 *bitrev = fn_8022F780(n4 * sizeof(*bitrev));
    float *trig = fn_8022F780((n + n4) * sizeof(*trig));
    float pi;
    s32 i;
    s32 n2 = n >> 1;
    float log2 = (float)fn_80102380(lbl_80651848);
    log2n = (s32)fn_80102074((float)fn_80102380((float)n) / log2);
    pi = lbl_80651850;
    lookup->log2n = log2n;
    lookup->n = n;
    lookup->trig = trig;
    lookup->bitrev = bitrev;

    for (i = 0; i < n4; i++) {
        float angle = (pi / (float)n) * (float)(4 * i);
        trig[i * 2] = (float)fn_80101988(angle);
        trig[i * 2 + 1] = -(float)fn_801021D0(angle);
        angle = (pi / (float)(2 * n)) * (float)(2 * i + 1);
        trig[n2 + i * 2] = (float)fn_80101988(angle);
        trig[n2 + i * 2 + 1] = (float)fn_801021D0(angle);
    }
    pi = lbl_80651850;
    for (i = 0; i < n / 8; i++) {
        float angle = (pi / (float)n) * (float)(4 * i + 2);
        trig[n + i * 2] = 0.5f * (float)fn_80101988(angle);
        trig[n + i * 2 + 1] = 0.5f * -(float)fn_801021D0(angle);
    }
    {
        s32 mask = (1 << (log2n - 1)) - 1;
        s32 msb = 1 << (log2n - 2);
        for (i = 0; i < n / 8; i++) {
            s32 acc = 0;
            s32 j;
            for (j = 0; msb >> j; j++) {
                if ((msb >> j) & i)
                    acc |= 1 << j;
            }
            bitrev[i * 2] = ((~acc) & mask) - 1;
            bitrev[i * 2 + 1] = acc;
        }
    }
    lookup->scale = lbl_80651854 / (float)n;
}
