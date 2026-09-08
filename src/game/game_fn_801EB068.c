void fn_801EB068(float x, float y, float z)
{
    *(volatile float*)0xCC008000 = x;
    *(volatile float*)0xCC008000 = y;
    *(volatile float*)0xCC008000 = z;
}
