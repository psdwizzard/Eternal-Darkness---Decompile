typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern const float lbl_8065162C;
extern const float lbl_80651630;

/* Normalize a vector, allowing the source and destination to coincide. */
void PSVECNormalize(register Vec3 *source, register Vec3 *destination)
{
    register float half = lbl_8065162C;
    register float three = lbl_80651630;
    register float xy, z, lengthSquared, inverseLength, correction;

    /* ASM: psq_l, ps_mul, ps_madd and ps_sum0 compute the squared
     * length in paired-single lanes, which scalar C cannot represent. */
    asm {
        psq_l xy, 0(source), 0, 0
        ps_mul inverseLength, xy, xy
        psq_l z, 8(source), 1, 0
        ps_madd lengthSquared, z, z, inverseLength
        ps_sum0 lengthSquared, lengthSquared, z, inverseLength
    }
    /* ASM: frsqrte retains the unrounded reciprocal-square-root estimate;
     * converting the double C intrinsic result to float adds a rounding. */
    asm { frsqrte inverseLength, lengthSquared }
    correction = inverseLength * inverseLength;
    half = inverseLength * half;
    correction = three - correction * lengthSquared;
    inverseLength = correction * half;

    /* ASM: ps_muls0 and psq_st scale and store the paired components;
     * scalar C cannot preserve the upper lane or use quantized stores. */
    asm {
        ps_muls0 xy, xy, inverseLength
        psq_st xy, 0(destination), 0, 0
        ps_muls0 z, z, inverseLength
        psq_st z, 8(destination), 1, 0
    }
}
