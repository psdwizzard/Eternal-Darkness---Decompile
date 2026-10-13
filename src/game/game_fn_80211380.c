typedef float Mtx[3][4];
typedef struct { float x, y, z; } Vec;
extern float fn_80048C2C(float);
extern float fn_80048C50(float);
extern void fn_80211AAC(const Vec *, Vec *);
extern const float lbl_80651608;
extern const float lbl_8065160C;

/* Builds a rotation matrix of rad radians about axis (PSMTXRotAxisRad):
 * the axis is normalised into vN, then each row is assembled as paired
 * singles from (x, y) * sin / (1 - cos) products. The (x, y) pair is
 * loaded over rad once rad is no longer needed. */
void fn_80211380(register Mtx m, const Vec *axis, register float rad)
{
    Vec vN;
    register float s, c, t;
    register float zero = lbl_8065160C;
    register Vec *nAxis = &vN;
    register float cc, z, tmp2, tmp3, tT, tmp5, tmp6, tmp7, tmp8, tmp9;

    s = fn_80048C2C(rad);
    c = fn_80048C50(rad);
    t = lbl_80651608 - c;
    fn_80211AAC(axis, nAxis);
    /* ASM: psq_l loads (x, y) as one pair; C can only load lane zero. */
    asm {
        psq_l rad, 0(nAxis), 0, 0
    }
    z = nAxis->z;
    /* ASM: ps_merge00/ps_muls0/ps_muls1 scale both lanes at once; scalar
     * C only addresses lane zero. */
    asm {
        ps_merge00 cc, c, c
        ps_muls0 tT, rad, t
        ps_muls0 tmp5, z, t
        ps_muls1 tmp3, tT, rad
        ps_muls0 tmp2, tT, rad
        ps_muls0 rad, rad, s
        ps_muls0 tT, tT, z
    }
    tmp6 = __fnmsubs(z, s, tmp3);
    tmp7 = __fmadds(z, s, tmp3);
    /* ASM: ps_neg/ps_sum0/ps_sum1 combine lanes of different pairs and
     * psq_st stores both lanes; C cannot express cross-lane moves. */
    asm {
        ps_neg tmp9, rad
        ps_sum0 tmp8, tT, zero, rad
        ps_sum0 tmp2, tmp2, tmp6, cc
        ps_sum1 tmp3, cc, tmp7, tmp3
        ps_sum0 tmp6, tmp9, zero, tT
        ps_sum0 tmp9, tT, tT, tmp9
        psq_st tmp8, 8(m), 0, 0
        psq_st tmp2, 0(m), 0, 0
    }
    m[1][0] = tmp3;
    m[1][2] = tmp6;
    m[2][0] = tmp9;
    m[2][2] = tmp5 * z + c;
    m[2][3] = zero;
}
