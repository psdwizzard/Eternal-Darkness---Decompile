typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern const float lbl_8065162C;
extern const float lbl_80651630;

/* Distance between two points, using one reciprocal-square-root refinement. */
float fn_80211D74(register const Vec3 *a, register const Vec3 *b)
{
    /* Reuse the paired temporaries for the scalar refinement. */
    register float squaredDistance, reciprocal, correction;
    register float half, three;

    /* ASM: psq_l, ps_sub and ps_mul compute differences and squared
     * y/z lanes. C has no paired-single type to retain both lanes. */
    asm {
        psq_l squaredDistance, 4(a), 0, 0
        psq_l reciprocal, 4(b), 0, 0
        ps_sub correction, squaredDistance, reciprocal
        psq_l squaredDistance, 0(a), 0, 0
        psq_l reciprocal, 0(b), 0, 0
        ps_mul correction, correction, correction
        ps_sub squaredDistance, squaredDistance, reciprocal
    }
    half = lbl_8065162C;
    /* ASM: ps_madd and ps_sum0 accumulate x*x + y*y + z*z across
     * both lanes; C cannot express the paired cross-lane reduction. */
    asm {
        ps_madd squaredDistance, squaredDistance, squaredDistance, correction
        ps_sum0 squaredDistance, squaredDistance, correction, correction
    }
    three = lbl_80651630;
    /* ASM: frsqrte retains the hardware estimate without the extra
     * rounding instruction introduced by converting its double intrinsic. */
    asm { frsqrte reciprocal, squaredDistance }
    correction = reciprocal * reciprocal;
    reciprocal = reciprocal * half;
    correction = __fnmsubs(correction, squaredDistance, three);
    reciprocal = correction * reciprocal;
    /* ASM: fsel preserves the single-precision scale without the extra
     * rounding emitted when converting the double-valued C intrinsic. */
    asm { fsel reciprocal, reciprocal, reciprocal, squaredDistance }
    return squaredDistance * reciprocal;
}
