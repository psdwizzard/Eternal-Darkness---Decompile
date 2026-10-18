#include "src/game/types.h"

/* Each Huffman node has a signed child in each of the two tables. */
typedef struct WeightTree {
    u32 unused;
    s32 root;
    s16 zero[512];
    s16 one[512];
} WeightTree;

typedef struct WeightBits {
    u8 *cursor;
    u32 unused04;
    u32 unused08;
    u8 byte;
    u8 mask;
    u8 padding[2];
    WeightTree *tree;
} WeightBits;

typedef struct WeightStream {
    u8 *cursor;
    u8 padding[12];
} WeightStream;

typedef struct WeightDecoder {
    u8 padding00[0x3150];
    WeightBits bits[3];
    u8 padding318C[0x31DC - 0x318C];
    WeightStream streams[3];
    u8 padding320C[0x3260 - 0x320C];
    u8 transposed;
} WeightDecoder;

extern s32 divTable[];

/* Read one 4x4 basis block and its differential Huffman-coded weight. */
s32 GetMCAotBasis(register WeightDecoder *decoder, register u8 *block, register s32 *state,
                register s32 table, register s32 stride, register s32 index)
{
    register WeightTree *tree;
    register s16 node;
    register WeightBits *bits;
    register s32 mask;
    register s32 shift;
    register u32 code;
    register u16 packed;
    register s32 xstep;
    register s32 field, offset, column;
    register u8 *pixel;
    register u8 high;
    register u8 minimum;
    register u8 low;
    register WeightDecoder *stream;
    register u8 bit;
    register u8 maximum;
    register u8 *row;

    xstep = table;
    stream = (WeightDecoder *)((u8 *)decoder + index * 16);
    high = *stream->streams[0].cursor++;
    low = *stream->streams[0].cursor++;
    code = (high << 8) | low;

    if (decoder->transposed) {
        field = ((code >> 6) & 31);
        offset = field * stride;
        /* ASM: add/extrwi retain the retail address
         * grouping and evaluation order that MWCC changes in C. */
        asm {
            add row, offset, xstep
            extrwi field, code, 1, 19
        }
        column = code & 63;
        xstep = (code >> 11) & 1;
        offset = 1;
        /* ASM: add/slw retain the retail address
         * grouping and evaluation order that MWCC changes in C. */
        asm {
            add row, column, row
            slw xstep, offset, xstep
        }
    } else {
        field = (code & 63);
        offset = field * stride;
        /* ASM: add/extrwi retain the retail address
         * grouping and evaluation order that MWCC changes in C. */
        asm {
            add row, offset, xstep
            extrwi field, code, 1, 20
        }
        column = (code >> 6) & 31;
        xstep = (code >> 12) & 1;
        offset = 1;
        /* ASM: add/slw retain the retail address
         * grouping and evaluation order that MWCC changes in C. */
        asm {
            add row, column, row
            slw xstep, offset, xstep
        }
    }

    if (field) stride <<= 1;

    minimum = (*row & 0xF0) >> 4;
    block[0] = minimum;
    maximum = minimum;
    pixel = row + xstep;

#define SAMPLE_WEIGHT(i, p) \
    if ((block[i] = (*(p) & 0xF0) >> 4) > maximum) maximum = block[i]; \
    if (block[i] < minimum) minimum = block[i]

    SAMPLE_WEIGHT(1, pixel);
    pixel += xstep;
    SAMPLE_WEIGHT(2, pixel);
    pixel += xstep;
    SAMPLE_WEIGHT(3, pixel);
    row += stride;
    SAMPLE_WEIGHT(4, row);
    pixel = row + xstep;
    SAMPLE_WEIGHT(5, pixel);
    pixel += xstep;
    SAMPLE_WEIGHT(6, pixel);
    pixel += xstep;
    SAMPLE_WEIGHT(7, pixel);
    row += stride;
    SAMPLE_WEIGHT(8, row);
    pixel = row + xstep;
    SAMPLE_WEIGHT(9, pixel);
    pixel += xstep;
    SAMPLE_WEIGHT(10, pixel);
    pixel += xstep;
    SAMPLE_WEIGHT(11, pixel);
    row += stride;
    SAMPLE_WEIGHT(12, row);
    pixel = row + xstep;
    SAMPLE_WEIGHT(13, pixel);
    pixel += xstep;
    SAMPLE_WEIGHT(14, pixel);
    pixel += xstep;
    SAMPLE_WEIGHT(15, pixel);
#undef SAMPLE_WEIGHT

    tree = decoder->bits[index].tree;
    bits = &decoder->bits[index];
    node = tree->root;
    while (node >= 256) {
        if (bits->mask == 0) {
            bits->byte = *bits->cursor++;
            bits->mask = 0x80;
        }
        bit = bits->byte;
        /* ASM: li supplies the retail shift count in a register;
         * C uses an immediate shift for the constant one-bit step. */
        asm { li shift, 1 }
        mask = bits->mask;
        bit &= mask;
        bits->mask = (s32)mask >> shift;
        if (bit) {
            node = tree->one[node];
        } else {
            node = tree->zero[node];
        }
    }
    *state += tree->zero[node];
    packed = code;
    if (code & 0x8000) {
        return (*state + ((packed >> 13) & 3)) * -*(s32 *)((u8 *)divTable + (maximum - minimum) * 4);
    }
    return (*state + ((packed >> 13) & 3)) * *(s32 *)((u8 *)divTable + (maximum - minimum) * 4);
}
