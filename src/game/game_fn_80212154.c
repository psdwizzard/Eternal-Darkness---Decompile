typedef float Mtx34[3][4];
typedef float Mtx43[4][3];

/* Transpose a 3-by-4 matrix, including when source and destination coincide. */
void PSMTXReorder(register const Mtx34 source, register Mtx43 destination)
{
    register float row0, row1;

    /* ASM: psq_l loads both columns of a row into one register;
     * scalar C has no representation for the independent upper lane. */
    asm {
        psq_l row0, 0(source), 0, 0
        psq_l row1, 16(source), 0, 0
        psq_l f4, 32(source), 0, 0
        psq_l f1, 8(source), 0, 0
    }
    destination[0][0] = row0;
    /* ASM: psq_l, ps_merge01 and ps_merge11 load and interleave the
     * remaining column pairs; C cannot address their upper lanes. */
    asm {
        psq_l f3, 24(source), 0, 0
        ps_merge01 f12, f4, row0
        psq_l f5, 40(source), 0, 0
        ps_merge11 f7, row1, f4
    }
    destination[0][1] = row1;
    /* ASM: ps_merge00, ps_merge01, ps_merge11 and psq_st interleave
     * and store two components at once, which scalar C cannot express. */
    asm {
        ps_merge00 f8, f1, f3
        psq_st f12, 8(destination), 0, 0
        ps_merge01 f9, f5, f1
        psq_st f7, 16(destination), 0, 0
        ps_merge11 f10, f3, f5
        psq_st f8, 24(destination), 0, 0
        psq_st f9, 32(destination), 0, 0
        psq_st f10, 40(destination), 0, 0
    }
}
