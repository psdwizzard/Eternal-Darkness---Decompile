typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;

typedef struct DecodeTree DecodeTree;
typedef struct BitReader {
    const u8* input;
    u8 pad04[8];
    u8 current;
    u8 mask;
    u8 pad0E[2];
    DecodeTree* tree;
} BitReader;

typedef struct ImagePlane {
    u8 pad00[4];
    u8* data;
    u16 width;
    u16 height;
    u16 stride;
    u8 pad0E[0x38 - 0xE];
} ImagePlane;

typedef struct Decoder {
    ImagePlane planes[3];
    u8 padA8[0x30D8 - 0xA8];
    BitReader differences[3];
    BitReader runs[3];
    u8 pad3150[0x3CC6 - 0x3150];
    s16 upper;
    s16 lower;
} Decoder;

s16 decodeHuff(BitReader* reader);

/* Decode the three image planes with escaped differences, zero runs,
 * and a predictor averaged from adjacent samples in the previous row. */
void IpicDcvDec(register Decoder* arg)
{
    register ImagePlane* image;
    register int plane;
    register int rounded;
    BitReader* runs;
    register u8* dest;
    register u8* previous;
    s16 value;
    register int stride;
    int run;
    register int predictor;
    int width;
    int columns;
    int rows;
    register Decoder* decoder;
    register int total;
    register u8* streams;
    s16 lower;
    register int difference;
    BitReader* differences;

    plane = 0;
    /* ASM: addi, mulli, and add retain the initial zero-index address calculation.
     * MWCC replaces the zero additions with moves and folds the multiplication. */
    asm {
        addi decoder, arg, 0
        mulli rounded, plane, 20
        addi image, decoder, 0
        add streams, decoder, rounded
    }
    /* Advance both reader arrays by one BitReader for each plane. */
    do {
        stride = image->stride * 2;
        differences = (BitReader*)(streams + 0x30D8);
        width = image->width;
        runs = (BitReader*)(streams + 0x3114);
        dest = image->data;
        rows = image->height;
        run = 0;

        for (; rows > 0; rows--) {
            previous = dest - stride;
            predictor = *previous;
            columns = width;

            for (; columns > 0; columns--) {
                if (run == 0) {
                    difference = decoder->upper;
                    total = 0;
                    lower = decoder->lower;
                    do {
                        value = decodeHuff(differences);
                        total += value;
                    } while (lower >= value || value >= difference);
                    /* ASM: extsh preserves the separate signed truncation before
                     * the short comparison; MWCC folds the two C conversions. */
                    asm { extsh difference, total }
                    if ((s16)difference == 0) {
                        run = decodeHuff(runs);
                    }
                } else {
                    difference = 0;
                    run--;
                }
                /* ASM: add, lbzu, clrlwi, addi, stb, add, and srawi preserve
                 * the byte truncation and rounded predictor in retail order.
                 * MWCC reassociates the additions and schedules the store earlier. */
                asm {
                    add r4, predictor, difference
                    lbzu r5, 2(previous)
                    clrlwi r3, r4, 24
                    addi rounded, r3, 1
                    stb r4, 0(dest)
                    add rounded, r5, rounded
                    srawi predictor, rounded, 1
                }
                dest += 2;
            }
            dest += 4;
        }
        plane++;
        image++;
        streams += sizeof(BitReader);
    } while (plane < 3);
}
