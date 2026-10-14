typedef float Mtx[3][4];

/* Send the upper 3-by-3 normal matrix to the graphics FIFO, row by row. */
void fn_8022B638(register const Mtx mtx, register volatile float *fifo)
{
    register float row0, z0, row1, z1, row2, z2;

    /* ASM: psq_l loads two row components into independent lanes;
     * scalar C cannot represent the upper paired-single lane. */
    asm { psq_l row0, 0(mtx), 0, 0 }
    z0 = mtx[0][2];
    /* ASM: psq_l loads the next row's pair, unavailable in scalar C. */
    asm { psq_l row1, 16(mtx), 0, 0 }
    z1 = mtx[1][2];
    /* ASM: psq_l loads the last row's pair, unavailable in scalar C. */
    asm { psq_l row2, 32(mtx), 0, 0 }
    z2 = mtx[2][2];

    /* ASM: psq_st writes both row components to the FIFO in one store;
     * scalar C cannot store both paired-single lanes. */
    asm { psq_st row0, 0(fifo), 0, 0 }
    *fifo = z0;
    /* ASM: psq_st writes the second pair, unavailable in scalar C. */
    asm { psq_st row1, 0(fifo), 0, 0 }
    *fifo = z1;
    /* ASM: psq_st writes the final pair, unavailable in scalar C. */
    asm { psq_st row2, 0(fifo), 0, 0 }
    *fifo = z2;
}
