typedef float Mtx[3][4];
typedef struct Vec3 { float x, y, z; } Vec3;

/* Transform an array of positions by a 3x4 affine matrix.
 * f0-f3 hold the paired x/y output coefficients; f4-f5 hold the
 * third row. Preserve the fused products and sum order of that row.
 * As in the original routine, the caller supplies a positive count. */
void fn_80211764(register const Mtx matrix, const Vec3* source,
                 Vec3* destination, register unsigned int count)
{
    register float a, b, xy;
    register float* input = (float*)source;
    register float* output = (float*)destination - 1;

    --count;
    a = matrix[0][0];
    b = matrix[1][0];
    /* ASM: ps_merge00 packs a matrix column; scalar C cannot set
     * the second lane independently of the first. */
    asm { ps_merge00 f0, a, b }
    a = matrix[0][1];
    b = matrix[1][1];
    /* ASM: ps_merge00 packs the y column; scalar C cannot construct
     * the two independent lanes of a paired register. */
    asm { ps_merge00 f1, a, b }
    a = matrix[0][2];
    b = matrix[1][2];
    /* ASM: ps_merge00 packs the z column; scalar C cannot construct
     * the two independent lanes of a paired register. */
    asm { ps_merge00 f2, a, b }
    a = matrix[0][3];
    b = matrix[1][3];
    /* ASM: ps_merge00 packs translations; psq_l loads both lanes
     * of the third matrix row, unavailable as a scalar C operation. */
    asm {
        ps_merge00 f3, a, b
        psq_l f4, 32(matrix), 0, 0
        psq_l f5, 40(matrix), 0, 0
    }
    do {
        /* ASM: psq_l/lu load paired coordinates, ps_madds0/1 select
         * individual lanes, and ps_mul/madd/sum0 evaluate the third
         * row. C cannot express paired lanes or their fused arithmetic. */
        asm {
            psq_l xy, 0(input), 0, 0
            psq_lu f7, 8(input), 1, 0
            ps_madds0 f8, f0, xy, f3
            ps_mul f9, f4, xy
            ps_madds1 f8, f1, xy, f8
            ps_madd f10, f5, f7, f9
            ps_madds0 f12, f2, f7, f8
            ps_sum0 f13, f10, f9, f10
        }
        input++;
        /* ASM: psq_stu stores both output lanes and the final scalar;
         * scalar C cannot store the upper lane of a paired register. */
        asm {
            psq_stu f12, 4(output), 0, 0
            psq_stu f13, 8(output), 1, 0
        }
    } while (count-- != 0);
}
