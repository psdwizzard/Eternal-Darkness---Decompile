typedef unsigned char u8;
typedef unsigned int u32;

void fn_801E79A0(u8* bits, u32 index)
{
    u32 offset = (index >> 5) << 2;
    u32 mask = ~(1 << (index & 31));
    u8* bytes;

    bytes = bits + 4;
    bytes += offset;
    *(u32*)bytes &= mask;
}
