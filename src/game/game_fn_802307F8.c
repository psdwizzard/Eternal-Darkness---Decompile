/* fn_802307F8: Vorbis codebook header unpack (vorbis_staticbook_unpack). */

#include "src/game/types.h"

typedef struct StaticCodebook {
    s32 dim;          /* 0x00 */
    s32 entries;      /* 0x04 */
    s32 *lengthlist;  /* 0x08 */
    s32 maptype;      /* 0x0C */
    s32 q_min;        /* 0x10 */
    s32 q_delta;      /* 0x14 */
    s32 q_quant;      /* 0x18 */
    s32 q_sequencep;  /* 0x1C */
    s32 *quantlist;   /* 0x20 */
    u8 pad24[0x30 - 0x24];
    s32 allocedp;     /* 0x30 */
} StaticCodebook;

extern void *memset(void *dest, int value, unsigned long size);
extern s32 fn_8022E868(void *, s32);
extern void *fn_8022F780(s32 size);
extern s32 fn_80235B10(StaticCodebook *);
extern void fn_8023582C(StaticCodebook *);
extern s32 fn_80236144(u32);

s32 fn_802307F8(void *opb, StaticCodebook *s) {
    s32 i, j;

    memset(s, 0, sizeof(StaticCodebook));
    s->allocedp = 1;

    if (fn_8022E868(opb, 24) != 0x564342) goto _eofout;

    s->dim = fn_8022E868(opb, 16);
    s->entries = fn_8022E868(opb, 24);
    if (s->entries == -1) goto _eofout;

    switch (fn_8022E868(opb, 1)) {
    case 0:
        s->lengthlist = fn_8022F780(sizeof(*s->lengthlist) * s->entries);

        if (fn_8022E868(opb, 1)) {
            for (i = 0; i < s->entries; i++) {
                if (fn_8022E868(opb, 1)) {
                    s32 num = fn_8022E868(opb, 5);
                    if (num == -1) goto _eofout;
                    s->lengthlist[i] = num + 1;
                } else {
                    s->lengthlist[i] = 0;
                }
            }
        } else {
            for (i = 0; i < s->entries; i++) {
                s32 num = fn_8022E868(opb, 5);
                if (num == -1) goto _eofout;
                s->lengthlist[i] = num + 1;
            }
        }
        break;
    case 1:
    {
        s32 length = fn_8022E868(opb, 5) + 1;
        s->lengthlist = fn_8022F780(sizeof(*s->lengthlist) * s->entries);

        for (i = 0; i < s->entries;) {
            s32 num = fn_8022E868(opb, fn_80236144(s->entries - i));
            if (num == -1) goto _eofout;
            for (j = 0; j < num && i < s->entries; j++) {
                s->lengthlist[i] = length;
                i++;
            }
            length++;
        }
    }
        break;
    default:
        return -1;
    }

    switch ((s->maptype = fn_8022E868(opb, 4))) {
    case 0:
        break;
    case 1:
    case 2:
        s->q_min = fn_8022E868(opb, 32);
        s->q_delta = fn_8022E868(opb, 32);
        s->q_quant = fn_8022E868(opb, 4) + 1;
        s->q_sequencep = fn_8022E868(opb, 1);

        {
            s32 quantvals = 0;
            switch (s->maptype) {
            case 1:
                quantvals = fn_80235B10(s);
                break;
            case 2:
                quantvals = s->entries * s->dim;
                break;
            }

            s->quantlist = fn_8022F780(sizeof(*s->quantlist) * quantvals);
            for (i = 0; i < quantvals; i++)
                s->quantlist[i] = fn_8022E868(opb, s->q_quant);

            if (quantvals && s->quantlist[quantvals - 1] == -1) goto _eofout;
        }
        break;
    default:
        goto _eofout;
    }

    return 0;

_eofout:
    fn_8023582C(s);
    return -1;
}
