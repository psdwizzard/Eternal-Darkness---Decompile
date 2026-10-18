typedef struct Vec3 {
    float x, y, z;
} Vec3;

/* Add two vectors; the result may alias either input. */
void PSVECAdd(register const Vec3 *a, register const Vec3 *b,
                 register Vec3 *result)
{
    register float az, bz, sumZ;

    /* ASM: psq_l, ps_add and psq_st add and store x/y together.
     * Scalar C cannot represent the independent upper paired-single lane. */
    asm {
        psq_l f2, 0(a), 0, 0
        psq_l f4, 0(b), 0, 0
        ps_add f6, f2, f4
        psq_st f6, 0(result), 0, 0
    }
    /* ASM: psq_l selects the quantized single-component loads used here;
     * scalar C loads use lfs instead. */
    asm {
        psq_l az, 8(a), 1, 0
        psq_l bz, 8(b), 1, 0
    }
    sumZ = az + bz;
    /* ASM: psq_st selects a quantized single-component store;
     * scalar C stores use stfs instead. */
    asm { psq_st sumZ, 8(result), 1, 0 }
}
