typedef struct Quaternion {
    float x, y, z, w;
} Quaternion;

/* Hamilton product. Either input may also be the destination. */
void fn_80211DC0(register const Quaternion *a, register const Quaternion *b,
                 register Quaternion *out)
{
    register float xy, zw, bxy, bzw;
    float resultX;
    register float resultY;

    /* ASM: psq_l and ps_neg load and negate quaternion pairs. C has
     * no paired-single type to preserve both lanes of these values. */
    asm {
        psq_l xy, 0(a), 0, 0
        psq_l zw, 8(a), 0, 0
        psq_l bxy, 0(b), 0, 0
        ps_neg f5, xy
        psq_l bzw, 8(b), 0, 0
        ps_neg f6, zw
    }
    /* ASM: ps_merge01 forms (-x,y), a cross-lane operation absent in C. */
    asm { ps_merge01 f4, f5, xy }
    /* ASM: ps_muls0 forms the z*x product while retaining its paired
     * companion; C emits only a scalar multiply. */
    asm { ps_muls0 resultY, zw, bxy }
    /* ASM: ps_muls0, ps_merge01 and ps_muls1 form paired z/w terms,
     * which scalar C cannot retain in both register lanes. */
    asm {
        ps_muls0 f5, f5, bxy
        ps_merge01 zw, f6, zw
        ps_muls1 f8, f4, bxy
    }
    resultX = a->w * bxy;
    resultX = __fmadds(a->y, bzw, resultX);
    resultY = __fmadds(-xy, bzw, resultY);
    /* ASM: ps_madds0 and ps_madds1 fuse both z/w product lanes; C
     * cannot address the upper lane for arithmetic. */
    asm {
        ps_madds0 f5, zw, bzw, f5
        ps_madds1 f8, f6, bzw, f8
    }
    resultX += __fmadds(xy, b->w, zw * b->y);
    resultY += __fmadds(a->y, b->w, a->w * b->y);
    /* ASM: ps_merge10 swaps the z/w cross terms, which C cannot do
     * without storing and reloading the upper lane. */
    asm { ps_merge10 f5, f5, f5 }
    out->x = resultX;
    out->y = resultY;
    /* ASM: ps_sub and psq_st finish both z/w lanes; C has no paired
     * subtraction or paired store. */
    asm {
        ps_sub f5, f5, f8
        psq_st f5, 8(out), 0, 0
    }
}
