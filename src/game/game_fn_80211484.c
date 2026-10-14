typedef float Mtx[3][4];

extern const float lbl_80651608;
extern const float lbl_8065160C;

/* Construct a translation matrix. */
void fn_80211484(register Mtx m, float x, float y, float z)
{
    register float zero = lbl_8065160C;
    float one = lbl_80651608;

    m[0][3] = x;
    m[1][3] = y;
    /* ASM: psq_st clears two matrix entries per store using both lanes
     * of zero; scalar C emits separate stfs instructions for each entry. */
    asm {
        psq_st zero, 4(m), 0, 0
        psq_st zero, 32(m), 0, 0
    }
    m[1][0] = zero;
    m[1][1] = one;
    m[1][2] = zero;
    m[2][2] = one;
    m[2][3] = z;
    m[0][0] = one;
}
