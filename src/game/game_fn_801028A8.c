typedef unsigned char u8;
typedef short s16;
typedef int s32;

typedef struct DecodeTree {
    s32 count;
    s32 root;
    s16 left[512];
    s16 right[512];
} DecodeTree;

typedef struct BitReader {
    const u8* input;
    u8 pad04[8];
    u8 current;
    u8 mask;
} BitReader;

__declspec(section ".sdata") extern s32 readTree_signed;
__declspec(section ".sdata") extern s32 readTree_scale;

static inline s16 read_bit(BitReader* reader)
{
    u8 bit;

    if (reader->mask == 0) {
        reader->current = *reader->input++;
        reader->mask = 0x80;
    }
    bit = reader->current & reader->mask;
    reader->mask >>= 1;
    return bit != 0;
}

/* NonMatching: behavior-complete recursive decode-tree loader. Explicit inline
 * suppresses the unused out-of-line helper, making the unit's .text size exact.
 * A 16-bit helper result selects retail's 0x30-byte frame. The sole remaining
 * difference is MWCC's epilogue scheduling of mtlr after the final restores.
 * Attempt 5: shared-return control flow, register/lifetime variants, and
 * equivalent type spellings did not move mtlr under the canonical settings. */
s16 _readTree(DecodeTree* tree, BitReader* reader)
{
    s16 value;
    int node;
    s16 stored;

    if (read_bit(reader)) {
        node = tree->count++;
        tree->left[node] = _readTree(tree, reader);
        tree->right[node] = _readTree(tree, reader);
        return (s16)node;
    }

    value = read_bit(reader) ? 0x80 : 0;
    value |= read_bit(reader) ? 0x40 : 0;
    value |= read_bit(reader) ? 0x20 : 0;
    value |= read_bit(reader) ? 0x10 : 0;
    value |= read_bit(reader) ? 8 : 0;
    value |= read_bit(reader) ? 4 : 0;
    value |= read_bit(reader) ? 2 : 0;
    value |= read_bit(reader) ? 1 : 0;

    stored = value;
    if (readTree_signed != 0 && (s16)value > 127) {
        stored -= 256;
    }
    stored = (s16)stored << readTree_scale;
    tree->left[(s16)value] = (s16)stored;
    return value;
}
