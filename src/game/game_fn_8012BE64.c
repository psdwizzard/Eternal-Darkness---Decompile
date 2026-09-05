typedef signed short s16;

void fn_8012BE64(register const s16* input, register float* output)
{
    register float first;
    register float second;
    asm {
        psq_l first, 0(input), 0, 7
        psq_lu second, 4(input), 0, 7
        psq_st first, 0(output), 0, 0
        psq_stu second, 8(output), 0, 0
    }
}
