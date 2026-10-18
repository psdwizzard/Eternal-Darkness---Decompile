extern double sin(double x); /* sin */

extern float lbl_80651890;
extern float lbl_80651894;
extern float lbl_80651898;
extern float lbl_8065189C;
extern float lbl_806518A0;
extern double lbl_806518A8;

typedef union IntToDouble {
    double value;
    struct { unsigned int high, low; } words;
} IntToDouble;

/* Evaluate the rising, flat, or falling portion of the window. */
float _vorbis_window(int disabled, int pos, register int total,
                  register int fadeIn, register int fadeOut) {
    float result = lbl_80651890;
    register int inBias;
    register int outBias;
    register int inStart;
    register int outStart;
    register int quarter;
    float sine;
    register double finalSine;
    register float rounded;
    register float sample, width;
    float half, pi;
    volatile IntToDouble numerator, denominator;
    register double encodedSample, bias, encodedWidth;

    if (disabled != 0) {
        return result;
    }
    /* ASM: srwi, add, srawi and addze implement truncating signed
     * divisions. MWCC otherwise chooses carry-based division by two and
     * merges the quotient register for division by four. */
    asm {
        srwi inBias, fadeIn, 31
        srwi outBias, fadeOut, 31
        add inBias, inBias, fadeIn
        srawi inStart, inBias, 1
        add outBias, outBias, fadeOut
        srawi inBias, total, 2
        addze quarter, inBias
    }
    inStart = quarter - inStart;
    /* ASM: srawi completes the biased signed division. The C shift changes
     * register allocation and schedules the comparison ahead of it. */
    asm { srawi inBias, outBias, 1 }
    outStart = (total - quarter) - inBias;

    if (pos >= inStart && pos < fadeIn + inStart) {
        numerator.words.high = 0x43300000;
        numerator.words.low = (unsigned int)(pos - inStart) ^ 0x80000000;
        bias = lbl_806518A8;
        half = lbl_80651898;
        encodedSample = numerator.value;
        denominator.words.low = (unsigned int)fadeIn ^ 0x80000000;
        /* ASM: fsubs rounds the explicit integer-bias subtraction to float;
         * this MWCC emits fsub and frsp for the corresponding C cast. */
        asm { fsubs sample, encodedSample, bias }
        sample = half + sample;
        pi = lbl_80651894;
        denominator.words.high = 0x43300000;
        encodedWidth = denominator.value;
        /* ASM: fsubs converts the denominator directly to single precision,
         * avoiding MWCC'sine separate double subtraction and rounding. */
        asm { fsubs width, encodedWidth, bias }
        sample /= width;
        sample *= pi;
        sine = sin(sample * half);
        sine *= sine;
        sine *= lbl_8065189C;
        finalSine = sin(sine);
        /* ASM: frsp and fmr retain the separate rounding and return transfer.
         * MWCC coalesces the C cast and return into sample single frsp to f1. */
        asm {
            frsp f0, finalSine
            fmr rounded, f0
        }
        return rounded;
    }
    if (pos >= outStart && pos < outStart + fadeOut) {
        denominator.words.high = 0x43300000;
        denominator.words.low = (unsigned int)(fadeOut - (pos - outStart)) ^ 0x80000000;
        bias = lbl_806518A8;
        half = lbl_80651898;
        encodedSample = denominator.value;
        numerator.words.low = (unsigned int)fadeOut ^ 0x80000000;
        /* ASM: fsubs rounds the explicit integer-bias subtraction to float;
         * this MWCC emits fsub and frsp for the corresponding C cast. */
        asm { fsubs sample, encodedSample, bias }
        sample = sample - half;
        pi = lbl_80651894;
        numerator.words.high = 0x43300000;
        encodedWidth = numerator.value;
        /* ASM: fsubs converts the denominator directly to single precision,
         * avoiding MWCC'sine separate double subtraction and rounding. */
        asm { fsubs width, encodedWidth, bias }
        sample /= width;
        sample *= pi;
        sine = sin(sample * half);
        sine *= sine;
        sine *= lbl_8065189C;
        finalSine = sin(sine);
        /* ASM: frsp and fmr retain the separate rounding and return transfer.
         * MWCC coalesces the C cast and return into sample single frsp to f1. */
        asm {
            frsp f0, finalSine
            fmr rounded, f0
        }
        return rounded;
    }
    if (pos >= inStart + fadeIn && pos < outStart) {
        result = lbl_806518A0;
    }
    return result;
}
