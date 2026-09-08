typedef unsigned int u32;

extern void fn_80226378(void);
extern void fn_802263D4(void);

u32 fn_801EB30C(void)
{
    fn_80226378();
    fn_802263D4();
    return (*(volatile u32*)0xCC003014 & ~0x04000000) + 0x80000000;
}
