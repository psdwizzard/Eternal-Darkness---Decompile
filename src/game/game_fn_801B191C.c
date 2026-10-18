typedef unsigned int u32;

extern u32 __DTKState;

u32 DTKGetState(void)
{
    return __DTKState;
}
