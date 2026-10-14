/* A FIFO write transfers the bits of two matrix components together. */
typedef union MatrixPair {
    float component[2];
    double packed;
} MatrixPair;

/* Stream the first two rows of a 3-by-4 matrix to the graphics FIFO. */
void fn_8022B66C(register const MatrixPair *matrix,
                 register volatile double *fifo)
{
    register double tail;

    /* ASM: psq_l loads two independent float lanes per register;
     * scalar C has no type for the paired-single lanes. */
    asm {
        psq_l f0, 0(matrix), 0, 0
        psq_l f1, 8(matrix), 0, 0
        psq_l f2, 16(matrix), 0, 0
        psq_l tail, 24(matrix), 0, 0
    }
    /* ASM: psq_st writes both float lanes to the FIFO together;
     * scalar C cannot store a paired-single register. */
    asm {
        psq_st f0, 0(fifo), 0, 0
        psq_st f1, 0(fifo), 0, 0
        psq_st f2, 0(fifo), 0, 0
    }
    /* Unmatched: this emits stfd; retail stores both lanes with psq_st. */
    *fifo = tail;
}
