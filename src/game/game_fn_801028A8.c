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

__declspec(section ".sdata") extern s32 lbl_8064CC68;
__declspec(section ".sdata") extern s32 lbl_8064CC6C;

static int read_bit(BitReader* reader)
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

/* NonMatching: behavior-complete recursive decode-tree loader. Code and
 * relocations agree apart from MWCC reserving a 0x40-byte frame for this split
 * TU where retail reserves 0x30 bytes; only frame allocation and the associated
 * prologue/epilogue stack offsets differ. */
s16 fn_801028A8(DecodeTree* tree, BitReader* reader)
{
    s16 value;
    int node;
    s16 stored;

    if (read_bit(reader)) {
        node = tree->count++;
        tree->left[node] = fn_801028A8(tree, reader);
        tree->right[node] = fn_801028A8(tree, reader);
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
    if (lbl_8064CC68 != 0 && (s16)value > 127) {
        stored -= 256;
    }
    stored = (s16)stored << lbl_8064CC6C;
    tree->left[(s16)value] = (s16)stored;
    return value;
}
