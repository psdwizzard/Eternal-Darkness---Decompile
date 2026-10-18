#include "src/game/types.h"

/* Vorbis vorbis_book_decodevv_add: interleaved multi-channel accumulate. */
typedef struct DecodeAux DecodeAux;
typedef struct OggPackBuffer OggPackBuffer;

typedef struct Codebook {
    s32 dim;
    s32 entries;
    void *c;
    void *valuelist;
    void *quantlist;
    DecodeAux *decode_tree;
} Codebook;

s32 vorbis_book_decode(Codebook *book, OggPackBuffer *b);

s32 vorbis_book_decodevv_add(register Codebook *book, register float **a, s32 offset,
                register s32 ch, register OggPackBuffer *b, s32 n)
{
    register s32 byteOffset;
    register s32 chptr;
    register s32 i;
    s32 j, entry;
    s32 end;
    s32 limit = offset + n;
    /* ASM: or (mr) preserves the channel-count copy; C emits addi. */
    asm { or ch, ch, ch }
    i = offset / ch;
    /* ASM: or (mr) preserves argument copies; C emits addi. */
    asm {
        or book, book, book
        or a, a, a
        or b, b, b
    }
    /* ASM: li initializes the channel before division; C schedules it afterward. */
    asm { li chptr, 0 }
    end = limit / ch;
    byteOffset = i * sizeof(float);
    for (; i < end;) {
        register Codebook *callBook;
        register OggPackBuffer *callBuffer;
        /* ASM: or (mr) emits the retail call argument copies instead of addi. */
        asm {
            or callBook, book, book
            or callBuffer, b, b
        }
        entry = vorbis_book_decode(callBook, callBuffer);
        if (entry == -1) {
            return -1;
        }
        {
            const float *t = (const float *)book->valuelist + entry * book->dim;
            s32 columnOffset = byteOffset;
            for (j = 0; j < book->dim; t++, j++) {
                *(float *)((u8 *)a[chptr++] + columnOffset) += *t;
                if (chptr == ch) {
                    chptr = 0;
                    columnOffset += sizeof(float);
                    byteOffset += sizeof(float);
                    i++;
                }
            }
        }
    }
    return 0;
}
