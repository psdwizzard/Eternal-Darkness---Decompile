typedef unsigned int u32;

void fn_801E79A0(u32* bits, u32 index)
{
    bits++;
    bits[index >> 5] &= ~(1 << (index & 31));
}
