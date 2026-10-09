typedef unsigned short u16;

extern u16 lbl_80607120[];

void fn_8018C118(u16* entries, int packed_count)
{
    u16* p;
    int offset;
    int group;
    int i;

    offset = lbl_80607120[1];
    p = entries;

    for (group = 0; group < 2; group++) {
        for (i = 0; i < ((packed_count >> 1) & 0x7F) + 1; i++) {
            p[0] = 0;
            p[1] = 0;
            p[2] = 0;
            p[3] = 0x200;
            p[4] = 0x200;
            p[5] = 0;
            p[6] = 0x200;
            p[7] = 0x200;
            p += 8;
        }
        p = entries + offset * 2;
    }
}
