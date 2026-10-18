typedef struct Vec3 {
    float x, y, z;
} Vec3;

/* Return the squared length of a vector. */
float PSVECSquareMag(register const Vec3 *v)
{
    register float xySquared, lengthSquared;

    /* ASM: psq_l and ps_mul square x and y in paired-single lanes;
     * scalar C cannot express the two independent lanes. */
    asm {
        psq_l xySquared, 0(v), 0, 0
        ps_mul xySquared, xySquared, xySquared
    }
    lengthSquared = v->z;
    /* ASM: ps_madd and ps_sum0 add z*z and fold in the y*y lane;
     * scalar C cannot access or preserve the paired-single upper lane. */
    asm {
        ps_madd lengthSquared, lengthSquared, lengthSquared, xySquared
        ps_sum0 lengthSquared, lengthSquared, xySquared, xySquared
    }
    return lengthSquared;
}
