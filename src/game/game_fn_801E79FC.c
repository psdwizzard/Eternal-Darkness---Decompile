typedef unsigned int u32;
typedef unsigned char u8;

int fn_801E79FC(u8* bits, u32 index)
{
    u32* words = (u32*)(bits + 4);
    return (words[index >> 5] & (1 << (index & 31))) != 0;
}
