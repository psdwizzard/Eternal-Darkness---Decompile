typedef unsigned int u32;
typedef unsigned char u8;

int fn_801E7B24(u32** sets, int count, int ordinal)
{
    u32 offset;
    u32* set;
    u32 bit;
    int found;
    u32 limit;
    u32 word;
    int i;
    found = -1;
    limit = 0;
    for (i = 0; i < count; i++)
        limit = limit > sets[i][0] ? limit : sets[i][0];
    bit = 0;
    offset = 0;
    for (; bit < limit; bit++) {
        if ((bit & 31) == 0) offset += 4;
        for (i = 0; i < count; i++) {
            set = sets[i];
            if (bit < set[0]) {
                word = *(u32*)((u8*)set + offset);
                if (!(word & (1 << (bit & 31))))
                    continue;
                if (++found == ordinal) return bit;
                break;
            }
        }
    }
    return -1;
}
