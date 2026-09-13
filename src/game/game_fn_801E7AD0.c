typedef unsigned int u32;
typedef unsigned char u8;

u32 fn_801E7AD0(u32** sets, int count, u32 bit)
{
    u32 offset = (bit >> 5) << 2;
    u32 mask = 1 << (bit & 31);
    u32 result = 0;
    u32 word;
    u8* bytes;
    int i;

    for (i = 0; i < count; i++) {
        u32* set = sets[i];
        if (bit < set[0]) {
            bytes = (u8*)(set + 1);
            bytes += offset;
            word = *(u32*)bytes;
            if (word & mask) {
                result++;
            }
        }
    }
    return result;
}
