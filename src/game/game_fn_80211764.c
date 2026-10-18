typedef float Mtx[3][4];
typedef struct Vec3 { float x, y, z; } Vec3;

/* Transform an array of positions by a 3x4 affine matrix.
 * f0-f3 hold the paired x/y output coefficients; f4-f5 hold the
 * third row. Preserve the fused products and sum order of that row.
 * As in the original routine, the caller supplies a positive count. */
void PSMTXMultVecArray(register const Mtx matrix, const Vec3* source,
                 Vec3* destination, register unsigned int count)
{
    register float row0, row1;
    register const float* input = (const float*)source - 1;
    register float* output = (float*)destination - 1;

    row0 = matrix[0][0];
    row1 = matrix[1][0];
    /* ASM: ps_merge00 packs a matrix column; scalar C cannot set
     * the second lane independently of the first. */
    asm { ps_merge00 f0, row0, row1 }
    row0 = matrix[0][1];
    row1 = matrix[1][1];
    /* ASM: ps_merge11 packs the y column; scalar C cannot construct
     * the two independent lanes of a paired register. */
    asm { ps_merge11 f1, row0, row1 }
    row0 = matrix[0][2];
    row1 = matrix[1][2];
    /* ASM: ps_merge00 packs the z column; scalar C cannot construct
     * the two independent lanes of a paired register. */
    asm { ps_merge00 f2, row0, row1 }
    row0 = matrix[0][3];
    row1 = matrix[1][3];
    /* ASM: ps_merge11 packs translations; psq_l loads both lanes
     * of the third matrix row, unavailable as a scalar C operation. */
    asm {
        ps_merge11 f3, row0, row1
        psq_l f4, 32(matrix), 0, 0
        psq_l f5, 40(matrix), 0, 0
    }
    do {
        /* ASM: psq_lu loads coordinates; ps_madds0, ps_madds1,
         * ps_mul, ps_madd and ps_sum0 evaluate both result lanes.
         * C cannot express the upper lane or paired fused operations. */
        asm {
            psq_lu f6, 4(input), 0, 0
            ps_madds0 f8, f0, f6, f3
            ps_mul f9, f4, f6
            ps_madds1 f8, f1, f6, f8
            psq_lu f7, 8(input), 1, 0
            ps_madds0 f12, f2, f7, f8
            ps_madd f10, f5, f7, f9
            ps_sum0 f13, f10, f9, f10
        }
        /* ASM: psq_stu stores the paired x/y result and scalar z,
         * advancing the output pointer. C cannot store the upper lane. */
        asm {
            psq_stu f12, 4(output), 0, 0
            psq_stu f13, 8(output), 1, 0
        }
    } while (--count != 0);
}
