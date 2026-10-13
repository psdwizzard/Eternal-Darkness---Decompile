#include "src/game/types.h"

/* Vorbis static_codebook (codebook.h) */
typedef struct StaticCodebook {
    s32 dim;
    s32 entries;
    s32 *lengthlist;
} StaticCodebook;

/* Vorbis codebook (codebook.h) */
typedef struct Codebook {
    s32 dim;
    s32 entries;
    StaticCodebook *c;
} Codebook;

/* Vorbis decode_aux (codebook.h) */
typedef struct DecodeAux {
    s16 *tab;
    s16 *tabl;
    s16 tabn;
    s16 *ptr0;
    s16 *ptr1;
    s32 aux;
} DecodeAux;

extern void *fn_8022F780(s32 size);           /* _ogg_malloc */
extern void fn_8022F8FC(void);
extern int *fn_80235EC4(int *lengths, int count); /* _make_words */
extern void *memset(void *, int, unsigned long);

/* _make_decode_tree */
DecodeAux *fn_80235C64(Codebook *c)
{
    StaticCodebook *s = c->c;
    s32 top = 0;
    s32 i, j, n;
    DecodeAux *t = fn_8022F780(sizeof(DecodeAux));
    s16 *ptr0 = t->ptr0 = fn_8022F780(c->entries * 2 * sizeof(s16));
    s16 *ptr1 = t->ptr1 = fn_8022F780(c->entries * 2 * sizeof(s16));
    int *codelist = fn_80235EC4(s->lengthlist, s->entries);

    memset(ptr0, 0, c->entries * 2 * sizeof(s16));
    memset(ptr1, 0, c->entries * 2 * sizeof(s16));
    t->aux = c->entries * 2;
    fn_8022F8FC();

    for (i = 0; i < c->entries; i++) {
        if (s->lengthlist[i] > 0) {
            s32 ptr = 0;
            for (j = 0; j < s->lengthlist[i] - 1; j++) {
                int bit = (codelist[i] >> j) & 1;
                if (!bit) {
                    if (!ptr0[ptr]) {
                        top++;
                        ptr0[ptr] = top;
                    }
                    ptr = ptr0[ptr];
                } else {
                    if (!ptr1[ptr]) {
                        top++;
                        ptr1[ptr] = top;
                    }
                    ptr = ptr1[ptr];
                }
            }
            if (!((codelist[i] >> j) & 1))
                ptr0[ptr] = -i;
            else
                ptr1[ptr] = -i;
        }
    }

    {
        u32 v = c->entries;
        s32 ret = 0;
        while (v) {
            ret++;
            v >>= 1;
        }
        t->tabn = ret - 4;
    }
    if (t->tabn < 5)
        t->tabn = 5;
    n = 1 << t->tabn;
    t->tab = fn_8022F780(n * sizeof(s16));
    t->tabl = fn_8022F780(n * sizeof(s16));
    for (i = 0; i < n; i++) {
        s32 p = 0;
        for (j = 0; j < t->tabn && (p > 0 || j == 0); j++) {
            if (i & (1 << j))
                p = ptr1[p];
            else
                p = ptr0[p];
        }
        t->tab[i] = p;
        t->tabl[i] = j;
    }
    return t;
}
