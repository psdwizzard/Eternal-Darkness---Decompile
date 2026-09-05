void fn_80149D58(register float* input, register short* output)
{
    asm {
        lfs f1, 0(input)
        psq_st f1, 0(output), 1, 5
    }
}
