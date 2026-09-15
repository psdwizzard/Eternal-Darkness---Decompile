typedef unsigned short u16;

extern u16 lbl_80607120[];

#define CURRENT_ENTRY(address) ((u16 *)(address))

void fn_8018C118(u16* entries, int packed_count)
{
    register unsigned long entries_r = (unsigned long)entries;
    u16* second;
    int group;

    second = (u16 *)entries_r + lbl_80607120[1] * 2;

    for (group = 0; group < 2; group++) {
        int i;
        for (i = 0; i < (((packed_count >> 1) & 0x7F) + 1); i++) {
            CURRENT_ENTRY(entries_r)[0] = 0;
            CURRENT_ENTRY(entries_r)[1] = 0;
            CURRENT_ENTRY(entries_r)[2] = 0;
            CURRENT_ENTRY(entries_r)[3] = 0x200;
            CURRENT_ENTRY(entries_r)[4] = 0x200;
            CURRENT_ENTRY(entries_r)[5] = 0;
            CURRENT_ENTRY(entries_r)[6] = 0x200;
            CURRENT_ENTRY(entries_r)[7] = 0x200;
            entries_r += 8 * sizeof(u16);
        }
        entries_r = (unsigned long)second;
    }
}

#undef CURRENT_ENTRY
