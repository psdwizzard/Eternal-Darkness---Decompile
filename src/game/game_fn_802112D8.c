typedef float Mtx[3][4];

extern const float lbl_80651608;
extern const float lbl_8065160C;

/* Build an affine rotation about the selected axis from its sine and cosine. */
void fn_802112D8(register Mtx m, unsigned int axis, register float sine,
                 register float cosine)
{
    register float zero = lbl_8065160C;
    register float one = lbl_80651608;
    register float negativeSine;

    /* ASM: ps_neg negates both lanes; scalar C only negates lane zero. */
    asm { ps_neg negativeSine, sine }
    axis |= 0x20;
    if (axis == 'x') goto rotateX;
    if (axis == 'y') goto rotateY;
    if (axis == 'z') goto rotateZ;
    goto done;

rotateX:
    /* ASM: psq_st selects a single-lane quantized store; C emits stfs. */
    asm { psq_st one, 0(m), 1, 0 }
    /* ASM: psq_st and ps_merge00 construct and store row pairs; C has
     * no paired-single type for the second lane. */
    asm {
        psq_st zero, 4(m), 0, 0
        ps_merge00 f5, sine, cosine
        psq_st zero, 12(m), 0, 0
        ps_merge00 f2, cosine, negativeSine
        psq_st zero, 28(m), 0, 0
    }
    m[2][3] = zero;
    /* ASM: psq_st writes the sine/cosine and cosine/negative-sine
     * pairs; scalar C cannot store their upper lanes. */
    asm {
        psq_st f5, 36(m), 0, 0
        psq_st f2, 20(m), 0, 0
    }
    goto done;
rotateY:
    m[1][2] = zero;
    m[1][3] = zero;
    m[0][0] = cosine;
    m[0][1] = zero;
    m[2][2] = cosine;
    m[2][3] = zero;
    m[1][0] = zero;
    m[1][1] = one;
    m[0][2] = sine;
    m[0][3] = zero;
    m[2][0] = negativeSine;
    m[2][1] = zero;
    goto done;
rotateZ:
    /* ASM: psq_st and ps_merge00 form row pairs and clear unused
     * columns; C cannot represent the second paired-single lane. */
    asm {
        psq_st zero, 8(m), 0, 0
        ps_merge00 f5, sine, cosine
        ps_merge00 negativeSine, cosine, negativeSine
        psq_st zero, 24(m), 0, 0
        psq_st zero, 32(m), 0, 0
        psq_st f5, 16(m), 0, 0
        psq_st negativeSine, 0(m), 0, 0
    }
    m[2][2] = one;
    m[2][3] = zero;
done:
    return;
}

