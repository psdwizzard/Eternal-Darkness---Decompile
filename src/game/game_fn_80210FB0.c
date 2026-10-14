typedef float Mtx[3][4];

extern const float lbl_80651608;
extern const float lbl_8065160C;

/* Initialize an affine transformation to the identity matrix. */
void fn_80210FB0(register Mtx matrix)
{
    register float zero = lbl_8065160C;
    register float one = lbl_80651608;
    register float zeroOne;

    /* ASM: psq_st, ps_merge01 and ps_merge10 construct and store pairs
     * (0, 0), (0, 1) and (1, 0). Scalar C cannot access the upper
     * paired-single lane and emits separate stfs stores instead. */
    asm {
        psq_st zero, 8(matrix), 0, 0
        ps_merge01 zeroOne, zero, one
        psq_st zero, 24(matrix), 0, 0
        ps_merge10 one, one, zero
        psq_st zero, 32(matrix), 0, 0
        psq_st zeroOne, 16(matrix), 0, 0
        psq_st one, 0(matrix), 0, 0
        psq_st one, 40(matrix), 0, 0
    }
}
