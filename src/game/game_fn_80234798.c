typedef int s32;
typedef struct ResidueLook ResidueLook;
typedef struct LevelTable LevelTable;

extern s32 **fn_80234C38(void *vb, ResidueLook *look, float **in, s32 ch,
                       s32 (*classify)(float *, s32, ResidueLook *, s32, s32));
extern s32 fn_80234E9C(float *in, s32 n, LevelTable **tablep, s32 count,
                      s32 value);

/* Compact active channels before classifying residue partitions. */
s32 **fn_80234798(void *vb, ResidueLook *look, float **in, s32 *nonzero,
                  s32 ch)
{
    float **channel = in;
    s32 used = 0;

    if (ch > 0) {
        do {
            if (*nonzero) {
                in[used++] = *channel;
            }
            nonzero++;
            channel++;
        } while (--ch);
    }

    if (used) {
        return fn_80234C38(vb, look, in, used,
            (s32 (*)(float *, s32, ResidueLook *, s32, s32))fn_80234E9C);
    }
    return 0;
}
