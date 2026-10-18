typedef float Mtx[3][4];

/* Invert an affine matrix. The cofactor pairs hold rows zero and one;
 * scalar arithmetic computes row two and the inverse translation. */
unsigned int PSMTXInverse(register const Mtx source, Mtx inverse)
{
    register float bc;
    register float hi;
    register float ca;
    register float c00;
    register float g;
    register float ef;
    register float c10;
    register float d;
    register float a;
    register float fd;
    register float c12;
    register float c11;
    register float c02;
    register float ig;
    register float c01;
    float c20, c21, c22, det, reciprocal;
    float product20;
    float x, y, z;
    /* ASM: psq_l loads both components of a row fragment; this MWCC
     * version has no paired-single C type. */
    asm {
        psq_l a, 0(source), 1, 0
        psq_l bc, 4(source), 0, 0
    }
    d = source[1][0];
    /* ASM: ps_merge10 rotates row components and psq_l loads a pair.
     * Scalar C cannot represent the second lane. */
    asm {
        ps_merge10 ca, bc, a
        psq_l ef, 20(source), 0, 0
    }
    g = source[2][0];
    /* ASM: ps_merge10, psq_l, ps_mul and ps_msub form two cofactor
     * rows with fused per-lane rounding unavailable in scalar C. */
    asm {
        ps_merge10 fd, ef, d
        psq_l hi, 36(source), 0, 0
        ps_mul c02, ef, ca
        ps_mul c00, hi, fd
        ps_merge10 ig, hi, g
        ps_msub c02, bc, fd, c02
        ps_mul c01, bc, ig
        ps_msub c00, ef, ig, c00
    }
    product20 = ef * g;
    /* ASM: ps_msub completes the remaining cofactor pair with fused
     * per-lane rounding, which scalar C cannot express. */
    asm {
        ps_msub c01, hi, ca, c01
    }
    c20 = __fmsubs(d, hi, product20);
    c21 = bc * g - a * hi;
    c22 = a * ef - bc * d;
    det = __fmadds(g, c02, __fmadds(d, c01, a * c00));
    if (det == 0.0f)
        return 0;
    reciprocal = __fres(det);
    reciprocal = (reciprocal + reciprocal) - det * (reciprocal * reciprocal);
    /* ASM: ps_merge11 extracts the upper cofactor lanes into scalar FPRs;
     * C cannot address the second lane of a paired-single register. */
    asm {
        ps_merge11 c10, c00, c00
        ps_merge11 c11, c01, c01
        ps_merge11 c12, c02, c02
    }
    x = source[0][3];
    y = source[1][3];
    z = source[2][3];
    c00 *= reciprocal;
    c01 *= reciprocal;
    c02 *= reciprocal;
    c10 *= reciprocal;
    c11 *= reciprocal;
    c12 *= reciprocal;
    c20 *= reciprocal;
    c21 *= reciprocal;
    c22 *= reciprocal;
    inverse[0][0] = c00;
    inverse[0][1] = c01;
    inverse[1][0] = c10;
    inverse[1][1] = c11;
    inverse[2][0] = c20;
    inverse[2][1] = c21;
    inverse[2][2] = c22;
    inverse[0][2] = c02;
    inverse[0][3] = __fnmadds(c02, z, __fmadds(c01, y, c00 * x));
    inverse[1][2] = c12;
    inverse[1][3] = __fnmadds(c12, z, __fmadds(c11, y, c10 * x));
    inverse[2][3] = __fnmadds(c22, z, __fmadds(c21, y, c20 * x));
    return 1;
}
