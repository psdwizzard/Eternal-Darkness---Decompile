typedef union PairedFloats {
    struct { float first, second; } component;
    double bits;
} PairedFloats;

typedef struct Quaternion {
    float x, y, z, w;
} Quaternion;

/* Hamilton product. A pair is moved as raw bits so each component keeps
 * its own floating-point lane. */
void PSQUATMultiply(register const Quaternion *a, register const Quaternion *b,
                    register Quaternion *out)
{
    register double xy = ((const PairedFloats *)&a->x)->bits;
    register double zw = ((const PairedFloats *)&a->z)->bits;
    register double bxy = ((const PairedFloats *)&b->x)->bits;
    register double bzw;
    register double resultXY;
    register double resultZW;

    /* ASM: ps_neg negates both float lanes; scalar C cannot retain
     * the second lane in a register. */
    asm {
        ps_neg f5, xy
    }
    bzw = ((const PairedFloats *)&b->z)->bits;
    /* ASM: ps_neg, ps_merge01, ps_muls0 and ps_muls1 operate on both
     * lanes; scalar C cannot retain the second component. */
    asm {
        ps_neg f6, zw
        ps_merge01 f4, f5, xy
        ps_muls0 f7, zw, bxy
        ps_muls0 f5, f5, bxy
        ps_merge01 zw, f6, zw
        ps_muls1 f8, f4, bxy
    }
    /* ASM: ps_madds0 fuses two lane products, which scalar C cannot do. */
    asm { ps_madds0 f7, f4, bzw, f7 }
    /* ASM: ps_muls1, ps_madds0, ps_madds1, ps_merge10 and ps_add
     * compute and rearrange both lanes; C has only scalar arithmetic. */
    asm {
        ps_muls1 bxy, zw, bxy
        ps_madds0 f5, zw, bzw, f5
        ps_madds1 f8, f6, bzw, f8
        ps_merge10 f7, f7, f7
        ps_madds1 bxy, xy, bzw, bxy
        ps_merge10 f5, f5, f5
        ps_add resultXY, f7, bxy
    }
    ((PairedFloats *)&out->x)->bits = resultXY;
    /* ASM: ps_sub subtracts both component lanes, which C cannot express. */
    asm { ps_sub resultZW, f5, f8 }
    ((PairedFloats *)&out->z)->bits = resultZW;
}
