typedef unsigned int u32;

extern void fn_80226378(void);
extern void fn_802263D4(void);

#pragma opt_propagation off

u32 fn_801EB30C(void)
{
    u32 pointer;

    fn_80226378();
    fn_802263D4();
    pointer = *(volatile u32*)0xCC003014;
    pointer &= ~(1u << 26);
    return pointer + 0x80000000;
}

#pragma opt_propagation reset
