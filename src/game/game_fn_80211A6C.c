typedef struct Vec3 {
    float x, y, z;
} Vec3;

/* Subtract two vectors; the destination may alias either input. */
void PSVECSubtract(register const Vec3 *left, register const Vec3 *right,
                 register Vec3 *destination)
{
    register float leftZ, rightZ, differenceZ;

    /* ASM: psq_l, ps_sub and psq_st subtract x/y in parallel.
     * C has no type representing both paired-single lanes. */
    asm {
        psq_l f2, 0(left), 0, 0
        psq_l f4, 0(right), 0, 0
        ps_sub f6, f2, f4
        psq_st f6, 0(destination), 0, 0
    }
    /* ASM: psq_l loads z with an implicit second lane of 1;
     * ordinary C loads cannot initialize that paired-single lane. */
    asm {
        psq_l leftZ, 8(left), 1, 0
        psq_l rightZ, 8(right), 1, 0
    }
    differenceZ = leftZ - rightZ;
    /* ASM: psq_st stores the z lane through the quantized store unit;
     * a C assignment instead emits stfs. */
    asm { psq_st differenceZ, 8(destination), 1, 0 }
}
