/* Ipic_BasisNumDec: run-length/Huffman decode the three image planes. Plane 0 is
 * written to its own buffer; planes 1 and 2 share one stream whose symbols
 * carry both 4-bit values. A zero symbol is followed by a run of zeros. */

typedef unsigned char u8;
typedef unsigned short u16;
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

typedef struct Plane {
    u8* data;
    u16 width;
    u16 height;
    u8 pad08[0x30];
} Plane;

typedef struct Decoder {
    u8 pad00[4];
    Plane planes[3];
    u8 pad_a8[0x318C - 0xAC];
    BitReader value0;
    BitReader value1;
    BitReader run0;
    BitReader run1;
} Decoder;

/* NonMatching under GC/1.3: retail's `li rN,1; sraw` mask shift, the
 * unfolded reader pointers (r9/r10) and the r31/0x48 frame are GC/1.2.5n
 * codegen, the version the sibling decodeHuff (same decoder, Matching)
 * is built with. The control flow and data layout already line up. */
static inline u8 read_bit(BitReader* reader)
{
    u8 bit;

    if (reader->mask == 0) {
        reader->current = *reader->input++;
        reader->mask = 0x80;
    }
    bit = reader->current & reader->mask;
    reader->mask >>= 1;
    return bit;
}

static inline s16 decode_symbol(BitReader* reader)
{
    DecodeTree* tree = reader->tree;
    s16 node = tree->root;

    while (node >= 256) {
        if (read_bit(reader) != 0) {
            node = tree->right[node];
        } else {
            node = tree->left[node];
        }
    }
    return tree->left[node];
}

void Ipic_BasisNumDec(Decoder* dec)
{
    BitReader* valueReader;
    BitReader* runReader;
    u8* out;
    u8* outU;
    u8* outV;
    int width;
    int height;
    int run;
    int x;
    s16 value;

    valueReader = &dec->value0;
    runReader = &dec->run0;
    run = 0;
    out = dec->planes[0].data;
    width = dec->planes[0].width;
    height = dec->planes[0].height;
    for (; height > 0; height--) {
        for (x = 0; x < width; x++) {
            if (run == 0) {
                value = decode_symbol(valueReader);
                if (value == 0) {
                    run = decode_symbol(runReader);
                }
                out[1] = value;
                out += 2;
            } else {
                out[1] = 0;
                out += 2;
                run--;
            }
        }
        out += 4;
    }

    outU = dec->planes[1].data;
    valueReader = &dec->value1;
    outV = dec->planes[2].data;
    runReader = &dec->run1;
    width = dec->planes[1].width;
    height = dec->planes[1].height;
    run = 0;
    for (; height > 0; height--) {
        for (x = 0; x < width; x++) {
            if (run == 0) {
                value = decode_symbol(valueReader);
                if (value == 0) {
                    run = decode_symbol(runReader);
                }
                outU[1] = value & 0xF;
                outU += 2;
                outV[1] = (value >> 4) & 0xF;
                outV += 2;
            } else {
                outU[1] = 0;
                run--;
                outU += 2;
                outV[1] = 0;
                outV += 2;
            }
        }
        outU += 4;
        outV += 4;
    }
}
