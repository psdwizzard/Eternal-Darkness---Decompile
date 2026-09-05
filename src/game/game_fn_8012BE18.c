typedef signed short s16;

extern void fn_801252D8(int);

void fn_8012BE18(register const s16* input, register float* output, int format)
{
    register float first;
    register float second;
    fn_801252D8(format);
    asm {
        psq_l first, 0(input), 0, 6
        psq_lu second, 4(input), 1, 6
        psq_st first, 0(output), 0, 0
        psq_stu second, 8(output), 1, 0
    }
}
