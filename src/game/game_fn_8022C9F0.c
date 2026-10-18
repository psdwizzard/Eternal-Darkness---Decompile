typedef unsigned short u16;

extern volatile u16 *__memReg;

void PERFResetAllMemMetrics(void)
{
    /* Clear the memory performance counter register pairs in hardware order. */
    __memReg[25] = 0;
    __memReg[26] = 0;
    __memReg[27] = 0;
    __memReg[28] = 0;
    __memReg[30] = 0;
    __memReg[29] = 0;
    __memReg[32] = 0;
    __memReg[31] = 0;
    __memReg[34] = 0;
    __memReg[33] = 0;
    __memReg[36] = 0;
    __memReg[35] = 0;
    __memReg[38] = 0;
    __memReg[37] = 0;
    __memReg[40] = 0;
    __memReg[39] = 0;
    __memReg[42] = 0;
    __memReg[41] = 0;
    __memReg[44] = 0;
    __memReg[43] = 0;
}
