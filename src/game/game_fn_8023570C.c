#include "src/game/types.h"

/* Vorbis static codebook and its runtime decoding data. */
typedef struct StaticCodebook {
    s32 dim;
    s32 entries;
    s32 *lengthlist;
    s32 maptype;
    s32 q_min;
    s32 q_delta;
    s32 q_quant;
    s32 q_sequencep;
    s32 *quantlist;
} StaticCodebook;

typedef struct DecodeAux {
    s16 *tab;
    s16 *tabl;
    s16 tabn;
    s16 *ptr0;
    s16 *ptr1;
    s32 aux;
} DecodeAux;

typedef struct Codebook {
    s32 dim;
    s32 entries;
    StaticCodebook *c;
    float *valuelist;
    s32 *codelist;
    DecodeAux *decode_tree;
    s32 dec_maxlength;
} Codebook;

extern void *memset(void *, int, unsigned long);
extern void fn_8022F8FC(void);
extern float *fn_802358A0(StaticCodebook *b);
extern DecodeAux *fn_80235C64(Codebook *c);

static void clear_codebook(register Codebook *c)
{
    if (c->decode_tree) {
        memset(c->decode_tree, 0, sizeof(*c->decode_tree));
    }
    {
        register Codebook *clear;
        /* ASM: or (mr) keeps the cleanup argument copy as a register move;
         * a C pointer assignment is emitted as addi with zero. */
        asm { or clear, c, c }
        memset(clear, 0, sizeof(*clear));
    }
}

/* vorbis_book_init_decode */
s32 fn_8023570C(register Codebook *book, register StaticCodebook *source)
{
    register StaticCodebook *s;
    register Codebook *c;
    /* ASM: or (mr) preserves the retail pointer moves; this compiler emits
     * addi with a zero immediate for C pointer assignments. */
    asm {
        or s, source, source
        or c, book, book
    }
    memset(book, 0, sizeof(*book));
    fn_8022F8FC();
    c->c = s;
    c->entries = s->entries;
    c->dim = s->dim;
    c->valuelist = fn_802358A0(s);
    c->decode_tree = fn_80235C64(c);
    if (c->decode_tree) {
        return 0;
    }
    clear_codebook(c);
    return -1;
}
