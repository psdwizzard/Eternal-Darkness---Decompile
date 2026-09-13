typedef unsigned int u32;
typedef unsigned char u8;

u32 fn_801E7A28(u32** sets, int count)
{
    u32 offset;
    u32* set;
    u32 bit;
    u32 result = 0;
    u32 max = 0;
    int i;
    int j;

    for (i = 0; i < count; i++) {
        max = max > sets[i][0] ? max : sets[i][0];
    }

    bit = 0;
    offset = 0;
    for (; bit < max; bit++) {
        if ((bit & 31) == 0) {
            offset += 4;
        }
        for (j = 0; j < count; j++) {
            set = sets[j];
            if (bit < set[0]) {
                u32 word = *(u32*)((u8*)set + offset);
                if (word & (1 << (bit & 31))) {
                    result++;
                    break;
                }
            }
        }
    }
    return result;
}
