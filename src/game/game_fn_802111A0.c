typedef float Mtx[3][4];

/* Inverse-transpose of the upper 3x3 of an affine matrix: each output
 * element is the matching cofactor divided by the determinant, and the
 * translation column is cleared. Returns 0 if the matrix is singular.
 * Rows zero and one of the cofactors are built as paired singles; row
 * two and the third column use scalar arithmetic. */
unsigned int fn_802111A0(register const Mtx src, register Mtx invX)
{
    register float a;
    register float bc;
    register float d;
    register float ef;
    register float g;
    register float hi;
    register float ca;
    register float fd;
    register float ig;
    register float row0;
    register float row1;
    register float reciprocal;
    float c, f, row20, row21, c02, c12, c22, det, zero;

    /* ASM: psq_l with W=1 loads a column-zero element as (x, 1.0); MWCC
     * emits lfs for a scalar load. */
    asm {
        psq_l a, 0(src), 1, 0
        psq_l d, 16(src), 1, 0
    }
    g = src[2][0];
    /* ASM: psq_l loads both lanes of a row fragment and ps_merge10 swaps
     * lanes; the paired-single products need both lanes, which scalar C
     * cannot represent. */
    asm {
        psq_l bc, 4(src), 0, 0
        ps_merge10 ca, bc, a
        psq_l ef, 20(src), 0, 0
        ps_merge10 fd, ef, d
        psq_l hi, 36(src), 0, 0
        ps_mul row0, hi, fd
        ps_merge10 ig, hi, g
        ps_mul row1, bc, ig
    }
    /* ASM: ps_msub finishes both cofactor lanes of rows zero and one;
     * scalar fmsubs would only compute lane zero. */
    asm {
        ps_msub row0, ef, ig, row0
        ps_msub row1, hi, ca, row1
    }
    c = src[0][2];
    f = src[1][2];
    row20 = bc * f - ef * c;
    row21 = c * d - f * a;
    det = __fmadds(g, row20, __fmadds(d, row1, a * row0));
    zero = bc - bc;
    if (det == zero)
        return 0;

    reciprocal = __fres(det);
    reciprocal = (reciprocal + reciprocal) - det * (reciprocal * reciprocal);
    invX[0][3] = zero;
    invX[1][3] = zero;
    invX[2][3] = zero;
    /* ASM: ps_muls0 scales both cofactor lanes and psq_st stores the
     * pair; C cannot address the second lane. */
    asm {
        ps_muls0 row0, row0, reciprocal
        ps_muls0 row1, row1, reciprocal
        psq_st row0, 0(invX), 0, 0
        psq_st row1, 16(invX), 0, 0
    }
    c02 = d * src[2][1] - ef * g;
    c12 = bc * g - a * src[2][1];
    c22 = a * ef - bc * d;
    invX[2][0] = row20 * reciprocal;
    invX[2][1] = row21 * reciprocal;
    invX[0][2] = c02 * reciprocal;
    invX[1][2] = c12 * reciprocal;
    invX[2][2] = c22 * reciprocal;
    return 1;
}
