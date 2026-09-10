void fn_801FD21C(float x, float y)
{
    *(volatile float*)0xCC008000 = x;
    *(volatile float*)0xCC008000 = y;
}
