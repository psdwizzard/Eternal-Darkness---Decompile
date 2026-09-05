typedef signed short s16;

void fn_8012BE78(register const float* input, register s16* output)
{
    register float first;
    register float second;
    asm {
        psq_l first, 0(input), 0, 0
        psq_lu second, 8(input), 0, 0
        psq_st first, 0(output), 0, 7
        psq_stu second, 4(output), 0, 7
    }
}
