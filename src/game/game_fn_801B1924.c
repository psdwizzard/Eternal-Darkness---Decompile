typedef unsigned int u32;

extern u32 __DTKPosition;

u32 DTKGetPosition(void)
{
    return __DTKPosition;
}
