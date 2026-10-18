typedef struct Vec3 {
    float x, y, z;
} Vec3;

/* Compute the cross product, including when out aliases an input. */
void PSVECCrossProduct(register const Vec3 *a, register const Vec3 *b,
                 register Vec3 *out)
{
    register float axy, bxy, az, bz;

    /* ASM: psq_l loads both vector components; scalar C has no paired type. */
    asm { psq_l bxy, 0(b), 0, 0 }
    az = a->z;
    /* ASM: psq_l and ps_merge10 load a pair and swap its lanes, which
     * scalar C cannot express while retaining both floating-point lanes. */
    asm {
        psq_l axy, 0(a), 0, 0
        ps_merge10 f6, bxy, bxy
    }
    bz = b->z;
    /* ASM: ps_mul, ps_muls0, ps_msub, ps_merge11 and ps_merge01 compute
     * and arrange the cross product in paired lanes unavailable in C. */
    asm {
        ps_mul f4, bxy, az
        ps_muls0 f7, bxy, axy
        ps_msub f5, axy, bz, f4
        ps_msub f8, axy, f6, f7
        ps_merge11 f9, f5, f5
        ps_merge01 f10, f5, f8
    }
    /* ASM: psq_st and ps_neg store x and negate/store the remaining pair;
     * scalar stores and negation cannot preserve the paired-lane result. */
    asm {
        psq_st f9, 0(out), 1, 0
        ps_neg f10, f10
        psq_st f10, 4(out), 0, 0
    }
}
