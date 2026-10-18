typedef unsigned int u32;

extern u32 salLastTick;
extern u32 OSGetTick(void);

u32 salGetStartDelay(void)
{
    u32 elapsed = OSGetTick() - salLastTick;
    u32 result = elapsed * 8;
    result /= (*(volatile u32*)0x800000F8 / 4) / 125000;
    return result;
}
