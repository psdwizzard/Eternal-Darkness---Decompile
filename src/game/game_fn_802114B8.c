typedef float Mtx[3][4];

extern const float lbl_8065160C;

/* Construct a scale matrix. */
void PSMTXScale(register Mtx m, float x, float y, float z)
{
    register float zero = lbl_8065160C;

    m[0][0] = x;
    /* ASM: psq_st clears two entries per store using both lanes of
     * zero; scalar C produces separate stfs instructions. */
    asm {
        psq_st zero, 4(m), 0, 0
        psq_st zero, 12(m), 0, 0
    }
    m[1][1] = y;
    /* ASM: psq_st clears two entries per store using both lanes of
     * zero; scalar C produces separate stfs instructions. */
    asm {
        psq_st zero, 24(m), 0, 0
        psq_st zero, 32(m), 0, 0
    }
    m[2][2] = z;
    m[2][3] = zero;
}
