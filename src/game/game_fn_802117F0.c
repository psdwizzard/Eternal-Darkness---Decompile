typedef float Mtx[3][4];
typedef struct Vec3 { float x, y, z; } Vec3;

/* Transform a direction by the linear part of an affine matrix.
 * Each paired product holds the separate x and y contributions. */
void PSMTXMultVecSR(register const Mtx matrix, register const Vec3* source,
                 register Vec3* destination)
{
    register float tail0, tail1, tail2, outZ;

    /* ASM: psq_l loads both lanes and ps_mul multiplies them independently;
     * scalar C cannot represent the paired x/y products. */
    asm {
        psq_l f0, 0(matrix), 0, 0
        psq_l f6, 0(source), 0, 0
        psq_l f2, 16(matrix), 0, 0
        ps_mul f8, f0, f6
        psq_l f4, 32(matrix), 0, 0
        ps_mul f10, f2, f6
        psq_l f7, 8(source), 1, 0
        ps_mul f12, f4, f6
    }
    tail1 = matrix[1][2];
    /* ASM: ps_sum0 reduces the x/y product pair; scalar C cannot
     * access its upper lane. */
    asm { ps_sum0 f8, f8, f8, f8 }
    tail2 = matrix[2][2];
    /* ASM: ps_sum0 adds the second row's x/y product lanes, which
     * cannot be addressed independently in scalar C. */
    asm { ps_sum0 f10, f10, f10, f10 }
    tail0 = matrix[0][2];
    /* ASM: ps_sum0 reduces the last pair; ps_madd completes the paired
     * fused products and psq_st stores their lower lanes. C cannot
     * express these paired-single arithmetic and store operations. */
    asm {
        ps_sum0 f12, f12, f12, f12
        ps_madd f9, tail0, f7, f8
        psq_st f9, 0(destination), 1, 0
        ps_madd f11, tail1, f7, f10
        psq_st f11, 4(destination), 1, 0
        ps_madd outZ, tail2, f7, f12
    }
    destination->z = outZ;
}
