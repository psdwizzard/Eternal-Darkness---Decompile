void fn_801F3914(float x, float y)
{
    *(volatile float*)0xCC008000 = x;
    *(volatile float*)0xCC008000 = y;
}
