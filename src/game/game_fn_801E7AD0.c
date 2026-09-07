typedef unsigned int u32;
typedef unsigned char u8;

u32 fn_801E7AD0(u32** sets, int count, u32 bit)
{
    u32 mask = 1 << (bit & 31);
    u32 offset = (bit >> 5) << 2;
    u32 result = 0;
    int i;

    for (i = 0; i < count; i++) {
        u32* set = sets[i];
        if (bit < set[0] && (*(u32*)((u8*)set + 4 + offset) & mask)) {
            result++;
        }
    }
    return result;
}
