#include "src/game/types.h"

/* Vorbis decode_aux (codebook.h) */
typedef struct DecodeAux {
    s16 *tab;
    s16 *tabl;
    s16 tabn;
    s16 *ptr0;
    s16 *ptr1;
} DecodeAux;

/* Vorbis codebook (codebook.h) */
typedef struct Codebook {
    s32 dim;
    s32 entries;
    void *c;
    void *valuelist;
    void *quantlist;
    DecodeAux *decode_tree;
} Codebook;

typedef struct OggPackBuffer OggPackBuffer;

extern s32 fn_8022E7FC(OggPackBuffer *b);            /* oggpack_read1 */
extern void fn_8022E954(OggPackBuffer *b, s32 bits); /* oggpack_adv */
extern s32 fn_8022E988(OggPackBuffer *b, s32 bits);  /* oggpack_look */

/* decode_packed_entry_number */
s32 fn_80230718(Codebook *book, OggPackBuffer *b)
{
    s32 ptr = 0;
    DecodeAux *t = book->decode_tree;
    s32 lok = fn_8022E988(b, t->tabn);

    if (lok >= 0) {
        ptr = t->tab[lok];
        fn_8022E954(b, t->tabl[lok]);
        if (ptr <= 0)
            return -ptr;
    }

    do {
        switch (fn_8022E7FC(b)) {
        case 0:
            ptr = t->ptr0[ptr];
            break;
        case 1:
            ptr = t->ptr1[ptr];
            break;
        case -1:
            return -1;
        }
    } while (ptr > 0);

    return -ptr;
}
