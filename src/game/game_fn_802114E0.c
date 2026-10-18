typedef float Mtx[3][4];
typedef struct Quaternion { float x, y, z, w; } Quaternion;
extern const float lbl_80651608;

/* Convert a quaternion to a rotation matrix, including normalization. */
void PSMTXQuat(register Mtx m, register const Quaternion *q)
{
    register float zero, one, two, norm, xy, zw, squaresXY;
    register float squaresZW, sums, yx, crossW, reciprocal;
    float x, y;
    one = lbl_80651608;

    /* ASM: psq_l loads the two quaternion pairs; scalar C cannot load
     * both lanes of a paired-single register. */
    asm {
        psq_l xy, 0(q), 0, 0
        psq_l zw, 8(q), 0, 0
    }
    zero = one - one;
    two = one + one;
    /* ASM: ps_mul, ps_merge10, ps_madd, ps_sum0 and ps_muls1 compute
     * quaternion products in both lanes and sum the squared norm. C
     * has no paired-single type or cross-lane arithmetic operators. */
    asm {
        ps_mul squaresXY, xy, xy
        ps_merge10 yx, xy, xy
        ps_madd sums, zw, zw, squaresXY
        ps_mul squaresZW, zw, zw
        ps_sum0 norm, sums, sums, sums
        ps_muls1 crossW, yx, zw
    }
    reciprocal = __fres(norm);
    /* ASM: ps_sum1 builds (x*x + z*z, y*y + z*z), requiring access
     * to the upper lane of squaresXY, which C cannot address. */
    asm {
        ps_sum1 sums, squaresZW, sums, squaresXY
    }
    norm = __fnmsubs(norm, reciprocal, two);
    /* ASM: ps_muls1 multiplies by the w lane, which C cannot address. */
    asm {
        ps_muls1 squaresZW, zw, zw
    }
    norm = reciprocal * norm;
    /* ASM: ps_sum0 adds the squared x and y lanes; C cannot access y*y. */
    asm {
        ps_sum0 squaresXY, squaresXY, squaresXY, squaresXY
    }
    /* The refined reciprocal gives the matrix scale 2 / dot(q, q). */
    norm *= two;
    /* ASM: ps_madd and ps_msub form paired sums and differences of
     * quaternion products; scalar C cannot operate on both lanes. */
    asm {
        ps_madd reciprocal, xy, yx, squaresZW
        ps_msub squaresZW, xy, yx, squaresZW
    }
    x = q->x;
    y = q->y;
    m[0][3] = zero;
    squaresXY = __fnmsubs(squaresXY, norm, one);
    /* ASM: ps_nmsub computes both diagonal entries in parallel; scalar
     * C cannot preserve the upper diagonal lane. */
    asm {
        ps_nmsub sums, sums, norm, one
    }
    m[2][3] = zero;
    reciprocal *= norm;
    squaresZW *= norm;
    m[2][2] = squaresXY;
    m[1][0] = reciprocal;
    m[1][1] = sums;
    /* ASM: ps_merge11 extracts the upper diagonal lane for C to store. */
    asm {
        ps_merge11 yx, sums, sums
    }
    m[0][0] = yx;
    m[0][1] = squaresZW;
    /* ASM: ps_merge11 extracts x*w from the upper product lane. */
    asm {
        ps_merge11 squaresXY, crossW, crossW
    }
    /* Finish x*z +/- y*w and y*z +/- x*w in scalar arithmetic. */
    yx = __fmadds(x, zw, crossW);
    zw = __fmadds(y, zw, squaresXY);
    m[0][2] = yx * norm;
    m[1][2] = __fnmsubs(squaresXY, two, zw) * norm;
    m[1][3] = zero;
    m[2][0] = __fnmsubs(crossW, two, yx) * norm;
    m[2][1] = zw * norm;
}
