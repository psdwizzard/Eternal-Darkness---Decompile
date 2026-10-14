/* A FIFO write transfers the bits of two matrix components together. */
typedef union MatrixPair {
    float component[2];
    double packed;
} MatrixPair;

/* Stream the six component pairs of a 3-by-4 matrix to the graphics FIFO. */
void fn_8022B604(register const MatrixPair *matrix,
                 register volatile double *fifo)
{
    register double tail;

    /* ASM: psq_l loads two independent float lanes per register;
     * C has no paired-single type for these matrix components. */
    asm {
        psq_l f0, 0(matrix), 0, 0
        psq_l f1, 8(matrix), 0, 0
        psq_l f2, 16(matrix), 0, 0
        psq_l f3, 24(matrix), 0, 0
        psq_l f4, 32(matrix), 0, 0
    }
    /* Copy the last pair as raw 64-bit data without numeric conversion. */
    tail = matrix[5].packed;
    /* ASM: psq_st writes the two float lanes together; a C double
     * store would interpret the lower lane as a double instead. */
    asm {
        psq_st f0, 0(fifo), 0, 0
        psq_st f1, 0(fifo), 0, 0
        psq_st f2, 0(fifo), 0, 0
        psq_st f3, 0(fifo), 0, 0
        psq_st f4, 0(fifo), 0, 0
    }
    *fifo = tail;
}
