typedef unsigned int u32;
typedef unsigned char u8;

int fn_801E7B24(u32** sets, int count, int ordinal)
{
    u32 limit = 0;
    u32 bit;
    u32 offset = 0;
    int found = -1;
    int i;
    for (i = 0; i < count; i++)
        limit = limit > sets[i][0] ? limit : sets[i][0];
    for (bit = 0; bit < limit; bit++) {
        if ((bit & 31) == 0) offset += 4;
        for (i = 0; i < count; i++) {
            u32* set = sets[i];
            if (bit < set[0] && (*(u32*)((u8*)set + offset) & (1 << (bit & 31)))) {
                if (++found == ordinal) return bit;
                break;
            }
        }
    }
    return -1;
}
