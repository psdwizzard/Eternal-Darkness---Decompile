typedef unsigned int u32;
typedef unsigned char u8;

u32 fn_801E7A28(u32** sets, int count)
{
    u32 max = 0;
    u32 result = 0;
    u32 bit;
    u32 offset;
    int i;

    for (i = 0; i < count; i++) {
        max = max > sets[i][0] ? max : sets[i][0];
    }

    offset = 0;
    for (bit = 0; bit < max; bit++) {
        if ((bit & 31) == 0) {
            offset += 4;
        }
        for (i = 0; i < count; i++) {
            u32* set = sets[i];
            if (bit < set[0] && (*(u32*)((u8*)set + offset) & (1 << (bit & 31)))) {
                result++;
                break;
            }
        }
    }
    return result;
}
