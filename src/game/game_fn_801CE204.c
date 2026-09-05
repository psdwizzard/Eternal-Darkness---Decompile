typedef unsigned int u32;

extern u32 lbl_8064D524;
extern u32 OSGetTick(void);

u32 fn_801CE204(void)
{
    u32 elapsed = OSGetTick() - lbl_8064D524;
    u32 result = elapsed * 8;
    result /= (*(volatile u32*)0x800000F8 / 4) / 125000;
    return result;
}
