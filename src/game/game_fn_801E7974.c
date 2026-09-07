typedef unsigned int u32;
typedef unsigned char u8;

void fn_801E7974(u8* bits, u32 index)
{
    u32* words = (u32*)(bits + 4);
    words[index >> 5] |= 1 << (index & 31);
}
