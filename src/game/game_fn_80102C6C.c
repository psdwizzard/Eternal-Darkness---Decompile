typedef unsigned char u8;
typedef short s16;

typedef struct DecodeTree {
    int count;
    int root;
    s16 left[512];
    s16 right[512];
} DecodeTree;

typedef struct BitReader {
    const u8* input;
    u8 pad04[8];
    u8 current;
    u8 mask;
    u8 pad0E[2];
    DecodeTree* tree;
} BitReader;

s16 fn_80102C6C(BitReader* reader)
{
    DecodeTree* tree = reader->tree;
    s16 node = tree->root;

    while (node >= 256) {
        int bit;

        if (reader->mask == 0) {
            reader->current = *reader->input++;
            reader->mask = 0x80;
        }
        bit = reader->current & reader->mask;
        reader->mask >>= 1;
        if ((u8)bit != 0) {
            node = tree->right[node];
        } else {
            node = tree->left[node];
        }
    }
    return tree->left[node];
}
