typedef struct Vec3 {
    float x, y, z;
} Vec3;

/* Squared distance between two points. */
float PSVECSquareDistance(register const Vec3 *a, register const Vec3 *b)
{
    register float difference, other, yzSquared;

    /* ASM: psq_l, ps_sub and ps_mul retain the y/z differences and
     * their squares in paired lanes, which scalar C cannot represent. */
    asm {
        psq_l difference, 4(a), 0, 0
        psq_l other, 4(b), 0, 0
        ps_sub yzSquared, difference, other
        psq_l difference, 0(a), 0, 0
        psq_l other, 0(b), 0, 0
        ps_mul yzSquared, yzSquared, yzSquared
        ps_sub difference, difference, other
    }
    other = __fmadds(difference, difference, yzSquared);
    /* ASM: ps_sum0 adds the retained z square to the scalar x/y sum;
     * C cannot directly read the upper paired-single lane. */
    asm { ps_sum0 other, other, yzSquared, yzSquared }
    return other;
}
