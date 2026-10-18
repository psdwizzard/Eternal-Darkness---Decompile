extern double sin(double x);

extern const volatile float lbl_80651890;
extern const volatile float lbl_80651894;
extern const volatile float lbl_80651898;
extern const volatile float lbl_8065189C;
extern const volatile float lbl_806518A0;
extern const volatile double lbl_806518A8;

typedef union IntToDouble {
    double value;
    struct { unsigned int high, low; } words;
} IntToDouble;

/* Evaluate the rising, flat, or falling portion of the window. */
float _vorbis_window(int disabled, register int pos, register int total,
                  register int fadeIn, register int fadeOut) {
    float result = lbl_80651890;
    register int inBias;
    register int outBias;
    register int inStart;
    register int outStart;
    register int quarter;
    float sine;
    register double finalSine;
    register float rounded, returnTemp;
    register float width;
    register float sample;
    register double encodedSample;
    register double bias;
    register double encodedWidth;
    register float half;
    register float pi;
    volatile IntToDouble numerator, denominator;

    if (disabled != 0) {
        return result;
    }
    inBias = (unsigned int)fadeIn >> 31;
    outBias = (unsigned int)fadeOut >> 31;
    inBias = inBias + fadeIn;
    inStart = inBias >> 1;
    outBias = outBias + fadeOut;
    /* ASM: srawi and addze divide by four with truncation toward zero.
     * The C division merges the intermediate and quotient registers. */
    asm {
        srawi inBias, total, 2
        addze quarter, inBias
    }
    inStart = quarter - inStart;
    inBias = outBias >> 1;
    outStart = (total - quarter) - inBias;

    if (pos >= inStart && pos < fadeIn + inStart) {
        register unsigned int exponent, sampleBits;
        register int offset = pos - inStart;
        /* ASM: lis and xoris retain the separate exponent and biased integer
         * registers used by the signed integer-to-float conversion;
         * C emits the exponent setup before computing the sample offset. */
        asm {
            lis exponent, 0x4330
            xoris sampleBits, offset, 0x8000
        }
        numerator.words.high = exponent;
        bias = lbl_806518A8;
        numerator.words.low = sampleBits;
        half = lbl_80651898;
        encodedSample = numerator.value;
        denominator.words.low = (unsigned int)fadeIn ^ 0x80000000;
        /* ASM: fsubs rounds the explicit integer-bias subtraction to float;
         * this MWCC emits fsub and frsp for the corresponding C cast. */
        asm { fsubs sample, encodedSample, bias }
        pi = lbl_80651894;
        denominator.words.high = exponent;
        encodedWidth = denominator.value;
        sample = half + sample;
        /* ASM: fsubs converts the denominator directly to single precision,
         * avoiding MWCC's separate double subtraction and rounding. */
        asm { fsubs width, encodedWidth, bias }
        width = pi * (sample / width);
        sine = sin(width * half);
        sine *= sine;
        sine *= lbl_8065189C;
        finalSine = sin(sine);
        /* ASM: frsp and fmr retain the separate rounding and return transfer.
         * MWCC coalesces the C cast and return into a single frsp to f1. */
        asm {
            frsp returnTemp, finalSine
            fmr rounded, returnTemp
        }
        return rounded;
    }
    if (pos >= outStart && pos < outStart + fadeOut) {
        register float fallHalf;
        register double fallBias;
        register unsigned int widthBits;
        register unsigned int exponent;
        register unsigned int sampleBits;
        register int offset;
        offset = pos - outStart;
        /* ASM: lis and subf keep the exponent setup between the offset
         * subtractions; C schedules the exponent store before the subf. */
        asm {
            lis exponent, 0x4330
            subf sampleBits, offset, fadeOut
        }
        denominator.words.high = exponent;
        /* ASM: xoris keeps the two biased integers in separate registers;
         * C reuses the numerator register before encoding the width. */
        asm {
            xoris sampleBits, sampleBits, 0x8000
            xoris widthBits, fadeOut, 0x8000
        }
        denominator.words.low = sampleBits;
        fallBias = lbl_806518A8;
        encodedSample = denominator.value;
        numerator.words.low = widthBits;
        /* ASM: fsubs rounds the explicit integer-bias subtraction to float;
         * this MWCC emits fsub and frsp for the corresponding C cast. */
        asm { fsubs sample, encodedSample, fallBias }
        fallHalf = lbl_80651898;
        numerator.words.high = exponent;
        pi = lbl_80651894;
        encodedWidth = numerator.value;
        sample = sample - fallHalf;
        /* ASM: fsubs converts the denominator directly to single precision,
         * avoiding MWCC's separate double subtraction and rounding. */
        asm { fsubs width, encodedWidth, fallBias }
        width = pi * (sample / width);
        sine = sin(width * fallHalf);
        sine *= sine;
        sine *= lbl_8065189C;
        finalSine = sin(sine);
        /* ASM: frsp and fmr retain the separate rounding and return transfer.
         * MWCC coalesces the C cast and return into a single frsp to f1. */
        asm {
            frsp returnTemp, finalSine
            fmr rounded, returnTemp
        }
        return rounded;
    }
    if (pos >= inStart + fadeIn && pos < outStart) {
        result = lbl_806518A0;
    }
    return result;
}
