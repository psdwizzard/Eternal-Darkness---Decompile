typedef struct Quaternion {
    float x, y, z, w;
} Quaternion;

extern const float lbl_80651638;
extern const float lbl_80651654;
extern const float lbl_80651658;
extern double __frsqrte(double);

/* Normalize a quaternion, selecting zero below the squared-length threshold. */
void PSQUATNormalize(register const Quaternion *in, register Quaternion *out)
{
    register float xy, zw, lengthSquared;
    register double reciprocal;
    register float threshold, zero;
    register double correction;
    register float half, three;

    threshold = lbl_80651638;
    half = lbl_80651654;
    three = lbl_80651658;
    /* ASM: psq_l, ps_mul, ps_sub, ps_madd and ps_sum0 load quaternion
     * pairs and compute their squared length. C cannot represent both
     * lanes or the cross-lane sum of paired-single registers. */
    asm {
        psq_l xy, 0(in), 0, 0
        ps_mul lengthSquared, xy, xy
        psq_l zw, 8(in), 0, 0
        ps_sub zero, threshold, threshold
        ps_madd lengthSquared, zw, zw, lengthSquared
        ps_sum0 lengthSquared, lengthSquared, lengthSquared, lengthSquared
    }
    reciprocal = __frsqrte(lengthSquared);
    /* ASM: ps_sub retains both selection lanes; scalar C subtraction
     * cannot preserve the paired-single upper lane. */
    asm { ps_sub threshold, lengthSquared, threshold }
    correction = reciprocal * reciprocal;
    reciprocal = reciprocal * half;
    correction = three - correction * lengthSquared;
    reciprocal = correction * reciprocal;
    /* ASM: ps_sel, ps_muls0 and psq_st select the scale, multiply both
     * quaternion pairs and store them. C cannot express paired selection,
     * broadcast multiplication or paired stores. */
    asm {
        ps_sel reciprocal, threshold, reciprocal, zero
        ps_muls0 xy, xy, reciprocal
        ps_muls0 zw, zw, reciprocal
        psq_st xy, 0(out), 0, 0
        psq_st zw, 8(out), 0, 0
    }
}
