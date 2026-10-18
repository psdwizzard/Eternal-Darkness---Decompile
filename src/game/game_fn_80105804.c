#include "src/game/types.h"

typedef struct DecodeTree DecodeTree;
typedef struct BitReader {
    const u8 *input;
    u8 pad04[8];
    u8 current;
    u8 mask;
    u8 pad0E[2];
    DecodeTree *tree;
} BitReader;

typedef struct Decoder {
    u8 pad00[0x30D8];
    BitReader readers[3];
    u8 pad3114[0x3CC6 - 0x3114];
    s16 upper;
    s16 lower;
    u8 shift;
    u8 value_shift;
} Decoder;

extern s16 decodeHuff(BitReader *reader);
extern s32 GetMCAotSum(s32 decoder, s32 *sums, u8 count, s32 base,
                     s32 baseStride, s32 plane);
extern void _MotionComp(u8 *dst, s32 dstStride, u8 *src, s32 srcStride,
                       s32 halfX, s32 halfY);
extern u8 lbl_8032CC08[];

/* Center one reference sample and update the block's signed range. */
#define CENTER_SAMPLE(n)                                                  \
    do {                                                                  \
        if ((residuals[n] = pixels[n] - mean) < minimum) {                  \
            minimum = residuals[n];                                       \
        }                                                                 \
        value32 = residuals[n];                                           \
        if (value32 > maximum) {                                          \
            maximum = value32;                                            \
        }                                                                 \
    } while (0)

/* Reconstruct a 4x4 motion block from the reference and coded residuals. */
void PrediAotBlock(register Decoder *decoder, register u8 *inputDst,
                 register u8 *inputReference, register u16 inputStride,
                 register u32 mode, register u8 *inputBase,
                 register u16 inputBaseStride, register s32 inputPlane,
                 register s32 halfX, register s32 halfY)
{
    register u8 *dst, *reference, *base;
    register s32 stride, baseStride, plane, planeArg;
    register u8 *copyReference;
    register s32 copyStride, copyHalfX, copyHalfY, returnedMean;
    s32 sums[16];
    u8 pixels[16];
    volatile s32 residuals[16];
    u8 *clamp = lbl_8032CC08;
    register s32 *sumsCursor;
    register volatile s32 *accum;
    volatile s32 *residual;
    u8 *pixel;
    register s32 mean, minimum, maximum;
    register s32 total, bias, scale, i;
    register s32 readerOffset;
    register s32 codedMean, value32;
    register u8 count;
    s32 adjustment, previous;
    s32 totalFirst;
    s16 upperFirst;
    register s16 value, upper, lower;
    register s32 shift;
    register BitReader *reader;

    /* ASM: addi/subi retain retail's argument-copy operations. C emits
     * mr for the copies and an extra mask when narrowing the block count. */
    asm {
        addi reference, inputReference, 0
        addi stride, inputStride, 0
        addi dst, inputDst, 0
        addi plane, inputPlane, 0
        addi count, mode, -1
        addi base, inputBase, 0
        addi baseStride, inputBaseStride, 0
        addi planeArg, plane, 0
    }
    returnedMean = GetMCAotSum((s32)decoder, sums, count, (s32)base,
                              baseStride, planeArg);
    /* ASM: addi retains retail's return-value and interpolation-argument
     * copies, which this compiler emits as mr in equivalent C. */
    asm {
        addi codedMean, returnedMean, 0
        addi copyReference, reference, 0
        addi copyStride, stride, 0
        addi copyHalfX, halfX, 0
        addi copyHalfY, halfY, 0
    }
    _MotionComp(pixels, 4, copyReference, copyStride, copyHalfX, copyHalfY);
    /* Round the reference mean to the nearest whole sample. */
    mean = (pixels[1] + pixels[2] + pixels[3] + pixels[4] + pixels[5] +
            pixels[6] + pixels[7] + pixels[8] + pixels[9] + pixels[10] +
            pixels[11] + pixels[12] + pixels[13] + pixels[14] +
            pixels[15] + pixels[0] + 8) >> 4;
    minimum = maximum = pixels[0] - mean;
    residuals[0] = minimum;
    CENTER_SAMPLE(1);
    CENTER_SAMPLE(2);
    CENTER_SAMPLE(3);
    CENTER_SAMPLE(4);
    CENTER_SAMPLE(5);
    CENTER_SAMPLE(6);
    CENTER_SAMPLE(7);
    CENTER_SAMPLE(8);
    CENTER_SAMPLE(9);
    CENTER_SAMPLE(10);
    CENTER_SAMPLE(11);
    CENTER_SAMPLE(12);
    CENTER_SAMPLE(13);
    CENTER_SAMPLE(14);
    CENTER_SAMPLE(15);

    readerOffset = plane * sizeof(BitReader) + 0x30D8;
    plane = decoder->shift;
    shift = plane;
    upperFirst = decoder->upper;
    lower = decoder->lower;
    /* ASM: add keeps the reader displacement grouped before the decoder
     * base; MWCC reassociates C pointer arithmetic around the 0x30D8 offset. */
    asm { add reader, decoder, readerOffset }
    /* Escape symbols contribute to the value until an interior symbol ends it. */
    totalFirst = 0;
    do {
        value = decodeHuff(reader);
        totalFirst += value;
    } while (lower >= value || value >= upperFirst);
    bias = (s32)((u32)(totalFirst >> decoder->value_shift) << shift) - codedMean;

    /* Decode the contrast gain with the same escape rule. */
    total = 0;
    upper = decoder->upper;
    lower = decoder->lower;
    do {
        value = decodeHuff(reader);
        total += value;
    } while (lower >= value || value >= upper);
    value32 = ((s32 *)(clamp + 0x240))[maximum - minimum];
    scale = total >> decoder->value_shift;
    scale = value32 * scale;
    sumsCursor = sums;
    /* ASM: addi retains the retail accumulator-pointer copy; C emits mr. */
    asm { addi accum, sumsCursor, 0 }
    residual = residuals;
    for (i = 0; i < 16; i++) {
        adjustment = *residual++;
        previous = *accum;
        adjustment = scale * adjustment;
        adjustment = adjustment + previous;
        *accum++ = bias + adjustment;
    }
    /* Emit two rows per iteration; the unsigned indices preserve the
     * original indexed coefficient loads. */
    pixel = pixels;
    for (i = 0; i < 16; i += 8) {
        dst[0] = clamp[pixel[0] + (sumsCursor[0] >> shift) + 0x80];
        dst[1] = clamp[pixel[1] + (sums[(u32)(i + 1)] >> shift) + 0x80];
        dst[2] = clamp[pixel[2] + (sums[(u32)(i + 2)] >> shift) + 0x80];
        dst[3] = clamp[pixel[3] + (sums[(u32)(i + 3)] >> shift) + 0x80];
        dst += stride;
        dst[0] = clamp[pixel[4] + (sumsCursor[4] >> shift) + 0x80];
        dst[1] = clamp[pixel[5] + (sums[(u32)(i + 5)] >> shift) + 0x80];
        dst[2] = clamp[pixel[6] + (sums[(u32)(i + 6)] >> shift) + 0x80];
        dst[3] = clamp[pixel[7] + (sums[(u32)(i + 7)] >> shift) + 0x80];
        dst += stride;
        pixel += 8;
        sumsCursor += 8;
    }
}

#undef CENTER_SAMPLE
