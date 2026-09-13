typedef unsigned int u32;
typedef unsigned char u8;

static inline u32 IndexBit(u32 index)
{
    return 1 << (index & 31);
}

#pragma opt_common_subs off
int fn_801E79C4(u8* bits, u32 index)
{
    u32* words = (u32*)(bits + 4);
    words[index >> 5] ^= IndexBit(index);
    return (words[index >> 5] & IndexBit(index)) != 0;
}
