typedef unsigned int u32;
typedef unsigned char u8;

static inline u32 TestBits(u32 word, u32 mask)
{
    return word & mask;
}

int fn_801E79FC(u32* set, u32 index)
{
    u32 offset;
    u32 bit;

    set = (u32*)((u8*)set + 4);
    offset = (index >> 5) << 2;
    bit = index & 31;
    return TestBits(*(u32*)((u8*)set + offset), 1 << bit) != 0;
}
