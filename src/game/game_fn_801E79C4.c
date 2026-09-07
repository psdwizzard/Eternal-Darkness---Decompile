typedef unsigned int u32;
typedef unsigned char u8;

int fn_801E79C4(u8* bits, u32 index)
{
    u32 mask = 1 << (index & 31);
    u32* words = (u32*)(bits + 4);
    words[index >> 5] ^= mask;
    return (words[index >> 5] & mask) != 0;
}
