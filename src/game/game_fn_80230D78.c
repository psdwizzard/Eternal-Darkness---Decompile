#include "src/game/types.h"

typedef struct ToneTable {
    s32 count;      /* 0x00 */
    s32 length;     /* 0x04 */
    s32 param;      /* 0x08 */
    s32 *steps;     /* 0x0C */
    s32 *params;    /* 0x10 */
    float *samples; /* 0x14 */
    u8 pad[0x8];    /* 0x18 */
} ToneTable;

typedef struct ToneSource {
    u8 pad[0x1C];
    s32 *sizes;     /* 0x1C */
} ToneSource;

extern void *fn_8022F780(s32 size);
extern double fn_8010161C(double x);
extern double fn_80101988(double x);
extern double fn_80101A5C(double x);

extern float lbl_806517BC;
extern float lbl_806517C0;
extern float lbl_806517C4;
extern float lbl_806517C8;
extern float lbl_806517CC;
extern float lbl_806517D0;
extern float lbl_806517D4;
extern float lbl_806517D8;

ToneTable *fn_80230D78(ToneSource **src, s32 *index, s32 *params) {
    s32 *sizes = (*src)->sizes;
    ToneTable *table = fn_8022F780(sizeof(ToneTable));
    float a;
    float b;
    float x;
    float scale;
    float kSq;
    float kRate;
    float kLin;
    float kRamp;
    float kLinW;
    float kSqW;
    s32 i;
    s32 v;

    table->param = params[0];
    table->count = sizes[*index] / 2;
    table->length = params[2];
    table->params = params;

    x = params[1] * lbl_806517C0;
    a = fn_8010161C(lbl_806517BC * (x * x));
    b = fn_8010161C(lbl_806517C4 * (params[1] * lbl_806517C0));
    scale = (float)table->length /
            (lbl_806517C8 * (params[1] * lbl_806517C0) + (lbl_806517CC * b + lbl_806517D0 * a));

    table->steps = fn_8022F780((table->count + 1) * 4);
    kSq = lbl_806517BC;
    kRate = lbl_806517C0;
    kLin = lbl_806517C4;
    kRamp = lbl_806517C8;
    kLinW = lbl_806517CC;
    kSqW = lbl_806517D0;
    for (i = 0; i < table->count; i++) {
        x = i * ((params[1] * kRate) / table->count);
        a = fn_8010161C(kSq * (x * x));
        b = fn_8010161C(kLin * (i * ((params[1] * kRate) / table->count)));
        v = fn_80101A5C(scale * (kRamp * (i * ((params[1] * kRate) / table->count)) +
                                 (kLinW * b + kSqW * a)));
        if (v >= table->length) {
            v = table->length;
        }
        table->steps[i] = v;
    }
    table->steps[i] = -1;

    table->samples = fn_8022F780(table->length * 4);
    for (i = 0; i < table->length; i++) {
        table->samples[i] = lbl_806517D8 * (float)fn_80101988(lbl_806517D4 / table->length * i);
    }
    return table;
}
