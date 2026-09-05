typedef signed short s16;

extern void fn_801252D8(int);

void fn_8012BDCC(register const float* input, register s16* output, int format)
{
    register float first;
    register float second;
    fn_801252D8(format);
    asm {
        psq_l first, 0(input), 0, 0
        psq_lu second, 8(input), 1, 0
        psq_st first, 0(output), 0, 6
        psq_stu second, 4(output), 1, 6
    }
}
