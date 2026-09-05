typedef unsigned int u32;

extern u32 lbl_8064D160;
extern void fn_801F5598(u32, u32*, u32);

#pragma opt_propagation off
void fn_8015E168(u32 address, u32 size)
{
    u32 aligned_address = (address - 0x4B904) & ~31;
    u32* descriptor;

    lbl_8064D160 = aligned_address;
    descriptor = &lbl_8064D160;
    descriptor[1] = aligned_address;
    fn_801F5598((size + 31) & ~31, descriptor, aligned_address);
}
#pragma opt_propagation reset
