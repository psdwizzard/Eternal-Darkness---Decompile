#include "src/game/types.h"

typedef struct DecodeTree {
    s32 count;
    s32 root;
    s16 left[512];
    s16 right[512];
} DecodeTree;

typedef struct BitReader {
    const u8 *input;
    u8 pad04[8];
    u8 current;
    u8 mask;
    u8 pad0E[2];
    DecodeTree *tree;
} BitReader;

typedef struct ModePlane {
    u8 pad00[0x10];
    u16 indices[4];
    u8 pad18[0x1C];
    u8 count;
    u8 pad35[3];
} ModePlane;

typedef struct Decoder {
    ModePlane planes[3];
    u8 padA8[0x318C - 0xA8];
    BitReader values[2];
    BitReader runs[2];
} Decoder;

typedef struct PlaneCursor {
    s32 run;
    u8 pad04[4];
    u8 *modes;
    u8 pad0C[0x28];
} PlaneCursor;

typedef struct FrameContext {
    PlaneCursor planes[3];
} FrameContext;

static inline u8 read_bit(register BitReader *reader)
{
    register u8 mask;
    register u8 bit;
    register s32 shift;

    if (reader->mask == 0) {
        reader->current = *reader->input++;
        reader->mask = 0x80;
    }
    bit = reader->current;
    /* ASM: li keeps the one-bit shift count in a register. MWCC otherwise
     * substitutes an immediate shift for the retail variable shift. */
    asm { li shift, 1 }
    mask = reader->mask;
    bit &= mask;
    reader->mask = mask >> shift;
    return bit;
}

static inline s16 decode_symbol(register BitReader *reader)
{
    register DecodeTree *tree = reader->tree;
    register s16 node = tree->root;

    while (node >= 256) {
        if (read_bit(reader)) {
            node = tree->right[node];
        } else {
            node = tree->left[node];
        }
    }
    return tree->left[node];
}

/* Set the block modes, decoding luma and paired chroma symbols as needed. */
void decode_PB_cc(register Decoder *decoder, register FrameContext *context,
                 register s32 mode, register s32 flags)
{
    register s32 base = (flags << 5) | (mode << 4);
    register ModePlane *plane;
    register PlaneCursor *cursor;
    register BitReader *values;
    register BitReader *runs;
    register s32 count;
    register u8 *out;
    register u8 *outV;
    register u16 *indices;
    register s32 p;
    register s32 i;
    register s32 index;
    register s16 value;
    register DecodeTree *tree;
    register s16 node;

    if (mode == 1) {
        plane = decoder->planes;
        cursor = context->planes;
        p = 0;
        do {
            count = plane->count;
            indices = plane->indices;
            out = cursor->modes;
            for (i = 0; i < count; i++) {
                index = *indices;
                indices++;
                out[2 * index + 1] = base;
            }
            p++;
            plane++;
            cursor++;
        } while (p < 3);
        return;
    }

    count = decoder->planes[0].count;
    /* ASM: addi keeps the luma value reader in its own register.
     * C otherwise folds the offset into accesses through the decoder. */
    asm { addi values, decoder, 0x318C }
    out = context->planes[0].modes;
    /* ASM: addi keeps the luma run reader in its own register.
     * C otherwise folds the offset into accesses through the decoder. */
    asm { addi runs, decoder, 0x31B4 }
    indices = decoder->planes[0].indices;
    for (i = 0; i < count; i++) {
        index = *indices++;
        if (context->planes[0].run == 0) {
            tree = values->tree;
            node = tree->root;
            while (node >= 256) {
                if (read_bit(values)) {
                    node = tree->right[node];
                } else {
                    node = tree->left[node];
                }
            }
            value = tree->left[node];
            if (value == 0) {
                out[2 * index + 1] = base;
                context->planes[0].run = decode_symbol(runs);
            } else {
                out[2 * index + 1] = (base & 255) | value;
            }
        } else {
            out[2 * index + 1] = base;
            context->planes[0].run--;
        }
    }

    {
        register ModePlane *chroma;
        register BitReader *chromaValues, *chromaRuns;
        register u8 *outU;
        register u16 *chromaIndices;
        register s32 chromaCount;
        register s32 chromaBlock, chromaIndex;
        register s16 chromaValue;
        /* ASM: addi preserves the chroma plane base. C folds this and the
         * later index-array offset into one decoder-relative addition. */
        asm { addi chroma, decoder, 0x38 }
        outU = context->planes[1].modes;
        chromaCount = chroma->count;
        /* ASM: addi keeps the chroma value reader in its own register.
         * C otherwise folds the offset into accesses through the decoder. */
        asm { addi chromaValues, decoder, 0x31A0 }
        outV = context->planes[2].modes;
        /* ASM: addi keeps the chroma run reader in its own register.
         * C otherwise folds the offset into accesses through the decoder. */
        asm { addi chromaRuns, decoder, 0x31C8 }
        chromaIndices = chroma->indices;
        for (chromaBlock = 0; chromaBlock < chromaCount; chromaBlock++) {
            chromaIndex = *chromaIndices++;
            if (context->planes[1].run == 0) {
                tree = chromaValues->tree;
                node = tree->root;
                while (node >= 256) {
                    if (read_bit(chromaValues)) {
                        node = tree->right[node];
                    } else {
                        node = tree->left[node];
                    }
                }
                chromaValue = tree->left[node];
                if (chromaValue == 0) {
                    outU[2 * chromaIndex + 1] = base;
                    outV[2 * chromaIndex + 1] = base;
                    tree = chromaRuns->tree;
                    node = tree->root;
                    while (node >= 256) {
                        if (read_bit(chromaRuns)) {
                            node = tree->right[node];
                        } else {
                            node = tree->left[node];
                        }
                    }
                    context->planes[1].run = tree->left[node];
                } else {
                    register u32 lowMode, byteOffset, highMode;
                    /* ASM: clrlwi, slwi, and extrwi preserve the retail nibble
                     * extraction order, which C changes around the first OR. */
                    asm {
                        clrlwi lowMode, chromaValue, 28
                        slwi byteOffset, chromaIndex, 1
                        extrwi highMode, chromaValue, 4, 24
                    }
                    outU[byteOffset + 1] = (base & 255) | lowMode;
                    outV[byteOffset + 1] = (base & 255) | highMode;
                }
            } else {
                outU[2 * chromaIndex + 1] = base;
                outV[2 * chromaIndex + 1] = base;
                context->planes[1].run--;
            }
        }
    }
}
