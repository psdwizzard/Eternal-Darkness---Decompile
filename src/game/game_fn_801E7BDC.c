void fn_801E7BDC(float x, float y, float z)
{
    volatile float* fifo = (volatile float*)0xCC008000;
    fifo[0] = x;
    fifo[0] = y;
    fifo[0] = z;
}
