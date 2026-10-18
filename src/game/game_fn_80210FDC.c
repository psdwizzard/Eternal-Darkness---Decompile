typedef float Mtx[3][4];
extern const float Unit01[]; /* Paired translation mask: { 0, 1 }. */

/* Concatenate two affine matrices: ab = a * b. Load all of b before
 * writing results so either input matrix may also be the destination. */
void PSMTXConcat(register const Mtx a, register const Mtx b, register Mtx ab)
{
    register const float *unit = Unit01;
    register float translation, y, x, z;
    const float (*end)[4] = a + 3;

    /* ASM: psq_l loads two independent matrix entries into each FPR;
     * scalar C cannot represent the upper paired-single lane. */
    asm {
        psq_l f6, 0(b), 0, 0
        psq_l f7, 8(b), 0, 0
        psq_l f31, 0(unit), 0, 0
        psq_l f8, 16(b), 0, 0
        psq_l f9, 24(b), 0, 0
        psq_l f10, 32(b), 0, 0
        psq_l f11, 40(b), 0, 0
    }
    while (a != end) {
        x = a[0][0];
        y = a[0][1];
        z = a[0][2];
        translation = a[0][3];
        /* ASM: ps_muls0, ps_madds1 and ps_madds0 evaluate paired columns
         * with independent lanes, which scalar C cannot represent. */
        asm {
            ps_muls0 f2, f6, x
            ps_muls0 f0, f7, x
            ps_madds1 f2, f8, y, f2
            ps_madds1 f0, f9, y, f0
            ps_madds0 f2, f10, z, f2
            ps_madds0 f0, f11, z, f0
        }
        /* ASM: ps_madds1 adds translation only to the final column and
         * psq_st stores both lanes. C cannot address the upper lane. */
        asm {
            psq_st f2, 0(ab), 0, 0
            ps_madds1 f0, f31, translation, f0
            psq_st f0, 8(ab), 0, 0
        }
        ++a;
        ++ab;
    }
}
