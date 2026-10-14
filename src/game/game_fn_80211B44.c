typedef struct Vec3 {
    float x, y, z;
} Vec3;

/* Return the scalar product, accumulating the x/y products before the z product. */
float fn_80211B44(register Vec3 *a, register Vec3 *b)
{
    register float result, yzProduct, partial, bXY, aXY;

    /* ASM: psq_l and ps_mul retain the y and z products in separate lanes;
     * scalar C cannot represent the upper paired-single lane. */
    asm {
        psq_l yzProduct, 4(a), 0, 0
        psq_l f3, 4(b), 0, 0
        ps_mul yzProduct, yzProduct, f3
        psq_l aXY, 0(a), 0, 0
        psq_l bXY, 0(b), 0, 0
    }
    partial = __fmadds(aXY, bXY, yzProduct);
    /* ASM: ps_sum0 adds the retained z product to the x/y sum;
     * scalar C cannot directly access the upper paired-single lane. */
    asm { ps_sum0 result, partial, yzProduct, yzProduct }
    return result;
}
