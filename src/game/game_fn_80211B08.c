typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern const float lbl_8065162C;
extern const float lbl_80651630;

/* Return the length of a vector. */
float PSVECMag(register Vec3 *v)
{
    register float scale, length, correction;
    register float three;
    register float half;

    /* ASM: psq_l and ps_mul square the x and y components in paired-single
     * lanes, which scalar C cannot represent. */
    asm {
        psq_l scale, 0(v), 0, 0
        ps_mul scale, scale, scale
    }
    length = v->z;
    /* ASM: ps_madd adds z*z to the paired x*x lane; C has no paired lanes. */
    asm { ps_madd length, length, length, scale }
    half = lbl_8065162C;
    /* ASM: ps_sum0 folds the y*y lane into the sum, and frsqrte keeps the
     * unrounded reciprocal-square-root estimate (the C intrinsic is double). */
    asm {
        ps_sum0 length, length, scale, scale
        frsqrte scale, length
    }
    three = lbl_80651630;

    /* One Newton-Raphson step refines 1/sqrt(length squared). */
    correction = scale * scale;
    scale = scale * half;
    correction = three - correction * length;
    scale = correction * scale;

    /* ASM: fsel makes a zero length yield zero rather than NaN; the C
     * __fsel intrinsic returns double and forces an extra frsp. */
    asm { fsel scale, scale, scale, length }
    length = length * scale;
    return length;
}
