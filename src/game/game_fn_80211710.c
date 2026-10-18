typedef float Mtx[3][4];
typedef struct Vec3 { float x, y, z; } Vec3;

/* Transform a position by an affine matrix; source may equal destination. */
void PSMTXMultVec(register const Mtx matrix, register const Vec3 *source,
                 register Vec3 *destination)
{
    register float xy, zw, rowXY, rowZW;
    register float product, result, productY, resultY;

    /* ASM: psq_l, ps_mul and ps_madd load and multiply two lanes.
     * Scalar C cannot represent independent paired-single components. */
    asm {
        psq_l xy, 0(source), 0, 0
        psq_l rowXY, 0(matrix), 0, 0
        psq_l zw, 8(source), 1, 0
        ps_mul f4, rowXY, xy
        psq_l rowZW, 8(matrix), 0, 0
        ps_madd f5, rowZW, zw, f4
        psq_l f8, 16(matrix), 0, 0
    }
    /* ASM: ps_sum0 reduces both lanes; psq_l and ps_mul form the
     * second row products. These paired operations have no C spelling. */
    asm {
        ps_sum0 result, f5, result, f5
        psq_l f9, 24(matrix), 0, 0
        ps_mul f10, f8, xy
    }
    destination->x = result;
    /* ASM: ps_madd and ps_sum0 finish the second row, and psq_l
     * reads the third row in pairs. C cannot express these operations
     * on both lanes of a paired-single register. */
    asm {
        ps_madd f11, f9, zw, f10
        psq_l rowXY, 32(matrix), 0, 0
        ps_sum0 resultY, f11, resultY, f11
    }
    rowZW = matrix[2][2];
    /* ASM: ps_mul computes both x and y products, which scalar C
     * cannot retain in a single paired register. */
    asm { ps_mul product, rowXY, xy }
    destination->y = resultY;
    /* ASM: ps_merge11 extracts the y product from the upper lane,
     * which scalar C cannot address. */
    asm { ps_merge11 productY, product, product }
    /* Finish the third row with the same separately rounded x/y
     * products and fused z product used by the paired rows. */
    zw = __fmadds(rowZW, zw, product);
    result = zw + (productY + matrix[2][3]);
    /* ASM: psq_st selects the quantized scalar store used by the
     * paired-single routine; C emits stfs. */
    asm { psq_st result, 8(destination), 1, 0 }
}
