typedef unsigned short u16;

extern volatile u16 *__cpReg;

void GXClearGPMetric(void)
{
    __cpReg[2] = 4;
}
