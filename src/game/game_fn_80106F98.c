/* Initialize the compressed image streams, rebuild their Huffman trees,
 * decode the image, and write the three output planes. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;

typedef struct DecodeTree {
    int count;
    int root;
    s16 left[512];
    s16 right[512];
} DecodeTree;

typedef struct BitReader {
    const u8 *input;
    const u8 *start;
    u32 count;
    u8 current;
    u8 mask;
    u8 pad0E[2];
} BitReader;

typedef struct TreeReader {
    BitReader bits;
    DecodeTree *tree;
} TreeReader;

typedef struct ImagePlane {
    u8 pad00[4];
    u8 *data;
    u16 width, height, stride;
    u8 pad0E[0x2C - 0xE];
    u32 outputSize;
    u8 pad30[8];
} ImagePlane;

typedef struct Decoder {
    ImagePlane planes[3];
    u8 padA8[0x30D8 - 0xA8];
    TreeReader differences[3];
    TreeReader runs[3];
    TreeReader extra[3];
    TreeReader values[2];
    TreeReader valueRuns[2];
    BitReader remaining[3];
    u8 pad320C[0x3CC6 - 0x320C];
    s16 upper, lower;
    u8 mode;
} Decoder;

extern s16 _readTree(DecodeTree *, BitReader *);
extern void Ipic_BasisNumDec(Decoder *);
extern void IpicDcvDec(Decoder *);
typedef struct ImageSrc ImageSrc;
extern void MakeNest(ImageSrc *, int, int);
typedef struct Entry80104980 Entry80104980;
extern void IpicPlaneDec(Entry80104980 *, int, int *);
extern int readTree_signed;
extern int readTree_scale;

static inline u32 read_u32(const u8 *p)
{
    return ((u32)p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
}

/* Each stream starts with a big-endian count followed by its bit data. */
#define INIT_STREAM_DATA(reader, offset) \
    stream = payload + read_u32(header + (offset)); \
    (reader).count = read_u32(stream); \
    if ((reader).count == 0) { \
        (reader).start = 0; \
        (reader).input = 0; \
    } else { \
        (reader).start = stream + 4; \
        (reader).input = stream + 4; \
    }

#define INIT_STREAM(reader, offset) \
    INIT_STREAM_DATA(reader, offset); \
    (reader).mask = 0

static inline void load_tree(register BitReader *bits, DecodeTree *tree, int sign, int shift)
{
    register u32 count;
    readTree_signed = sign;
    readTree_scale = shift;
    tree->count = 0x100;
    /* ASM: lwz retains the reader address for the count test; C folds
     * that address into the conditional call setup. */
    asm { lwz count, 8(bits) }
    if (count != 0) {
        tree->root = _readTree(tree, bits);
    } else {
        tree->root = 0;
    }
}

void HVQM4DecodeIpic(Decoder **handle, const u8 *header, register u8 *output)
{
    register Decoder *decoder = *handle;
    const u8 *payload = header + 0x48;
    const u8 *stream;
    register ImagePlane *plane;
    register int i;
    register int limit;
    register int emptyMask;
    register int upperBase;
    register int lowerBase;
    register Decoder *callDecoder;

    decoder->mode = header[1];
    INIT_STREAM(decoder->values[0].bits, 0x08);
    INIT_STREAM(decoder->valueRuns[0].bits, 0x0C);
    INIT_STREAM(decoder->values[1].bits, 0x10);
    INIT_STREAM(decoder->valueRuns[1].bits, 0x14);
    INIT_STREAM(decoder->differences[0].bits, 0x18);
    INIT_STREAM(decoder->extra[0].bits, 0x1C);
    INIT_STREAM(decoder->remaining[0], 0x20);
    INIT_STREAM(decoder->differences[1].bits, 0x24);
    INIT_STREAM(decoder->extra[1].bits, 0x28);
    INIT_STREAM(decoder->remaining[1], 0x2C);
    INIT_STREAM(decoder->differences[2].bits, 0x30);
    INIT_STREAM(decoder->extra[2].bits, 0x34);
    INIT_STREAM(decoder->remaining[2], 0x38);
    INIT_STREAM(decoder->runs[0].bits, 0x3C);
    INIT_STREAM(decoder->runs[1].bits, 0x40);
    INIT_STREAM_DATA(decoder->runs[2].bits, 0x44);
    /* ASM: li and stb prevent the following tree initializer from being hoisted
     * ahead of the last stream's mask reset. */
    asm {
        li emptyMask, 0
        stb emptyMask, 0x3149(decoder)
    }

    {
        register BitReader *reader = &decoder->values[0].bits;
        DecodeTree *tree = decoder->values[0].tree;
        register u32 count;
        readTree_signed = emptyMask;
        readTree_scale = emptyMask;
        tree->count = 0x100;
        /* ASM: lwz retains the reader address for the count test; C folds
         * that address into the conditional call setup. */
        asm { lwz count, 8(reader) }
        if (count != 0) {
            tree->root = _readTree(tree, reader);
        } else {
            tree->root = emptyMask;
        }
    }
    load_tree(&decoder->valueRuns[0].bits, decoder->valueRuns[0].tree, 0, 0);
    load_tree(&decoder->differences[0].bits, decoder->differences[0].tree, 1, header[0]);
    load_tree(&decoder->extra[0].bits, decoder->extra[0].tree, 0, 2);

    limit = header[0];
    /* ASM: li keeps both bounds initialized before the signed truncations;
     * the C constants are otherwise delayed across the extsh blocks. */
    asm {
        li upperBase, 0x7F
        li lowerBase, -0x80
    }
    limit = upperBase << limit;
    /* ASM: extsh retains the signed truncation that MWCC folds into sth. */
    asm { extsh limit, limit }
    decoder->upper = limit;
    /* ASM: mr retains the call argument copy between the bound stores;
     * C schedules this copy after both stores. */
    asm { mr callDecoder, decoder }
    limit = (u32)lowerBase << header[0];
    /* ASM: extsh retains the signed truncation that MWCC folds into sth. */
    asm { extsh limit, limit }
    decoder->lower = limit;
    Ipic_BasisNumDec(callDecoder);
    IpicDcvDec(decoder);
    MakeNest((ImageSrc *)decoder, (header[4] << 8) | header[5],
                (header[6] << 8) | header[7]);
    i = 0;
    /* ASM: addi preserves the retail copy encoding; C emits mr. */
    asm { addi plane, decoder, 0 }
    do {
        register Entry80104980 *callDecoder;
        register int callIndex;
        register int *callOutput;
        /* ASM: addi preserves the three argument-copy encodings; C emits mr. */
        asm {
            addi callDecoder, decoder, 0
            addi callIndex, i, 0
            addi callOutput, output, 0
        }
        IpicPlaneDec(callDecoder, callIndex, callOutput);
        i++;
        output += plane->outputSize;
        /* ASM: addi keeps the plane advance after the output-pointer update;
         * MWCC schedules the independent C increment before it. */
        asm { addi plane, plane, 0x38 }
    } while (i < 3);
}
